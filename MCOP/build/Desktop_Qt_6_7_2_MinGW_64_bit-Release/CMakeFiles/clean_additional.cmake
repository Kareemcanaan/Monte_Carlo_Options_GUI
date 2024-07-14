# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\MCOP_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MCOP_autogen.dir\\ParseCache.txt"
  "MCOP_autogen"
  )
endif()
