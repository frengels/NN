#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <mutex>
#include <optional>
#include <queue>
#include <string>
#include <thread>

#include <spdlog/spdlog.h>
#include <sys/inotify.h>

#include "nn/fs/events.hpp"

namespace nn {
class fs_monitor {
public:
  using callback_type = std::function<void(uint32_t)>;

private:
  /**
   * out handle to the inotify system
   */
  int m_inotify;
  std::map<int, std::filesystem::path> m_watches;
  std::queue<fs_event> m_events;
  std::mutex m_queue_access;

  std::thread m_background_watcher;
  bool m_should_stop;

  std::shared_ptr<spdlog::logger> m_logger;

public:
  fs_monitor();
  ~fs_monitor();

  bool watch(const std::filesystem::path& p);
  void run();
  void stop();
  bool poll_events(fs_event& ev);

private:
  void _run_blocking();
};
} // namespace nn