#include <vector>

#ifndef AI_H_
#define AI_H_
class AI
{
	public:	
		typedef struct AIData
		{
			unsigned int playerState;
			int aiScore;
		} AIData;
		AI();
		~AI();
		int evaluateMove(unsigned int currentPlayerMap, unsigned int enemyPlayerMap, unsigned int winStates[], int numberOfWinStates); 
		bool isEnemyWinPossible(unsigned int currentPlayerMap, unsigned int enemyPlayerMap, unsigned int winState);
		int findDistanceFromWin(unsigned int playerMap, unsigned int winState);
		AIData minimax(unsigned int currentPlayerMap, unsigned int enemyPlayerMap, unsigned int winStates[], int numOfWinStates);
		unsigned int getFreeSpots(unsigned int currentPlayerMap, unsigned int enemyPlayerMap);
		std::vector<unsigned int> * produceMoves(unsigned int currentPlayerMap, unsigned int enemyPlayerMap);

	private:
		const static int numberOfBoardPositions = 9;
	/*	typedef struct AIData
		{
			unsigned int playerState;
			int aiScore;
		} AIData;*/
};

#endif
