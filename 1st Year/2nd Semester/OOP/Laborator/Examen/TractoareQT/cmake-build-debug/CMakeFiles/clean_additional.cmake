# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TractoareQT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TractoareQT_autogen.dir\\ParseCache.txt"
  "TractoareQT_autogen"
  )
endif()
