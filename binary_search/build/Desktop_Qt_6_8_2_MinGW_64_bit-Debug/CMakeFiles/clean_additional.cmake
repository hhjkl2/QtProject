# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\binary_search_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\binary_search_autogen.dir\\ParseCache.txt"
  "binary_search_autogen"
  )
endif()
