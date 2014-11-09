#include "ai.h"
#include <vector>
#include <iostream>

AI::AI()
{

}


AI::~AI()
{


}

int AI::evaluateMove(unsigned int currentPlayerMap, unsigned int enemyPlayerMap, unsigned int winStates[],int numberOfWinStates)
{
	for(int i = 0; i < numberOfWinStates; i++)
	{
		if(findDistanceFromWin(currentPlayerMap,winStates[i]) == 0)
		{
			return 1;
		}
		else if(findDistanceFromWin(enemyPlayerMap,winStates[i]) == 1 && isEnemyWinPossible(currentPlayerMap, enemyPlayerMap, winStates[i]))
		{
			return -1;
		}
	}

	return 0;
}

bool AI::isEnemyWinPossible(unsigned int currentPlayerMap, unsigned int enemyPlayerMap, unsigned int winState)
{
	unsigned int freeSpots = getFreeSpots(currentPlayerMap, enemyPlayerMap);
	return ((enemyPlayerMap | freeSpots) & winState) == winState;
}

int AI::findDistanceFromWin(unsigned int playerMap, unsigned int winState)
{
	int closenessToWin = 0, distanceFromWin;
	unsigned int mapToWin = playerMap & winState;

	for(int i = 0; i < numberOfBoardPositions; i++)
	{		
		closenessToWin += (mapToWin >> i) & 0x1;
	}

	distanceFromWin = 3 - closenessToWin;

	return distanceFromWin;
}

AI::AIData AI::minimax(unsigned int currentPlayerMap, unsigned int enemyPlayerMap, unsigned int winStates[], int numOfWinStates)
{
	int moveValue;
	int highestMoveValue = -8000;
	AIData returnMoveData, moveData;
	int bestScore = -8000;
	unsigned int bestMove = 0;

	std::vector<AIData> goodMoves;
	std::vector<unsigned int>* possibleMoves = produceMoves(currentPlayerMap, enemyPlayerMap);
	for(std::vector<unsigned int>::iterator iter = possibleMoves->begin(); iter != possibleMoves->end(); iter++)
	{
		moveValue = evaluateMove(*iter, enemyPlayerMap, winStates, numOfWinStates);
		AIData holdMoveData;
		holdMoveData.aiScore = moveValue;
		holdMoveData.playerState = *iter;
		if(moveValue > highestMoveValue)
		{
			goodMoves.erase(goodMoves.begin(), goodMoves.end());
			goodMoves.push_back(holdMoveData);
			highestMoveValue = moveValue;
			bestMove = *iter;
			bestScore = highestMoveValue;
		} 
		else if(moveValue == highestMoveValue)
		{
			goodMoves.push_back(holdMoveData);
		}		
	}

	if(highestMoveValue == 0)
	{
		for(std::vector<AIData>::iterator iter = goodMoves.begin(); iter != goodMoves.end(); iter++)
		{
			returnMoveData = minimax(enemyPlayerMap, iter->playerState, winStates, numOfWinStates);
			if(returnMoveData.aiScore > bestScore)
			{
				bestScore = returnMoveData.aiScore;
				bestMove = returnMoveData.playerState;
			}		
		}
	}
	else if (highestMoveValue != -8000){
		bestScore = goodMoves.begin()->aiScore;
		bestMove = goodMoves.begin()->playerState;
	}
	else{
		bestScore = 0;
		bestMove = currentPlayerMap;
	}
	
	moveData.aiScore = bestScore;
	moveData.playerState = bestMove;	
	delete possibleMoves;

	return moveData;
}

unsigned int AI::getFreeSpots(unsigned int currentPlayerMap, unsigned int enemyPlayerMap)
{
	return (currentPlayerMap | enemyPlayerMap) ^ 0x1FF;
}

std::vector<unsigned int> * AI::produceMoves(unsigned int currentPlayerMap, unsigned int enemyPlayerMap)
{
	std::vector<unsigned int> *possibleMoves = new std::vector<unsigned int>;
	unsigned int freeSpots = getFreeSpots(currentPlayerMap, enemyPlayerMap);
	for(int i = 0; i < numberOfBoardPositions; i++)
	{
		if(freeSpots & (0x1 << i))
		{
			possibleMoves->push_back(currentPlayerMap | (0x1 << i));
		}
	}

	return possibleMoves;
}


