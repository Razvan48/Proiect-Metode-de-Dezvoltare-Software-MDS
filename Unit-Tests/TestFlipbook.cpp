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
        TEST_METHOD(BulletBlast)
        {
            Logger::WriteMessage("Bullet Blast");

            try
            {
                ResourceManager::loadFlipbook("../../../Apocalypse/resources/animations/bulletBlast", 15.0, true, "bulletBlast");

                Assert::AreEqual(9, ResourceManager::getFlipbook("bulletBlast").getNumFrames()); // 9

                for (int i = 0; i < ResourceManager::getFlipbook("bulletBlast").getNumFrames(); i++)
                {
                    Assert::AreEqual(128u, ResourceManager::getFlipbook("bulletBlast").getTextureAtIndex(i).width); // 128
                    Assert::AreEqual(128u, ResourceManager::getFlipbook("bulletBlast").getTextureAtIndex(i).height); // 128
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

