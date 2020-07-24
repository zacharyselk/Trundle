#include <Trundle.h>


class Game : public Trundle::Application {
    public:
    Game()  { }
    ~Game()  { }
};

Trundle::Application* Trundle::CreateApplication() {
    return new Game();
}