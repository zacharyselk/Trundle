# Platform specific compilationi
if(APPLE)
  add_subdirectory(MacOS)
elseif(UNIX)
  add_subdirectory(Linux)
elseif(WIN32)
  add_subdirectory(Windows)
else()
  message(FATAL_ERROR "Error: Unknown platform, aborting.")
endif()

add_subdirectory(OpenGL)