set(render_source_files
  buffer.cpp
  renderer.cpp
  renderingQueue.cpp
  shader.cpp
)

target_sources(engine PRIVATE ${render_source_files})
