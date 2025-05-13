#pragma once

enum class Weapons
{
	SWORD,
	WAND,
	STAFF,
	AXE
};

class Player
{
protected:
	unsigned health = 0;
private:
	char* name = nullptr;

	struct Point {
		int x;
		int y;
		Point() :x(0), y(0) {};
		Point(int x, int y) :x(x), y(y) {};
		bool areAdjacent(const Point& other) const;
	} position;

	Weapons weapon;

	unsigned attackDamage = (unsigned)weapon;

	void copyDynamic(const Player& other);

	void copyFrom(const Player& other);

	void stealData(Player&& other) noexcept;

	const char* weaponToStr() const;

	void free();

public:

	void move(int offsetX, int offsetY);

	virtual void handleAttack(const Player& attacker);

	virtual void attack(Player& attacked);

	virtual void print() const;

	virtual Player* clone() const = 0;

	unsigned getAttackPower() const;

	void setAttackPower(unsigned attackPower);

	bool isAlive() const;

	const char* getName() const;

	Player() = default;
	Player(unsigned health, const char* name, Weapons weapon, unsigned attackDamage);
	Player(const Player& other);
	Player(Player&& other) noexcept;

	//не може да променяме името след създаване(по условие)
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;

	virtual ~Player();
};