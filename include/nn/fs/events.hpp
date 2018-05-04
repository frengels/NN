#pragma once

#include <string>

#include <sys/inotify.h>

namespace nn {
struct fs_event {
  uint32_t mask;
  std::string filename;
};
} // namespace nn