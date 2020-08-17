#pragma once


namespace Trundle {

  enum RenderingAPI {
     None = 0,
     OpenGL = 1
  };

  class Renderer {
  public:
    Renderer(RenderingAPI api)
      : api(api)  { }

    RenderingAPI getAPI() const { return api; }
  private:
    RenderingAPI api;
  }

}
