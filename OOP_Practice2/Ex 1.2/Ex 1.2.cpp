#include <iostream>

enum Color
{
    BROWN,
    GREEN,
    ORANGE,
    RED,
    YELLOW
};

enum YN
{
    NO,
    YES
};


struct Fruit
{
    char name[32];
    Color cl;
    YN annual;
    YN perennial;
    YN tropical;
};

int compareName(const Fruit& f1, const Fruit& f2)
{
    return std::strcmp(f1.name, f2.name);
}

int compareColor(const Fruit& f1, const Fruit& f2)
{
    return f1.cl > f2.cl;
}

int comparePerennial(const Fruit& f1, const Fruit& f2)
{
    return f1.perennial > f2.perennial;
}

void sortFruits(Fruit*& fruits, size_t count, int(*comp)(const Fruit& f1, const Fruit& f2))
{
    for (int i = 1; i < count; i++)
    {
        Fruit currFruit = fruits[i];
        int ind = i - 1;
        while (ind >= 0 && comp(fruits[ind], currFruit))
        {
            fruits[ind + 1] = fruits[ind];
            ind--;
        }
        fruits[ind + 1] = currFruit;    
    }
}

int getFilteredCount(Fruit* fruits, Color tgColor, size_t count)
{
    int counter = 0;
    for (size_t i = 0; i < count; i++)
    {
        if (fruits[i].perennial && fruits[i].cl == tgColor)
            counter++;
    }
    return counter;
}

Fruit* filterFruits(Fruit* fruits, Color tgColor, size_t count)
{
    Fruit* filtered = new Fruit[getFilteredCount(fruits, tgColor, count)];
    int filterInd = 0;
    for (size_t i = 0; i < count; i++)
    {
        if (fruits[i].perennial && fruits[i].cl == tgColor)
            filtered[filterInd++] = fruits[i];
    }
    return filtered;
}

// TODO: DEBUG!!!
Fruit* filterAndSort(Fruit*& fruits, Color targetColor, 
    size_t count, int (*comp)(const Fruit& f1, const Fruit& f2))
{
    Fruit* filtered = filterFruits(fruits, targetColor, count);
    int filteredCount = getFilteredCount(fruits, targetColor, count);
    delete[] fruits;
    fruits = filtered;

    for (int i = 1; i < filteredCount; i++)
    {
        Fruit currFruit = fruits[i];
        int ind = i - 1;
        while (ind >= 0 && !comp(fruits[ind], currFruit))
        {
            fruits[ind + 1] = fruits[ind];
            ind--;
        }
        fruits[ind + 1] = currFruit;
    }

    return fruits;
}

Fruit* createFruits(size_t count)
{
    Fruit* fruits = new Fruit[count];

    for (size_t i = 0; i < count; i++)
    {
        std::cin >> fruits[i].name;
        int n;
        std::cin >> n;
        fruits[i].cl = (Color)n;
        std::cin >> n;
        fruits[i].annual = (YN)n;
        std::cin >> n;
        fruits[i].perennial = (YN)n;
        std::cin >> n;
        fruits[i].tropical = (YN)n;
        std::cout << std::endl << std::endl;
    }

    return fruits;

}

void printFruit(const Fruit& f)
{
    std::cout << f.name << " " << f.cl << " " << f.annual << " " 
        << f.perennial << " " << f.tropical << std::endl;
}

int main()
{
    Fruit* fruits = createFruits(3);
    /*std::cout << "Before sort: " << std::endl;
    for (size_t i = 0; i < 3; i++)
    {
        printFruit(fruits[i]);
    }
    
    std::cout << "After sort by name: " << std::endl;

    sortFruits(fruits, 3, compareName);

    for (size_t i = 0; i < 3; i++)
    {
        printFruit(fruits[i]);
    }
    
    std::cout << "After sort by color: " << std::endl;

    sortFruits(fruits, 3, compareColor);

    for (size_t i = 0; i < 3; i++)
    {
        printFruit(fruits[i]);
    }*/


    std::cout << "Before sort and filter: " << std::endl;
    for (size_t i = 0; i < 3; i++)
    {
        printFruit(fruits[i]);
    }

    int filteredCount = getFilteredCount(fruits, GREEN, 3);
    filterAndSort(fruits, GREEN, 3, compareName);
    std::cout << "After sort and filter: " << std::endl;
    for (size_t i = 0; i < filteredCount; i++)
    {
        printFruit(fruits[i]);
    }

    delete[] fruits;
}