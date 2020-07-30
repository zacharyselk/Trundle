set(platform_source_files
  macOSWindow.cpp
  windowsWindow.cpp
  )

target_sources(engine PRIVATE ${platform_source_files})
