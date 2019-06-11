#include <iostream>
#include <functional>
#include <lua.hpp>
#include <glm.hpp>
#include "SDL/SDL.h"
#include "Constants.h"
#include "./Game.h"

int main(int argc, char *args[])
{
    Game *game = new Game();

    game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->isRunning())
    {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Destory();

    return 0;
}