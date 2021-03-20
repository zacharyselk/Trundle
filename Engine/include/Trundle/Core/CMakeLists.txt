
set(core_include_files
  application.h
  gateway.h
  input.h
  keyCode.h
  layer.h
  layerStack.h
  log.h
  pointer.h
  util.h
  window.h
)

target_sources(engine PRIVATE ${core_include_files})