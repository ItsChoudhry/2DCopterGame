#include "Game.hpp"
#include "AssetManager.hpp"
#include "Constants.hpp"
#include "Map.hpp"
#include "components/ColliderComponent.hpp"
#include "components/KeyboardControlComponent.hpp"
#include "components/ProjectileEmitterComponent.hpp"
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
Entity *mainPlayer = nullptr;
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

    loadLevel(1);
    m_running = true;
    return;
}

void Game::loadLevel(int t_levelNumber)
{
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    std::string levelName = "Level" + std::to_string(t_levelNumber);
    lua.script_file("./assets/scripts/" + levelName + ".lua");

    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];

    unsigned int assetIndex = 0;
    while (true)
    {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
        if (existsAssetIndexNode == sol::nullopt)
        {
            break;
        }
        else
        {
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];
            if (assetType.compare("texture") == 0)
            {
                std::string assetID = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->addTexture(assetID, assetFile.c_str());
            }
        }
        assetIndex++;
    }

    sol::table levelMap = levelData["map"];
    std::string mapTextureid = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];
    map = new Map(mapTextureid, static_cast<int>(levelMap["scale"]),
                  static_cast<int>(levelMap["tileSize"]));

    map->loadMap(mapFile, levelMap["mapSizeX"], levelMap["mapSizeY"]);
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
    if (collisionType == PLAYER_PROJECTILE_COLLISION)
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
    if (mainPlayer)
    {
        TransformComponent *mainPlayerTransform =
            mainPlayer->getComponent<TransformComponent>();
        camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
        camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

        camera.x = camera.x < 0 ? 0 : camera.x;
        camera.y = camera.y < 0 ? 0 : camera.y;
        camera.x = camera.x > camera.w ? camera.w : camera.x;
        camera.y = camera.y > camera.h ? camera.h : camera.y;
    }
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
