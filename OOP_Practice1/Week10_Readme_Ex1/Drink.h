#pragma once
class Drink
{
public:
	Drink() = default;
	Drink(const char* name, int ml);
	Drink(const Drink& other);
	Drink(Drink&& other) noexcept;

	Drink& operator=(const Drink& other);
	Drink& operator=(Drink&& other) noexcept;

	const char* getName() const;
	const int getMl() const;

	void setName(const char* name);
	void setMl(int ml);

	~Drink();

private:
	char* _name = nullptr;
	int _ml = 0;
	void copyFrom(const Drink& other);
	void moveFrom(Drink&& other);
	void free();
	bool isValidName(const char* name);
};