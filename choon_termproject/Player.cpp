#include "Player.h"
#include "Game.h"

std::default_random_engine Player::random_engine(time(nullptr));
std::uniform_int_distribution<unsigned int> Player::ability_range(0, 100);
std::uniform_real_distribution<float> Player::possibility(0.f, 1.f);

float PlayerRLGL::fallDownRate = 0.1f;

Player::Player(int number)
{
	this->number = number;

	agility = ability_range(random_engine);
	fearlessness = ability_range(random_engine);
}

Player::Player(int number, int agility, int fearlessness)
{
	this->number = number;
	this->agility = agility;
	this->fearlessness = fearlessness;
}





bool PlayerRLGL::act()
{
	std::uniform_int_distribution<int> random1(0, 10); // for random_distance
	std::uniform_int_distribution<int> random2(0, 100);
	int random_distance = random1(random_engine);
	int fearlessbonus_distance;
	int random_bonus = random2(random_engine);
	int random_number = random2(random_engine);
	if (random_bonus <= fearlessness && random_number <= (int)RedLightGreenLight::fallDownRate * 100) 
		// fearlessness가 클수록 if문의 조건을 만족할 확률 증가// 25%의 확률 fallDownRate 1%이하 숫자 무시
		return false;
	else if(random_bonus <= fearlessness && random_number > (int)RedLightGreenLight::fallDownRate * 100)
	{
		fearlessbonus_distance = agility * (fearlessness * 0.01);
		this->current_distance = agility + random_distance + fearlessbonus_distance;
		Player::total_distance += this->current_distance;
		return true;
	}
	else 
	{
		fearlessbonus_distance = 0;
		this->current_distance = agility + random_distance + fearlessbonus_distance;
		Player::total_distance += this->current_distance;
	}
}

void PlayerRLGL::dyingMessage()
{ 
	if (isPlaying())
	{
		printStatus();
		std::cout << " is still on the ground and died." << std::endl;
	}
		
	else
	{
		printStatus();
		std::cout << " fell down and died." << std::endl;
	}
};
void PlayerRLGL::escapeMessage()
{
		printStatus();
		std::cout << " safely escaped from the ground." << std::endl;
}





bool PlayerRPS::act()
{
	enum rpsType { Rock, Paper, Scissors };
	auto rps = [] {
		float p = possibility(random_engine);

		if (p < float(1.f / 3.f))
			return rpsType::Rock;
		else if (p < float(2.f / 3.f))
			return rpsType::Paper;
		else
			return  rpsType::Scissors;
	};

	rpsType myRPS, yourRPS;
	do {
		myRPS = rps();
		yourRPS = rps();
	}
	while(myRPS == yourRPS);
	
	if (myRPS == Rock)
	{
		if (yourRPS == Paper)
			return false;
		else
			return true;
	}
	else if (myRPS == Paper)
	{
		if (yourRPS == Scissors)
			return false;
		else
			return true;
	}
	else
	{
		if (yourRPS == Rock)
			return false;
		else
			return true;
	}
}


void PlayerRPS::dyingMessage()
{
	printStatus();
	std::cout << " died." << std::endl;
};

bool PlayerSS::act()
{
	std::uniform_int_distribution<int> random(0, 1);
	
	for (int i = 0; i < 5; i++)
	{
		choice[i] = random(random_engine); //같은 랜덤함수 사용해야지 같은 숫자라고 인식함 답지를 다른 class에 둘 수 없었음
		answer[i] = random(random_engine);
	}
	for (int i = 0; i < 5 ; i++)//sizeof(choice) / sizeof(int); i++)
	{
		choice[i] = _choice[i]; //답지와 선택이 모두 같을 때만 생존하는 것으로 설계 + fearlessness가 50 초과이어야 함
		answer[i] = _answer[i];
	}
	if (agility + fearlessness >= 120) // agility + fearlessness가 120이하인 경우 도전 포기하거나 떨어짐
		return true;
	else 
		return false;
}
void PlayerSS::dyingMessage()
{
	printStatus();
	std::cout << " died." << std::endl;
}