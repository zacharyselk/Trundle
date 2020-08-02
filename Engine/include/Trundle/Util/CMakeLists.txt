set(util_include_files
  boilerplate.h
  common.h
  constants.h
  imGuiLayer.h
)

target_sources(engine PRIVATE ${util_include_files})
