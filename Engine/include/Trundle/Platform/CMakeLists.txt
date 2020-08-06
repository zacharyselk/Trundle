add_subdirectory(OpenGL)

set(platform_include_files
  linuxWindow.h
  macOSWindow.h
  windowsWindow.h
)

target_sources(engine PRIVATE ${platform_include_files})
