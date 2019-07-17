#include "Game.hpp"
#include "AssetManager.hpp"
#include "Constants.hpp"
#include "Map.hpp"
#include "components/ColliderComponent.hpp"
#include "components/KeyboardControlComponent.hpp"
#include "components/SpirteComponent.hpp"
#include "components/TextLabelComponent.hpp"
#include "components/TransformComponent.hpp"
#include <iostream>
#include <string>

EntityManager manager;
AssetManager *Game::assetManager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map *map;

Game::Game() { this->m_running = false; }

Game::~Game() {}

void Game::initialize(int t_width, int t_height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing sdl" << std::endl;
        return;
    }
    if (TTF_Init() != 0)
    {
        std::cerr << "Error initializing ttf" << std::endl;
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

Entity &playerEntity(manager.addEntity("chopper", PLAYER_LAYER));
void Game::loadLevel(int t_levelNumber)
{
    // Add assets
    assetManager->addTexture("tank-image",
                             std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->addTexture(
        "chopper-image",
        std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->addTexture("radar-image",
                             std::string("./assets/images/radar.png").c_str());
    assetManager->addTexture("jungle-tiletexture",
                             std::string("./assets/tilemaps/jungle.png").c_str());
    assetManager->addTexture("helipad-image",
                             std::string("./assets/images/heliport.png").c_str());
    assetManager->addFont("charriot-font",
                          std::string("./assets/fonts/charriot.ttf").c_str(), 14);

    map = new Map("jungle-tiletexture", 2, 32);
    map->loadMap("./assets/tilemaps/jungle.map", 25, 20);

    // Add entities and components to them
    playerEntity.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    playerEntity.addComponent<SpirteComponent>("chopper-image", 2, 90, true, false);
    playerEntity.addComponent<KeyboardControlComponent>("up", "down", "left", "right",
                                                        "space");
    playerEntity.addComponent<ColliderComponent>("player", 240, 106, 32, 32);

    Entity &tankEntity(manager.addEntity("tank", ENEMY_LAYER));
    tankEntity.addComponent<TransformComponent>(150, 500, 20, 0, 32, 32, 1);
    tankEntity.addComponent<SpirteComponent>("tank-image");
    tankEntity.addComponent<ColliderComponent>("enemy", 150, 500, 32, 32);

    Entity &helipadEntity(manager.addEntity("helipad", OBSTACLE_LAYER));
    helipadEntity.addComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
    helipadEntity.addComponent<SpirteComponent>("helipad-image");
    helipadEntity.addComponent<ColliderComponent>("level_complete", 470, 420, 32, 32);

    Entity &radarEntity(manager.addEntity("radar", UI_LAYER));
    radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.addComponent<SpirteComponent>("radar-image", 8, 150, false, true);

    Entity &labelLevelName(manager.addEntity("LabelLevelName", UI_LAYER));
    labelLevelName.addComponent<TextLabelComponent>(10, 10, "First Level...",
                                                    "charriot-font", WHITE_COLOR);
}

bool Game::isRunning() const { return m_running; }

void Game::processInput()
{
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

    handleCameraMovement();
    checkCollisions();
}

void Game::checkCollisions()
{
    CollisionType collisionType = manager.checkCollisions();
    if (collisionType == PLAYER_ENEMY_COLLISION)
    {
        processGameOver();
    }
    if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION)
    {
        processNextLevel(1);
    }
}

void Game::processGameOver()
{
    std::cout << "Game over";
    m_running = false;
}

void Game::processNextLevel(int t_levelNumber)
{
    std::cout << "Next level";
    m_running = false;
}

void Game::handleCameraMovement()
{
    TransformComponent *mainPlayerTransform =
        playerEntity.getComponent<TransformComponent>();
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
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
