#include <iostream>
#include <random>
#include <time.h>

class Player
{
public:
	Player();
	Player(int number);
	Player(int number, int agility, int fearlessness);
	~Player() {};
	virtual bool act() { return true; };
	virtual bool isPlaying() { return playing; };
	void notPlaying() { playing = false; };
	unsigned int gettotaldistance(){ return total_distance; }
	int _choice[5]; // 다른 곳에 있으면 접근이 불가능해서 만듦
	int _answer[5]; // .. 리터럴로 쓰면 안되지만 변수로 사용하려고 많은 시간 시도했으나 접근이 안되거나 객체를 생성해야되서 못했습니다.
	void aliveMessage() { printStatus(); std::cout << " is alive." << std::endl; };
	virtual void dyingMessage() { printStatus(); std::cout << " died." << std::endl; };
	virtual void escapeMessage() { printStatus(); std::cout << "safely escaped from the groud" << std::endl; }
	virtual void printStatus() { std::cout << "Player #" << number << "(" << agility << "," << fearlessness << ")"; };
protected:
	unsigned int number;
	unsigned int agility;
	unsigned int fearlessness;
	unsigned int total_distance = 0;
	bool playing = true;
	static std::default_random_engine random_engine;
	static std::uniform_int_distribution<unsigned int> ability_range;
	static std::uniform_real_distribution<float> possibility;
};



class PlayerRLGL : public Player
{
	static float fallDownRate;
	unsigned int current_distance = 0;
	unsigned int total_distance = 0;
public:
	PlayerRLGL(const Player& player) : Player(player) { playing = true; };
	bool act();
	void dyingMessage();
	void escapeMessage();
};

class PlayerRPS : public Player
{
public:
	PlayerRPS(const Player& player) : Player(player) {  };
	bool act();
	void dyingMessage();
};

class PlayerSS : public Player
{
	int choice[5]; // 선택 랜덤으로 player가 선택함
	public:
	int answer[5]; // 정답지 1(오른쪽) 0(왼쪽) 징검다리 건너기
	PlayerSS(const Player& player) : Player(player) { };
	bool act();
	void dyingMessage();
};