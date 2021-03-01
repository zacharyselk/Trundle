set(event_source_files
  event.cpp
  keyEvent.cpp
  mouseEvent.cpp
  windowEvent.cpp
)

target_sources(engine PRIVATE ${event_source_files})