set(render_include_files
  buffer.h
  renderingContext.h
  renderingQueue.h
  shader.h
)

target_sources(engine PRIVATE ${render_include_files})
