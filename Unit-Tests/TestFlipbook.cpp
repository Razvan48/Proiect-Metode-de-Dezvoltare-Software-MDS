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
        TEST_METHOD(bulletBlast)
        {
            Logger::WriteMessage("bulletBlast");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/bulletBlast", "bulletBlast", 9);
        }

        TEST_METHOD(doorOpening0)
        {
            Logger::WriteMessage("doorOpening0");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/doorOpening0", "doorOpening0", 8);
        }
        
        TEST_METHOD(doorOpening1)
        {
            Logger::WriteMessage("doorOpening1");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/doorOpening1", "doorOpening1", 8);
        }

        TEST_METHOD(doorStatic0)
        {
            Logger::WriteMessage("doorStatic0");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/doorStatic0", "doorStatic0", 1);
        }

        TEST_METHOD(doorStatic1)
        {
            Logger::WriteMessage("doorStatic1");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/doorStatic1", "doorStatic1", 1);
        }

        TEST_METHOD(grenadeExplosion)
        {
            Logger::WriteMessage("grenadeExplosion");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/grenadeExplosion", "grenadeExplosion", 12);
        }

        TEST_METHOD(enemy0ArmsNot)
        {
            Logger::WriteMessage("enemy0ArmsNot");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/enemyComponents/arms/armsNot", "enemy0ArmsNot", 1);
        }

        TEST_METHOD(enemy0ArmsStayingAhead)
        {
            Logger::WriteMessage("enemy0ArmsStayingAhead");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/enemyComponents/arms/armsStayingAhead", "enemy0ArmsStayingAhead", 1);
        }

        TEST_METHOD(enemy0BodyIdle)
        {
            Logger::WriteMessage("enemy0BodyIdle");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/enemyComponents/body/bodyIdle", "enemy0BodyIdle", 1);
        }

        TEST_METHOD(enemy0HeadIdle)
        {
            Logger::WriteMessage("enemy0HeadIdle");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/enemyComponents/head/headIdle", "enemy0HeadIdle", 1);
        }

        TEST_METHOD(enemy0LegsNot)
        {
            Logger::WriteMessage("enemy0LegsNot");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/enemyComponents/legs/legsNot", "enemy0LegsNot", 1);
        }

        TEST_METHOD(enemy0LegsMovingAround)
        {
            Logger::WriteMessage("enemy0LegsMovingAround");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/enemyComponents/legs/legsMovingAround", "enemy0LegsMovingAround", 15);
        }

        TEST_METHOD(enemy0Dead)
        {
            Logger::WriteMessage("enemy0Dead");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/enemyDead/enemy0Dead", "enemy0Dead", 1);
        }

        TEST_METHOD(enemy1Dead)
        {
            Logger::WriteMessage("enemy1Dead");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/enemyDead/enemy1Dead", "enemy1Dead", 1);
        }

        TEST_METHOD(player0ArmsHoldingGrenade)
        {
            Logger::WriteMessage("player0ArmsHoldingGrenade");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsHoldingGrenade", "player0ArmsHoldingGrenade", 1);
        }

        TEST_METHOD(player0ArmsHoldingKnife)
        {
            Logger::WriteMessage("player0ArmsHoldingKnife");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsHoldingKnife", "player0ArmsHoldingKnife", 1);
        }

        TEST_METHOD(player0ArmsHoldingPistol)
        {
            Logger::WriteMessage("player0ArmsHoldingPistol");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsHoldingPistol", "player0ArmsHoldingPistol", 1);
        }

        TEST_METHOD(player0ArmsHoldingShotgun)
        {
            Logger::WriteMessage("player0ArmsHoldingShotgun");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsHoldingShotgun", "player0ArmsHoldingShotgun", 1);
        }

        TEST_METHOD(player0ArmsHoldingAK47)
        {
            Logger::WriteMessage("player0ArmsHoldingAK47");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsHoldingAK47", "player0ArmsHoldingAK47", 1);
        }

        TEST_METHOD(player0ArmsHoldingM4)
        {
            Logger::WriteMessage("player0ArmsHoldingAK47");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsHoldingM4", "player0ArmsHoldingM4", 1);
        }

        TEST_METHOD(player0ArmsMovingAhead)
        {
            Logger::WriteMessage("player0ArmsHoldingAK47");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsMovingAhead", "player0ArmsMovingAhead", 8);
        }

        TEST_METHOD(player0ArmsMovingAroundWalking)
        {
            Logger::WriteMessage("player0ArmsMovingAroundWalking");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsMovingAround", "player0ArmsMovingAroundWalking", 15);
        }

        TEST_METHOD(player0ArmsNot)
        {
            Logger::WriteMessage("player0ArmsNot");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsNot", "player0ArmsNot", 1);
        }

        TEST_METHOD(player0ArmsReloadingPistol)
        {
            Logger::WriteMessage("player0ArmsReloadingPistol");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsReloadingPistol", "player0ArmsReloadingPistol", 8);
        }

        TEST_METHOD(player0ArmsReloadingShotgun)
        {
            Logger::WriteMessage("player0ArmsReloadingShotgun");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsReloadingShotgun", "player0ArmsReloadingShotgun", 9);
        }

        TEST_METHOD(player0ArmsReloadingAK47)
        {
            Logger::WriteMessage("player0ArmsReloadingAK47");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsReloadingAK47", "player0ArmsReloadingAK47", 10);
        }

        TEST_METHOD(player0ArmsReloadingM4)
        {
            Logger::WriteMessage("player0ArmsReloadingM4");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsReloadingM4", "player0ArmsReloadingM4", 10);
        }

        TEST_METHOD(player0ArmsUsingGrenade)
        {
            Logger::WriteMessage("player0ArmsUsingGrenade");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsUsingGrenade", "player0ArmsUsingGrenade", 14);
        }

        TEST_METHOD(player0ArmsUsingKnife)
        {
            Logger::WriteMessage("player0ArmsUsingKnife");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsUsingKnife", "player0ArmsUsingKnife", 8);
        }

        TEST_METHOD(player0ArmsUsingPistol)
        {
            Logger::WriteMessage("player0ArmsUsingPistol");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsUsingPistol", "player0ArmsUsingPistol", 4);
        }

        TEST_METHOD(player0ArmsUsingShotgun)
        {
            Logger::WriteMessage("player0ArmsUsingShotgun");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsUsingShotgun", "player0ArmsUsingShotgun", 4);
        }

        TEST_METHOD(player0ArmsUsingFist)
        {
            Logger::WriteMessage("player0ArmsUsingFist");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsUsingFist", "player0ArmsUsingFist", 8);
        }

        TEST_METHOD(player0ArmsUsingAK47)
        {
            Logger::WriteMessage("player0ArmsUsingAK47");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsUsingAK47", "player0ArmsUsingAK47", 4);
        }

        TEST_METHOD(player0ArmsUsingM4)
        {
            Logger::WriteMessage("player0ArmsUsingM4");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/arms/armsUsingM4", "player0ArmsUsingM4", 4);
        }

        TEST_METHOD(player0BodyIdle)
        {
            Logger::WriteMessage("player0BodyIdle");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/body/bodyIdle", "player0BodyIdle", 1);
        }

        TEST_METHOD(player0HeadAngry)
        {
            Logger::WriteMessage("player0HeadAngry");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/head/headAngry", "player0HeadAngry", 4);
        }

        TEST_METHOD(player0HeadIdle)
        {
            Logger::WriteMessage("player0HeadIdle");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/head/headIdle", "player0HeadIdle", 4);
        }

        TEST_METHOD(player0HeadSatisfied)
        {
            Logger::WriteMessage("player0HeadSatisfied");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/head/headSatisfied", "player0HeadSatisfied", 4);
        }

        TEST_METHOD(player0HeadTired)
        {
            Logger::WriteMessage("player0HeadTired");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/head/headTired", "player0HeadTired", 8);
        }

        TEST_METHOD(player0LegsMovingAround)
        {
            Logger::WriteMessage("player0LegsMovingAround");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/legs/legsMovingAround", "player0LegsMovingAround", 15);
        }

        TEST_METHOD(player0LegsNot)
        {
            Logger::WriteMessage("player0LegsNot");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerComponents/legs/legsNot", "player0LegsNot", 1);
        }

        TEST_METHOD(player0Dead)
        {
            Logger::WriteMessage("player0Dead");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerDead/player0Dead", "player0Dead", 1);
        }

        TEST_METHOD(player1Dead)
        {
            Logger::WriteMessage("player1Dead");
            TestFlipbookFunc("../../../Apocalypse/resources/animations/playerDead/player1Dead", "player1Dead", 1);
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

        void TestFlipbookFunc(const std::string& resourcePath, const std::string& flipbookName, int numFrames)
        {
            try
            {
                ResourceManager::loadFlipbook(resourcePath.c_str(), 15.0, true, flipbookName);

                Assert::AreEqual(numFrames, ResourceManager::getFlipbook(flipbookName).getNumFrames());

                for (int i = 0; i < ResourceManager::getFlipbook(flipbookName).getNumFrames(); i++)
                {
                    Assert::AreEqual(128u, ResourceManager::getFlipbook(flipbookName).getTextureAtIndex(i).width); // 128
                    Assert::AreEqual(128u, ResourceManager::getFlipbook(flipbookName).getTextureAtIndex(i).height); // 128
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
    };
}

