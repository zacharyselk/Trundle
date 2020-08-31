set(render_source_files
  buffer.cpp
  renderer.cpp
  sceneRenderer.cpp
  shader.cpp
)

target_sources(engine PRIVATE ${render_source_files})
