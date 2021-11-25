set(opengl_source_files
  buffer.cpp
  pipeline.cpp
  shader.cpp
)

target_sources(engine PRIVATE ${opengl_source_files})