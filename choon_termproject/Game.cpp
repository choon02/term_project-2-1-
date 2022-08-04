#include <iostream>
#include "Game.h"
#include "Player.h"
#include <time.h>

Game::~Game()
{
	for (auto player = players.begin(); player != players.end(); ++player)
	{
		delete (*player);
	}
	players.clear();
}

void Game::printGameName()
{
	std::cout << "[[[" << gameName << "]]]" << std::endl;
}

void Game::printAlivePlayers()
{
	for (auto player = players.begin(); player != players.end(); ++player)
	{
		(*player)->aliveMessage();
	}
}



const unsigned int RedLightGreenLight::distance = 1000;
const float RedLightGreenLight::fallDownRate = 0.25f;



void RedLightGreenLight::join(Player* player)
{
	players.push_back(new PlayerRLGL(*player));
}

void RedLightGreenLight::play()
{
	printGameName();

	for (int t = 0; t < turn; ++t)
	{
		std::cout << "[turn#" << t + 1 << "]" << std::endl;
		auto player = players.begin();
		while (player != players.end())
		{
			if ((*player)->isPlaying()) {
				if ((*player)->act() && (*player)->gettotaldistance() > distance) // true일 경우 생존, distance 넘을 경우 게임 끝
				{
					(*player)->notPlaying();
					(*player)->escapeMessage();
					++player;
				}

				else if ((*player)->act() && (*player)->gettotaldistance() <= distance)
					++player;
				else // false일 경우 die
				{
					(*player)->notPlaying();
					(*player)->dyingMessage();
					delete (*player);
					player = players.erase(player);
				}
			}
			else {
				++player;
			}
			
		}
	}

	std::cout << "[Game Over]" << std::endl;

	auto player = players.begin();
	while (player != players.end())
	{
		if ((*player)->isPlaying())
		{
			(*player)->dyingMessage();
			delete (*player);
			player = players.erase(player);
		}
		else
		{
			++player;
		}
	}

	printAlivePlayers();

	std::cout << players.size() << " players are alive." << std::endl << std::endl;
}





void RPS::join(Player* player)
{
	players.push_back(new PlayerRPS(*player));
}

void RPS::play()
{
	printGameName();

	if (players.size() < 2)
	{
		std::cout << "There are not sufficient players.";
		return;
	}

	auto player = players.begin();
	
	while (player != players.end())
	{
		if ((*player)->act())
		{
			++player;
		}
		else
		{
			(*player)->dyingMessage();
			delete (*player);
			player = players.erase(player);
		}
	}

	printAlivePlayers();

	std::cout << players.size() << " players are alive." << std::endl << std::endl;
}



void SteppingStone::join(Player* player)
{
	players.push_back(new PlayerRPS(*player));
}

void SteppingStone::play()
{
	printGameName();
	
	// 정답지와 랜덤 선택 비교
	auto player = players.begin();
	while (player != players.end())
	{
		bool issame = true;
		for (int i = 0; i < 5; i++)
		{
			if ((*player)->_answer[i] != (*player)->_choice[i])
			{
				issame = false;
				break;
			}
			else
			{
				continue;
			}
		}
		if ((*player)->act() && issame) //  issame이 true이어야 생존
		{
			++player;
		}
		else
		{
			(*player)->dyingMessage();
			delete (*player);
			player = players.erase(player);
		}
	}
	std::cout << "[Game Over]" << std::endl;
	printAlivePlayers();
	std::cout << players.size() << " players are alive." << std::endl <<std::endl;
}
