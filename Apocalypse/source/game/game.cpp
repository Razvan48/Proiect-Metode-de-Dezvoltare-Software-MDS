#include "game.h"

Game::Game()
{
    windowManager.get();
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
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        GlobalClock::get().updateTime();

        glfwSwapBuffers(WindowManager::get().getWindow());
        glfwPollEvents();
    }
}