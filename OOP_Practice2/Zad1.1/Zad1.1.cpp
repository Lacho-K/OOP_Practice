#include "PlayerCollection.h"
#include "Warrior.h"
#include "Mag.h"
#include "Necromancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(std::time(nullptr));

    PlayerCollection collection;
    Player* warrior = new Warrior(50, 100, "Kratos", Weapons::SWORD, 30);
    Player* mage = new Mag("Fire", 0.3, 90, "Gandalf", Weapons::WAND, 20);
    Player* necro = new Necromancer("Fire", 0.3, 90, "Gosho", Weapons::WAND, 20);

    collection.add(warrior);
    collection.add(mage);
    collection.add(necro); // по подразбиране
    collection.getAt(2)->move(2, 0);    // за да са на различни позиции

    size_t i = 0;
    while (i < collection.getSize())
    {
        Player* attacker = collection.getAt(i);
        size_t j = i + 1;

        while (j < collection.getSize())
        {
            Player* defender = collection.getAt(j);

            if (!attacker->isAlive())
            {
                collection.remove(attacker->getName());
                if (i >= collection.getSize()) break;
                attacker = collection.getAt(i);
                j = i + 1;
                continue;
            }

            if (!defender->isAlive())
            {
                collection.remove(defender->getName());
                continue; // j stays same because elements shifted
            }

            attacker->attack(*defender);

            if (!defender->isAlive())
            {
                collection.remove(defender->getName());
                continue;
            }

            j++;
        }

        if (!attacker->isAlive())
        {
            collection.remove(attacker->getName());
            continue;
        }

        i++;
    }

    std::cout << "\nSurvivors:\n";
    for (size_t i = 0; i < collection.getSize(); i++)
    {
        collection[i]->print();
        std::cout << "-----------------------\n";
    }

    return 0;
}
