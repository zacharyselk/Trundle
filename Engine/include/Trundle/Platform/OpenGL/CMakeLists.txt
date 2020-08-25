set(opengl_include_files
  buffer.h
  openGLContext.h
  shader.h
)

target_sources(engine PRIVATE ${opengl_include_files})
