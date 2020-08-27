set(render_include_files
  buffer.h
  renderer.h
  renderingContext.h
  renderingQueue.h
  shader.h
  util.h
)

target_sources(engine PRIVATE ${render_include_files})
