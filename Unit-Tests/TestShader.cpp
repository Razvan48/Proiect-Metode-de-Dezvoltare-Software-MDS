#include "CppUnitTest.h"

#include <string>
#include <sstream>
#include <locale>
#include <stdexcept>

#include "../Apocalypse/source/ResourceManager/ResourceManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestShader
{
    TEST_CLASS(TestShader)
    {
    public:
        TEST_METHOD(Sprite)
        {
            Logger::WriteMessage("sprite-shader");

            try
            {
                ResourceManager::loadShader("../../../Apocalypse/shaders/sprite.vert", "../../../Apocalypse/shaders/sprite.frag", nullptr, "sprite");
            }
            catch (const std::runtime_error& err)
            {
                Assert::Fail(widen(err.what()).c_str());
            }
            catch (...)
            {
                Assert::Fail(L"Other errors");
            }
        }

        TEST_METHOD(Text)
        {
            Logger::WriteMessage("text-shader");

            try
            {
                ResourceManager::loadShader("../../../Apocalypse/shaders/text.vert", "../../../Apocalypse/shaders/text.frag", nullptr, "text");
            }
            catch (const std::runtime_error& err)
            {
                Assert::Fail(widen(err.what()).c_str());
            }
            catch (...)
            {
                Assert::Fail(L"Other errors");
            }
        }

        TEST_METHOD(Player)
        {
            Logger::WriteMessage("player-shader");

            try
            {
                ResourceManager::loadShader("../../../Apocalypse/shaders/player.vert", "../../../Apocalypse/shaders/player.frag", nullptr, "player");
            }
            catch (const std::runtime_error& err)
            {
                Assert::Fail(widen(err.what()).c_str());
            }
            catch (...)
            {
                Assert::Fail(L"Other errors");
            }
        }

    private:
        std::wstring widen(const std::string& str)
        {
            std::wostringstream wstm;
            const std::ctype<wchar_t>& ctfacet = std::use_facet<std::ctype<wchar_t>>(wstm.getloc());
            for (size_t i = 0; i < str.size(); ++i)
            {
                wstm << ctfacet.widen(str[i]);
            }

            return wstm.str();
        }
    };
}

