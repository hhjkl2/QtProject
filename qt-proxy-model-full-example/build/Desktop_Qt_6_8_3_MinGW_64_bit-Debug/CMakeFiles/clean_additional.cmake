# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appqt-proxy-model-full-example_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appqt-proxy-model-full-example_autogen.dir\\ParseCache.txt"
  "appqt-proxy-model-full-example_autogen"
  )
endif()
