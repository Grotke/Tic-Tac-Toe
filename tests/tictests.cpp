#include "gtest/gtest.h"
#include "ai.h"
#include <iostream>

TEST(AITest, identifyWin)
{
	AI ticAI = AI();	
	EXPECT_TRUE(ticAI.isEnemyWinPossible(0x123,0xD0,0x54));
	EXPECT_FALSE(ticAI.isEnemyWinPossible(0x127,0xC0,0x54));
	EXPECT_EQ(ticAI.findDistanceFromWin(0xC0, 0x54), 2);
}

TEST(AITest, findEditDistance)
{
	AI ticAI = AI();
	EXPECT_EQ(ticAI.findDistanceFromWin(0xD0,0x54), 1);
	EXPECT_EQ(ticAI.findDistanceFromWin(0xD0,0x1FF),0);
	EXPECT_EQ(ticAI.findDistanceFromWin(0x1FF,0x1FF),-6);

}

TEST(AITest, testEvaluation)
{
	AI ticAI = AI();
	unsigned int winStates[8] = {0x7,0x38,0x1C0,0x49,0x92,0x124,0x111,0x54};
	EXPECT_EQ(ticAI.evaluateMove(0x10,0x00,winStates,8),0);
	EXPECT_EQ(ticAI.evaluateMove(0x24,0x110,winStates,8),-1);
	EXPECT_EQ(ticAI.evaluateMove(0x92,0x24,winStates,8),1);	

}

TEST(AITest, movePrediction)
{		/*typedef struct AIData
		{
			unsigned int playerState;
			int aiScore;
		} AIData;*/
	
	AI ticAI = AI();
	unsigned int winStates[8] = {0x7,0x38,0x1C0,0x49,0x92,0x124,0x111,0x54};
	AI::AIData newData = ticAI.minimax(0x42,0xC8,winStates,8);
	EXPECT_EQ(newData.playerState,0x43);
	newData = ticAI.minimax(0x100,0x30,winStates, 8);
	EXPECT_EQ(newData.playerState, 0x108);
	newData = ticAI.minimax(0xE2,0x11C,winStates,8);
	EXPECT_EQ(newData.playerState, 0xE3);
}
