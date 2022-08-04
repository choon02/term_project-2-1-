#include <string>
#include <list>
#include <vector>
class Player;

class Game
{
protected:
	std::string gameName;
	std::list<Player*> players;
	virtual void printGameName();
public:
	Game(std::string name) :gameName(name) {};
	~Game();
	virtual void join(Player* player) = 0;
	virtual void play() = 0;
	void printAlivePlayers();
	std::list<Player*> getAlivePlayers() { return players; };
	
	//Player* operator[](int index) { return players[index]; };
};





class RedLightGreenLight : public Game
{
	friend class PlayerRLGL;

	static const unsigned int distance;
	static const float fallDownRate;
	
	const unsigned int turn = 20;
public:
	RedLightGreenLight() : Game("Red Light Green Light") {};
	RedLightGreenLight(int t) : Game("Red Light Green Light"), turn(t) {};
	~RedLightGreenLight() {};
	void join(Player* player);
	void play();
};





class RPS : public Game
{
	friend class PlayerRPS;

public:
	RPS() : Game("Rock Paper Scissors") {};
	~RPS() {};
	void join(Player* player);
	void play();
};

class SteppingStone : public Game
{
	friend class PlayerSS;
	const unsigned int howmanytimes = 5; // 5번 건너야 함
public:
	SteppingStone() : Game("Crossing stepping stone") {};
	~SteppingStone() {};
	void join(Player* player);
	void play();

};