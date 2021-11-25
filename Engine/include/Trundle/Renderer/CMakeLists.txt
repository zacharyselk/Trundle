set(renderer_include_files
  buffer.h
  pipeline.h
  render2D.h
  renderer.h
  shader.h
  util.h
)

target_sources(engine PRIVATE ${renderer_include_files})