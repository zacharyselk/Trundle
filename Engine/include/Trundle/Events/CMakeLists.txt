set(event_include_files
  event.h
  keyEvent.h
  mouseEvent.h
  windowEvent.h
)

target_sources(engine PRIVATE ${event_include_files})