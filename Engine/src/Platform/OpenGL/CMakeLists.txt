set(opengl_source_files
  buffer.cpp
  openGLContext.cpp
)

target_sources(engine PRIVATE ${opengl_source_files})
