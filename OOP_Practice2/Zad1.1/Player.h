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
	unsigned health = 0;
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

	virtual void handleAttack(unsigned receivedDamage) = 0;

	virtual void attack(Player& attacked) = 0;

	virtual void print() const;

	unsigned getAttackPower() const;

	void setAttackPower(unsigned attackPower);

	Player() = default;
	Player(unsigned health, const char* name, Weapons weapon, unsigned attackDamage);
	Player(const Player& other);
	Player(Player&& other);

	//не може да променяме името след създаване(по условие)
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;

	virtual ~Player();
};