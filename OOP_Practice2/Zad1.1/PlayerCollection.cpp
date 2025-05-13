#include "PlayerCollection.h"
#include <stdexcept>
#include <cstring>

PlayerCollection::PlayerCollection()
{
    capacity = 4;
    players = new Player * [capacity];
}

PlayerCollection::PlayerCollection(const PlayerCollection& other)
{
    copyFrom(other);
}

PlayerCollection& PlayerCollection::operator=(const PlayerCollection& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

PlayerCollection::~PlayerCollection()
{
    free();
}

void PlayerCollection::resize()
{
    Player** newArr = new Player * [capacity * 2];
    for (size_t i = 0; i < size; i++)
    {
        newArr[i] = players[i];
    }
    delete[] players;
    players = newArr;
    capacity *= 2;
}

void PlayerCollection::copyFrom(const PlayerCollection& other)
{
    players = new Player * [other.capacity];
    for (size_t i = 0; i < other.size; i++)
    {
        players[i] = other.players[i]->clone();
    }
    size = other.size;
    capacity = other.capacity;
}

void PlayerCollection::free()
{
    for (size_t i = 0; i < size; i++)
    {
        delete players[i];
    }
    delete[] players;
}

void PlayerCollection::add(Player* p)
{
    for (size_t i = 0; i < size; i++)
    {
        if (players[i]->getName() && p->getName()) {
            if (strcmp(players[i]->getName(), p->getName()) == 0)
            {
                throw std::invalid_argument("duplicate name");
            }
        }
    }

    if (size == capacity)
    {
        resize();
    }

    players[size++] = p;
}

const Player* PlayerCollection::operator[](size_t index) const
{
    if (index >= size)
    {
        throw std::out_of_range("invalid index");
    }
    return players[index];
}

Player* PlayerCollection::getAt(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("invalid index");
    }
    return players[index];
}

size_t PlayerCollection::getSize() const
{
    return size;
}

void PlayerCollection::remove(const char* name)
{
    for (size_t i = 0; i < size; i++)
    {
        if (strcmp(players[i]->getName(), name) == 0)
        {
            std::swap(players[i], players[size - 1]);
            delete players[size - 1];
            size--;
            return;
        }
    }
}
