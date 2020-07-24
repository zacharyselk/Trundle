set(trundle_source_files
  application.cpp
  application.h
  core.h
  gateway.h
  log.h
  threadPool.h
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(engine PUBLIC ${trundle_source_files})