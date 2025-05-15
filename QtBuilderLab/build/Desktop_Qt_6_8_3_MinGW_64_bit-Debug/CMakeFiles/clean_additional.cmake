# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QtBuilderLab_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QtBuilderLab_autogen.dir\\ParseCache.txt"
  "QtBuilderLab_autogen"
  )
endif()
