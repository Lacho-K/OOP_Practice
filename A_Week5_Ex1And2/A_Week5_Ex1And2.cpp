#include <iostream>

struct Date
{
    unsigned day;
    unsigned month;
    unsigned year;
};

class Event
{
    char name[20];
    Date date;
    unsigned startHour;
    unsigned endHour;

public:

    const char* getName() const 
    {
        return this->name;
    }

    const Date getDate() const
    {
        return this->date;
    }

    const unsigned getStartHour() const
    {
        return this->startHour;
    }
    
    const unsigned getEndHour() const
    {
        return this->endHour;
    }

    void setName(const char* newName)
    {
        strcpy(this->name, newName);
    }

    void setDate(const Date& newDate)
    {
        this->date = newDate;
    }

    void setStartHour(const unsigned newStartHour)
    {
        this->startHour = newStartHour;
    }
    
    void setEndHour(const unsigned newEndHour)
    {
        this->endHour = newEndHour;
    }

    int getDuration() const
    {
        return (int)this->endHour - (int)this->startHour;
    }

};

class EventCollection
{
    Event events[20];
    unsigned eventCount = 0;

public:

    void addEvent(const Event& newEvent)
    {
        events[eventCount++] = newEvent;
    }

    Event& findLongestEvent() const 
    {
        int biggestDuration = INT_MIN;
        for (size_t i = 0; i < eventCount; i++)
        {
            int currentDuration = events[i].getDuration();
            if(currentDuration > biggestDuration)
            {
                biggestDuration = currentDuration;
            }
        }
    }
};

int main()
{
    std::cout << "Hello World!\n";
}