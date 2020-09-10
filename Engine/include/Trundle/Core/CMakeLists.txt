set(core_include_files
  application.h
  core.h
  gateway.h
  log.h
  threadPool.h
  time.h
)

target_sources(engine PRIVATE ${core_include_files})
