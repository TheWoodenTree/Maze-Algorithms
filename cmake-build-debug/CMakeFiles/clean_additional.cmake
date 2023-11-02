# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\mine-sweeper_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\mine-sweeper_autogen.dir\\ParseCache.txt"
  "mine-sweeper_autogen"
  )
endif()
