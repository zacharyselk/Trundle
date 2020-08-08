#pragma once

#include <Trundle/trundle.hpp>
#include <Trundle/Core/core.h>
#include <Trundle/Events/event.h>


namespace Trundle {

  class TRUNDLE_API Layer {
  public:
    Layer(const std::string &name=std::string("Layer"))
      : name(name)  { }
    virtual ~Layer()  { }

    virtual void onAttach()  { }
    virtual void onDetach()  { }
    virtual void onUpdate()  { }
    virtual void onEvent(Event &event)  { }

    inline const std::string& getName()  { return name; }

  protected:
    // TODO: Gen with reflection
    std::string name;
  };

}
