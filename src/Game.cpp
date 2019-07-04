#include "Game.hpp"
#include "Constants.hpp"
#include "components/TransformComponent.hpp"
#include <iostream>

EntityManager manager;
SDL_Renderer *Game::renderer;

Game::Game() { this->m_running = false; }

Game::~Game() {}

void Game::initialize(int t_width, int t_height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing sdl" << std::endl;
        return;
    }

    m_window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                t_width, t_height, SDL_WINDOW_BORDERLESS);
    if (!m_window)
    {
        std::cerr << "Error creating window" << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!renderer)
    {
        std::cerr << "Error creating renderer" << std::endl;
        return;
    }

    loadLevel(0);
    m_running = true;
    return;
}

void Game::loadLevel(int t_levelNumber)
{
    Entity &newEntity(manager.addEntity("projectile"));
    newEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
}

bool Game::isRunning() const { return m_running; }

void Game::processInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
    {
        m_running = false;
        break;
    }
    case SDL_KEYDOWN:
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            m_running = false;
            break;
        }
    }
    default:
    {
        break;
    }
    }
}
void Game::update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME))
        ;

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    ticksLastFrame = SDL_GetTicks();

    manager.update(deltaTime);
}
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.hasNoEntities())
    {
        return;
    }

    manager.render();

    SDL_RenderPresent(renderer);
}

void Game::destory()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
