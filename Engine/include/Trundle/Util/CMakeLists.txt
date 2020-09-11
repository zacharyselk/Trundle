set(util_include_files
  boilerplate.h
  common.h
  imGuiLayer.h
  primitives.h
)

target_sources(engine PRIVATE ${util_include_files})
