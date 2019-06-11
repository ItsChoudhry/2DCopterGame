
#include "Constants.h"
#include "Game.h"
#include <memory>

int main(int argc, char *args[])
{
    std::unique_ptr<Game> game = std::make_unique<Game>();

    game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->isRunning())
    {
        game->processInput();
        game->update();
        game->render();
    }

    game->destory();

    return 0;
}
