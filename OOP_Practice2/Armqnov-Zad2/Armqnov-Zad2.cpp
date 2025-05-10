#include <iostream>
#include <fstream>
#pragma warning (disable:4996)

struct Egg
{
    char name[128];
    unsigned short size;

    Egg() : size(0)
    {
        name[0] = '\0';
    }

    Egg(char* id, unsigned short size) : size(size)
    {
        if (!id || id[0] == '\0')
            throw std::invalid_argument("id null or empty");

        strncpy(name, id, 127);
        name[127] = '\0';
    }
};

class EggBasket
{
    char ownerName[101];
    Egg* eggs = nullptr;
    size_t eggsCount = 0;
    size_t eggsCap = 8;
    size_t currentSize = 0;
    size_t maximumSize = 0;

    void copyFrom(const EggBasket& other)
    {
        strncpy(ownerName, other.ownerName, 100);
        ownerName[100] = '\0';

        eggs = new (std::nothrow) Egg[other.eggsCap];
        if (!eggs)
            throw std::bad_alloc();

        for (int i = 0; i < other.eggsCount; i++)
        {
            eggs[i] = other.eggs[i];
        }

        eggsCap = other.eggsCap;
        eggsCount = other.eggsCount;
        currentSize = other.currentSize;
        maximumSize = other.maximumSize;
    }

    void free()
    {
        delete[] eggs;
    }

    void resize()
    {
        Egg* newEggs = new Egg[eggsCap * 2];
        for (int i = 0; i < eggsCount; i++)
        {
            newEggs[i] = eggs[i];
        }

        delete[] eggs;
        eggs = newEggs;
    }

public:
    EggBasket()
    {
        eggs = new Egg[eggsCap];
    }

    EggBasket(const EggBasket& other)
    {
        copyFrom(other);
    }

    EggBasket(char* ownerName, Egg* eggs, size_t maxSize, size_t countEggs)
    {
        if (!ownerName || !eggs)
            throw std::invalid_argument("nullptr name or eggs");
        strncpy(this->ownerName, ownerName, 100);

        this->ownerName[100] = '\0';
        this->maximumSize = maxSize;   
        this->eggs = new Egg[countEggs];

        for (int i = 0; i < countEggs; i++)
        {
            addEgg(eggs[i].name, eggs[i].size);
        }
    }

    friend void serializeBasket(char* fName, const EggBasket& basket);

    friend void deserializeBasket(char* fName, EggBasket& basket);

    friend void report(const EggBasket& basket);

    EggBasket& operator=(const EggBasket& other)
    {
        if (this != &other)
        {
            EggBasket copy(other);
            std::swap(eggs, copy.eggs);
            std::swap(ownerName, copy.ownerName);
            std::swap(eggsCap, copy.eggsCap);
            std::swap(eggsCount, copy.eggsCount);
            std::swap(currentSize, copy.currentSize);
            std::swap(maximumSize, copy.maximumSize);
        }
        return *this;
    }

    ~EggBasket()
    {
        free();
    }

    void addEgg(char* name, unsigned short size)
    {
        if (!name || name[0] == '\0')
            throw std::invalid_argument("nullptr or empty name");

        Egg newEgg = Egg(name, size);
        if (currentSize + size > maximumSize || eggsCount == eggsCap)
        {
           resize();            
        }     

        eggs[eggsCount++] = newEgg;
        currentSize += size;
    }

    void removeEgg(char* name)
    {
        for (int i = 0; i < eggsCount; i++)
        {
            if (strcmp(eggs[i].name,name) == 0)
            {
                currentSize -= eggs[i].size;
                std::swap(eggs[i], eggs[eggsCount - 1]);
                eggsCount--;
                break;
            }
        }
    }


};

void serializeBasket(char* fName, const EggBasket& basket)
{
    if (!fName || fName[0] == '\0')
        throw std::invalid_argument("file name empty or null");

    std::ofstream ofs(fName, std::ios::binary);

    if (!ofs.is_open())
    {
        throw std::runtime_error("File was unable to open");
    }   

    ofs.write((const char*)basket.ownerName, sizeof(basket.ownerName));

    ofs.write((const char*)&basket.eggsCap, sizeof(basket.eggsCap));

    ofs.write((const char*)&basket.eggsCount, sizeof(basket.eggsCount));

    ofs.write((const char*)basket.eggs, sizeof(Egg) * basket.eggsCount);

    ofs.write((const char*)&basket.currentSize, sizeof(basket.currentSize));

    ofs.write((const char*)&basket.maximumSize, sizeof(basket.maximumSize));
}

void deserializeBasket(char* fName, EggBasket& basket)
{
    if (!fName || fName[0] == '\0')
        throw std::invalid_argument("file name empty or null");

    std::ifstream ifs(fName, std::ios::binary);

    if (!ifs.is_open())
    {
        throw std::runtime_error("File was unable to open");
    }

    ifs.read(basket.ownerName, sizeof(basket.ownerName));
    basket.ownerName[100] = '\0';

    ifs.read((char*)&basket.eggsCap, sizeof(basket.eggsCap));

    basket.eggs = new Egg[basket.eggsCap];

    ifs.read((char*)&basket.eggsCount, sizeof(basket.eggsCount));

    ifs.read((char*)basket.eggs, sizeof(Egg) * basket.eggsCount);

    ifs.read((char*)&basket.currentSize, sizeof(basket.currentSize));

    ifs.read((char*)&basket.maximumSize, sizeof(basket.maximumSize));
}

void report(const EggBasket& basket)
{
    size_t nameSize = 7 + strlen(basket.ownerName) + 1;
    char* fileName = new char[nameSize];

    strcpy(fileName, "report_");
    strcat(fileName, basket.ownerName);
    strcat(fileName, ".txt");

    std::ofstream ofs(fileName);

    if (!ofs.is_open())
    {
        throw std::runtime_error("Report file not open");
    }

    for (int i = 0; i < basket.eggsCount; i++)
    {
        ofs << "Egg " << i << ": " << "name: " << basket.eggs[i].name
            << ", size: " << basket.eggs[i].size << std::endl;
    }
}

void runTests()
{
    Egg eggs[3] = {
        Egg((char*)"Red", 10),
        Egg((char*)"Blue", 20),
        Egg((char*)"Green", 30)
    };

    EggBasket basket((char*)"stavri", eggs, 100, 3);
    serializeBasket((char*)"basket.bin", basket);

    EggBasket loaded;
    deserializeBasket((char*)"basket.bin", loaded);

    report(loaded);
    std::cout << "Test completed.\n";
}

int main()
{
    runTests();
}