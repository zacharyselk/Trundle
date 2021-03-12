
set(core_include_files
  application.h
  gateway.h
  layer.h
  layerStack.h
  log.h
  util.h
  window.h
)

target_sources(engine PRIVATE ${core_include_files})