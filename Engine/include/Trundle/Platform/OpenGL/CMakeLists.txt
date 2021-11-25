set(opengl_include_files
  buffer.h
  pipeline.h
  shader.h
  util.h
)

target_sources(engine PRIVATE ${opengl_include_files})