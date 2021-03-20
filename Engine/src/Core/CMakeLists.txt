set(core_source_files
  application.cpp
  input.cpp
  layer.cpp
  layerStack.cpp
)

target_sources(engine PRIVATE ${core_source_files})