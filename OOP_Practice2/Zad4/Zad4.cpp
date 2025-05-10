#include <iostream>
#include <fstream>
#pragma warning (disable:4996)

struct Car
{
    char name[23];
    unsigned short id;
    unsigned short power;
};

struct Owner
{
    char name[23];
    unsigned carId;
    unsigned totalPower;

    Owner() : name("\0"), carId(0), totalPower(0) {}

    Owner(char* name, unsigned carId, unsigned totalPower)
    {
        if (!name || name[0] == '\0')
            throw std::invalid_argument("name null or empty");

        strcpy(this->name, name);
        this->carId = carId;
        this->totalPower = totalPower;
    }
};

class Database
{
    Owner* owners;
    unsigned short* regNumbers;
    size_t count;
    size_t cap;

    static const Car cars[4];

    void copyFrom(const Database& other)
    {
        owners = new (std::nothrow) Owner[other.cap];
        regNumbers = new (std::nothrow) unsigned short[other.cap];        

        if (!owners || !regNumbers)
            throw std::bad_alloc();

        cap = other.cap;

        for (size_t i = 0; i < other.count; i++)
        {
            owners[i] = other.owners[i];
            regNumbers[i] = other.regNumbers[i];
        }

        count = other.count;
    }

    void free()
    {
        delete[] owners;
        delete[] regNumbers;
    }

    void resize()
    {
        cap *= 2;
        Owner* newOwners = new Owner[cap];
        unsigned short* newRegNums = new unsigned short[cap];

        for (int i = 0; i < count; i++)
        {
            newOwners[i] = owners[i];
            newRegNums[i] = regNumbers[i];
        }

        free();

        owners = newOwners;
        regNumbers = newRegNums;
    }

    bool isDuplicate(unsigned short regNum) const
    {
        for (int i = 0; i < count; i++)
        {
            if (regNumbers[i] == regNum)
                return true;
        }

        return false;
    }

    const Car& getMostFamousCar() const
    {
        unsigned short idsCounter[4]{};

        for (int i = 0; i < count; i++)
        {
            switch (owners[i].carId)
            {
                case 0:
                    idsCounter[0]++;
                    break;
                case 1:
                    idsCounter[1]++;
                    break;
                case 2:
                    idsCounter[2]++;
                    break;
                case 3:
                    idsCounter[3]++;
                    break;
                default:
                    break;
            }
        }

        int maxIndex = 0;
        for (int i = 0; i < 3; i++)
        {
            if (idsCounter[i] > idsCounter[i + 1])
                maxIndex = i;
        }

        return cars[maxIndex];       
    }

    unsigned getAveragePower() const
    {
        unsigned total = 0;

        for (size_t i = 0; i < count; i++)
        {
            total += cars[owners[i].carId].power;
        }

        return total / count;
    }

    int getOwnerInd(char* name)
    {
        for (int i = 0; i < count; i++)
        {
            if (strcmp(owners[i].name, name) == 0)
            {
                return i;
            }
        }

        return -1;
    }

public:

    Database() : count(0), cap(8), owners(new Owner[cap])
        , regNumbers(new unsigned short[cap]) {}

    Database(const Database& other)
    {
        copyFrom(other);
    }

    Database& operator=(const Database& other)
    {
        if (this != &other)
        {
            Database copy(other);
            std::swap(owners, copy.owners);
            count = copy.count;
            cap = copy.cap;
        }

        return *this;
    }

    ~Database()
    {
        free();
    }

    void addOwner(char* name, unsigned short regNo, unsigned short carId)
    {
        if (isDuplicate(regNo))
            throw std::invalid_argument("reg number already exists in database!");

        if (count == cap)
            resize();

        int ownerInd = getOwnerInd(name);

        if (ownerInd != -1)
        {
            owners[ownerInd].totalPower += cars[carId].power;
        }
        else
        {
            owners[count] = Owner(name, carId, cars[carId].power);
            regNumbers[count] = regNo;
            count++;
        }
    }

    void generateReport()
    {
        std::ofstream ofs("car-report.txt");

        if (!ofs.is_open())
            throw std::runtime_error("ofstream not open");

        if (count == 0)
        {
            ofs << "No cars in database";
            return;
        }

        ofs << "Most popular car: " << getMostFamousCar().name << std::endl;
        ofs << "Average power: " << getAveragePower() << std::endl;

        for (int i = 0; i < count; i++)
        {
            ofs << "Owner: " << owners[i].name 
                << ", Total power: " << owners[i].totalPower << std::endl;
        }


    }

    //TODO: Serialize and deserialize

};

const Car Database::cars[4] =
{
    { "Lambordgini Murcielago", 0, 670 },
    { "Mercedes-AMG", 1, 503 },
    { "Pagani Zonda R", 2, 740 },
    { "Bugatti Veyron", 3, 1020 }
};

int main()
{
    std::cout << "Hello World!\n";
}