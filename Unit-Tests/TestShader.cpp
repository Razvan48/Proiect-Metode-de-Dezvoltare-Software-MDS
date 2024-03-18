#include "CppUnitTest.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h> 
#include <cstdlib>

#include "../Apocalypse/source/ResourceManager/ResourceManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestShader
{
    GLFWwindow* window;

    TEST_MODULE_INITIALIZE(TestShaderModuleInit)
    {
        Logger::WriteMessage("TestShader module initialization");

        const char* github_actions = std::getenv("GITHUB_ACTIONS");
        bool env_github_actions = false;

        if (github_actions && std::string(github_actions) == "true") 
        {
            Logger::WriteMessage("GITHUB_ACTIONS - OK");

            env_github_actions = true;

            HINSTANCE opengl = LoadLibrary(TEXT("opengl32.dll"));
            HINSTANCE libglapi = LoadLibrary(TEXT("libglapi.dll"));
            HINSTANCE osmesa = LoadLibrary(TEXT("osmesa.dll"));

            if (opengl != NULL)
            {
                Logger::WriteMessage("opengl32.dll - OK");
            }
            else
            {
                Assert::Fail(L"opengl32.dll - FAIL");
            }

            if (libglapi != NULL)
            {
                Logger::WriteMessage("libglapi.dll - OK");
            }
            else
            {
                Assert::Fail(L"libglapi.dll - FAIL");
            }

            if (osmesa != NULL)
            {
                Logger::WriteMessage("osmesa.dll - OK");
            }
            else
            {
                Assert::Fail(L"osmesa.dll - FAIL");
            }
        }
        else 
        {
            Logger::WriteMessage("GITHUB_ACTIONS - NO");
        }

        // Init GLFW
        Logger::WriteMessage("Initialize GLFW");

        if (!glfwInit())
        {
            Assert::Fail(L"Failed to init GLFW");
        }

        // Set all the required options for GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // Use Mesa on Github Windows Runner
        if (env_github_actions)
        {
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_OSMESA_CONTEXT_API);
        }

        // Create a GLFWwindow object that we can use for GLFW's functions
        window = glfwCreateWindow(1200, 900, "Apocalypse", NULL, NULL);
        if (window == nullptr)
        {
            glfwTerminate();
            Assert::Fail(L"Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);

        // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            Assert::Fail(L"Failed to initialize GLAD");
        }

        // Successfully loaded OpenGL
        Logger::WriteMessage("Loaded OpenGL");
    }

    TEST_MODULE_CLEANUP(TestShaderModuleCleanup)
    {
        Logger::WriteMessage("TestShader module cleanup");

        // Destroy window
        glfwDestroyWindow(window);

        // Terminates GLFW, clearing any resources allocated by GLFW
        glfwTerminate();
    }

    TEST_CLASS(TestShader)
    {
    public:
        TEST_METHOD(Test1)
        {
            Logger::WriteMessage("Start TEST-1");

            // ResourceManager::loadShader("../../../Apocalypse/shaders/vertShader.vert", "../../../Apocalypse/shaders/fragShader.frag", nullptr, "TestShader");

            // TODO: compile
            // ExpectException
        }

        // TODO: more tests
    };
}

