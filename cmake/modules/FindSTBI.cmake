# By Jonathan Dearborn
# Based on FindFFMPEG.cmake
# Copyright (c) 2008 Andreas Schneider <mail@cynapses.org>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#
# Defines:
# STBI_FOUND
# STBI_INCLUDE_DIR


if (STBI_INCLUDE_DIR)
    set(STBI_FOUND TRUE)
else (STBI_INCLUDE_DIR)
  find_path(STBI_INCLUDE_DIR
    NAMES stb_image.h
    PATHS /usr/include /usr/include/stb /usr/local/include /usr/local/include/stb /opt/local/include /sw/include
    PATH_SUFFIXES stbi
  )

  if (STBI_INCLUDE_DIR)
    set(STBI_FOUND TRUE)
  endif(STBI_INCLUDE_DIR)

  if (STBI_FOUND)
    if (NOT STBI_FIND_QUIETLY)
      message(STATUS "Found stb-image: ${STBI_INCLUDE_DIR}")
    endif (NOT STBI_FIND_QUIETLY)
  else (STBI_FOUND)
    if (STBI_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find stb-image")
    endif (STBI_FIND_REQUIRED)
  endif (STBI_FOUND)

endif (STBI_INCLUDE_DIR)
