set(renderer_source_files
  buffer.cpp
  geometry.cpp
  pipeline.cpp
  render2D.cpp
  renderer.cpp
  shader.cpp
)

target_sources(engine PRIVATE ${renderer_source_files})