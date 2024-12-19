# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ProduseQT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ProduseQT_autogen.dir\\ParseCache.txt"
  "ProduseQT_autogen"
  )
endif()
