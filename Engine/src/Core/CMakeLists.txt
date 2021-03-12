set(core_source_files
  application.cpp
  layer.cpp
  layerStack.cpp
)

target_sources(engine PRIVATE ${core_source_files})