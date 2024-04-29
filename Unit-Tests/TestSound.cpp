#include "CppUnitTest.h"

#include <string>
#include <sstream>
#include <locale>
#include <stdexcept>

#include "../Apocalypse/source/ResourceManager/ResourceManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSound
{
    TEST_CLASS(TestSound)
    {
    public:
        TEST_METHOD(Walking)
        {
            Logger::WriteMessage("walking");

            try
            {
                ResourceManager::loadSound("../../../Apocalypse/resources/sounds/walking.mp3", FMOD_LOOP_NORMAL, "walking");
            }
            catch (const std::runtime_error& err)
            {
                Assert::Fail(widen(err.what()).c_str());
            }
            catch (...)
            {
                Assert::Fail(L"Other errors");
            }

            unsigned int length;
            ResourceManager::getSound("walking")->getLength(&length, FMOD_TIMEUNIT_MS);
            Assert::AreEqual(59977u, length); // 59977
        }

        TEST_METHOD(Running)
        {
            Logger::WriteMessage("running");

            try
            {
                ResourceManager::loadSound("../../../Apocalypse/resources/sounds/running.mp3", FMOD_LOOP_NORMAL, "running");
            }
            catch (const std::runtime_error& err)
            {
                Assert::Fail(widen(err.what()).c_str());
            }
            catch (...)
            {
                Assert::Fail(L"Other errors");
            }

            unsigned int length;
            ResourceManager::getSound("running")->getLength(&length, FMOD_TIMEUNIT_MS);
            Assert::AreEqual(5952u, length); // 5952
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

