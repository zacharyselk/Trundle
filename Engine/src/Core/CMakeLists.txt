set(core_source_files
  application.cpp
  layerStack.cpp
  time.cpp
)

target_sources(engine PRIVATE ${core_source_files})
