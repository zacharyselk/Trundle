set(opengl_source_files
  buffer.cpp
  openGLContext.cpp
  renderingQueue.cpp
  shader.cpp
)

target_sources(engine PRIVATE ${opengl_source_files})
