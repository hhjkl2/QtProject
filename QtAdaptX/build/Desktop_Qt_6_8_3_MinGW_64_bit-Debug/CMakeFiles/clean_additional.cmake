# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QtAdaptX_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QtAdaptX_autogen.dir\\ParseCache.txt"
  "QtAdaptX_autogen"
  )
endif()
