#pragma once


#define EVENT_BOILERPLATE(type)                           \
  static EventType getStaticType() {                      \
    return EventType::type;                               \
  }                                                       \
  virtual EventType getEventType() const override final { \
    return getStaticType();                               \
  }                                                       \
  virtual const char* getName() const override final {    \
    return #type;                                         \
  }

