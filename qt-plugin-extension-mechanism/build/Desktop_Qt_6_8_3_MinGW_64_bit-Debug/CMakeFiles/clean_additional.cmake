# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SamplePlugin_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SamplePlugin_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\qt-plugin-extension-mechanism_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\qt-plugin-extension-mechanism_autogen.dir\\ParseCache.txt"
  "SamplePlugin_autogen"
  "qt-plugin-extension-mechanism_autogen"
  )
endif()
