#pragma once
#include "Player.h"
#pragma warning (disable:4996)

class PlayerCollection
{
    Player** players = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void resize();
    void copyFrom(const PlayerCollection& other);
    void free();

public:
    PlayerCollection();
    PlayerCollection(const PlayerCollection& other);
    PlayerCollection& operator=(const PlayerCollection& other);
    ~PlayerCollection();

    void add(Player* p);
    const Player* operator[](size_t index) const;
    Player* getAt(size_t index);
    size_t getSize() const;
    void remove(const char* name);
};
