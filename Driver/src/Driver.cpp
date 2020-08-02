#include <Trundle.h>
#include <sstream>

class ExampleLayer : public Trundle::Layer {
public:
  ExampleLayer()
    : Layer("HelloLayer")  { }

  void onUpdate() override final {
    Trundle::Log::Info("ExampleLayer::Update");
  }

  void onEvent(Trundle::Event& event) override final {
    Trundle::Log::Info(event.toString());
  }
};

class Game : public Trundle::Application {
    public:
    Game()  {
      pushLayer(new ExampleLayer);
      pushOverlay(new Trundle::ImGuiLayer);
    }

    ~Game()  { }
};

Trundle::Application* Trundle::CreateApplication() {
    return new Game();
}
