#include "CppUnitTest.h"

#include <string>
#include <sstream>
#include <locale>
#include <stdexcept>

#include "../Apocalypse/source/ResourceManager/ResourceManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFlipbook
{
    TEST_CLASS(TestFlipbook)
    {
    public:
        TEST_METHOD(PlayerIdle)
        {
            Logger::WriteMessage("PlayerIdle");

            try
            {
                ResourceManager::loadFlipbook("../../../Apocalypse/animations/playerIdle", 15.0f, "playerIdle");

                Assert::AreEqual(8, ResourceManager::getFlipbook("playerIdle").getNumFrames()); // 8

                for (int i = 0; i < ResourceManager::getFlipbook("playerIdle").getNumFrames(); i++)
                {
                    Assert::AreEqual(static_cast<unsigned int>(128), ResourceManager::getFlipbook("playerIdle").getTextureAtIndex(i).width); // 128
                    Assert::AreEqual(static_cast<unsigned int>(128), ResourceManager::getFlipbook("playerIdle").getTextureAtIndex(i).height); // 128
                }
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

        TEST_METHOD(PlayerWalking)
        {
            Logger::WriteMessage("PlayerWalking");

            try
            {
                ResourceManager::loadFlipbook("../../../Apocalypse/animations/playerWalking", 25.0f, "playerWalking");

                Assert::AreEqual(15, ResourceManager::getFlipbook("playerWalking").getNumFrames()); // 15

                for (int i = 0; i < ResourceManager::getFlipbook("playerWalking").getNumFrames(); i++)
                {
                    Assert::AreEqual(static_cast<unsigned int>(128), ResourceManager::getFlipbook("playerWalking").getTextureAtIndex(i).width); // 128
                    Assert::AreEqual(static_cast<unsigned int>(128), ResourceManager::getFlipbook("playerWalking").getTextureAtIndex(i).height); // 128
                }
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

        TEST_METHOD(PlayerRunning)
        {
            Logger::WriteMessage("PlayerRunning");

            try
            {
                ResourceManager::loadFlipbook("../../../Apocalypse/animations/playerRunning", 30.0f, "playerRunning");

                Assert::AreEqual(15, ResourceManager::getFlipbook("playerRunning").getNumFrames()); // 15

                for (int i = 0; i < ResourceManager::getFlipbook("playerRunning").getNumFrames(); i++)
                {
                    Assert::AreEqual(static_cast<unsigned int>(128), ResourceManager::getFlipbook("playerRunning").getTextureAtIndex(i).width); // 128
                    Assert::AreEqual(static_cast<unsigned int>(128), ResourceManager::getFlipbook("playerRunning").getTextureAtIndex(i).height); // 128
                }
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

        TEST_METHOD(PlayerTired)
        {
            Logger::WriteMessage("PlayerTired");

            try
            {
                ResourceManager::loadFlipbook("../../../Apocalypse/animations/playerTired", 30.0f, "playerTired");

                Assert::AreEqual(8, ResourceManager::getFlipbook("playerTired").getNumFrames()); // 8

                for (int i = 0; i < ResourceManager::getFlipbook("playerTired").getNumFrames(); i++)
                {
                    Assert::AreEqual(static_cast<unsigned int>(128), ResourceManager::getFlipbook("playerTired").getTextureAtIndex(i).width); // 128
                    Assert::AreEqual(static_cast<unsigned int>(128), ResourceManager::getFlipbook("playerTired").getTextureAtIndex(i).height); // 128
                }
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
        
        // TODO: more tests

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

