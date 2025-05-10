#pragma once
class Player
{
	unsigned health = 1;
	char* name = nullptr;

	struct Point {
		int x;
		int y;
		Point() :x(0), y(0) {};
		Point(int x, int y) :x(x), y(y) {};
		bool areAdjacent(const Point& other) const;
	} position;

	enum class Weapons
	{
		SWORD,
		WAND,
		STAFF,
		AXE
	} weapon;

	unsigned attackDamage = (unsigned)weapon;

	void copyDynamic(const Player& other);

	void copyFrom(const Player& other);

	void stealData(Player&& other) noexcept;

	void swapData(Player& other) noexcept;

	void free();

public:

	void move(int offsetX, int offsetY);

	virtual void handleAttack(const Player& attacker) = 0;

	virtual void attack(Player& attacked) = 0;

	unsigned getAttackPower() const;

	void setAttackPower(unsigned attackPower);

	Player() = default;
	Player(const Player& other);
	Player(Player&& other);

	Player& operator=(const Player& other);
	Player& operator=(Player&& other);

	virtual ~Player();
};