#include "nn/fs/fs_monitor.hpp"

#include <unistd.h>

namespace nn {
fs_monitor::fs_monitor()
    : m_inotify{inotify_init()}
    , m_should_stop{false}
    , m_logger{spdlog::stdout_color_st("fswatch")} {
  m_logger->set_level(spdlog::level::trace);
}

fs_monitor::~fs_monitor() {
  if (m_inotify) {
    for (auto wd : m_watches) {
      inotify_rm_watch(m_inotify, wd.first);
    }
    close(m_inotify);
  }
}

bool fs_monitor::watch(const std::filesystem::path& p) {
  int wd = inotify_add_watch(m_inotify, p.c_str(), IN_ALL_EVENTS);
  if (wd < 0) {
    m_logger->warn("failed to watch: \"{}\"", p.string());
    return false;
  }

  m_logger->debug("added \"{}\" to the watch", p.string());
  m_watches[wd] = p;
  return true;
}

void fs_monitor::run() {
  // start the background thread
  m_background_watcher = std::thread(&fs_monitor::_run_blocking, this);
  m_logger->debug("he has started his watch");
}

void fs_monitor::stop() {
  m_should_stop = true;
  m_background_watcher.join();
  m_logger->debug("and so his watch ends");
}

bool fs_monitor::poll_events(fs_event& ev) {
  std::lock_guard<std::mutex> queue_access(m_queue_access);
  if (std::empty(m_events)) {
    return false;
  }

  fs_event ev_front{m_events.front()};
  m_events.pop();

  ev.filename = ev_front.filename;
  ev.mask = ev_front.mask;

  return true;
}

void fs_monitor::_run_blocking() {
  while (!m_should_stop) {
    char buffer[1024];

    int num_bytes = read(m_inotify, buffer, 1024);

    char* p;
    struct inotify_event* ievent;
    for (p = buffer; p < buffer + num_bytes;) {
      ievent = reinterpret_cast<struct inotify_event*>(p);
      // TODO: distinction between file and directory
      fs_event event = {};
      event.filename = m_watches[ievent->wd];
      event.mask = ievent->mask;

      m_logger->debug("inotify received: {}, {}", event.filename, event.mask);

      std::lock_guard<std::mutex> queue_access(m_queue_access);

      // push the event into the queue
      m_events.push(event);

      p += sizeof(struct inotify_event) + ievent->len;
    }
  }
}
} // namespace nn