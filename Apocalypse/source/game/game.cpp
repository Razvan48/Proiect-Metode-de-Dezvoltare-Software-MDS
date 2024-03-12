#include "game.h"

#include "../windowManager/windowManager.h"
#include "../globalClock/globalClock.h"
#include "../map/map.h"

#include <iostream>

Game::Game()
{
    WindowManager::get();
}

Game::~Game()
{

}

Game& Game::get()
{
    static Game instance;

    return instance;
}

void Game::loadAssets()
{

}

void Game::run()
{
    this->loadAssets();

    while (!glfwWindowShouldClose(WindowManager::get().getWindow()))
    {
        // Input
        // TODO

        // Render
        glClearColor(0.733f, 0.024f, 0.259f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Update
        GlobalClock::get().updateTime();

        // Swap the screen buffers
        glfwSwapBuffers(WindowManager::get().getWindow());
       
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
    }
}

