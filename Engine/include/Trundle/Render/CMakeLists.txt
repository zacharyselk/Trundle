set(render_include_files
  buffer.h
  renderingContext.h
  shader.h
)

target_sources(engine PRIVATE ${render_include_files})
