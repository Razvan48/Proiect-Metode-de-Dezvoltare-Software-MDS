#include "CppUnitTest.h"

#include <string>
#include <sstream>
#include <locale>
#include <stdexcept>

#include "../Apocalypse/source/ResourceManager/ResourceManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestTexture
{
    TEST_CLASS(TestTexture)
    {
    public:
        TEST_METHOD(OpenGLTest_png)
        {
            Logger::WriteMessage("OpenGL-test.png");

            try
            {
                ResourceManager::loadTexture("../../../Apocalypse/resources/textures/OpenGL-test.png", true, "OpenGL-Logo");

                Assert::AreEqual(static_cast<unsigned int>(2000), ResourceManager::getTexture("OpenGL-Logo").width); // 2000
                Assert::AreEqual(static_cast<unsigned int>(867), ResourceManager::getTexture("OpenGL-Logo").height); // 867
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

