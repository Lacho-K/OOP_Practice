#include <iostream>
#pragma warning(disable:4996)

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

    Event()
    {
        setName("");
        Date defaultDate = { 0,0,0 };
        setDate(defaultDate);
        setStartHour(0);
        setEndHour(0);
    }

    Event(const char* name, const Date& date, const unsigned startHour, const unsigned endHour)
    {
        setName(name);
        setDate(date);
        setStartHour(startHour);
        setEndHour(endHour);
    }

    Event(const Event& other)
    {
        setName(other.name);
        setDate(other.date);
        setStartHour(other.startHour);
        setEndHour(other.endHour);
    }

    Event& operator=(const Event& other)
    {
        setName(other.name);
        setDate(other.date);
        setStartHour(other.startHour);
        setEndHour(other.endHour);

        return (* this);
    }


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

    const int getDuration() const
    {
        return (int)this->endHour - (int)this->startHour;
    }

    const bool isNotIntersecting(const Event& other) const 
    {
        return (this->startHour < other.startHour && this->endHour < other.endHour)
            || (other.startHour < this->startHour && other.endHour < this->endHour);              
    }

};

class EventCollection
{
    Event events[20];
    unsigned eventCount = 0;

    void copyClassFrom(const EventCollection& other)
    {

        for (size_t i = 0; i < other.eventCount; i++)
        {
            this->events[i] = other.events[i];
        }
        this->eventCount = other.eventCount;

    }
    void copyEventFrom(const Event*& other, size_t eventsCount)
    {
        for (size_t i = 0; i < eventsCount; i++)
        {
            this->events[i] = other[i];
        }
        this->eventCount = eventsCount;

    }

    const EventCollection getMatchingDates(const Date& targetDate)
    {
        EventCollection matchingDates;
        for (size_t i = 0; i < eventCount; i++)
        {
            Date currentDate = this->events[i].getDate();
            if (currentDate.day == targetDate.day
                && currentDate.month == targetDate.month
                && currentDate.year == targetDate.year)
            {
                matchingDates.addEvent(this->events[i]);
            }
        }

        return matchingDates;
    }

public:

    EventCollection() = default;

    EventCollection(const Event*& events, const unsigned eventsCount)
    {
        copyEventFrom(events, eventsCount);
    }

    EventCollection(const EventCollection& other)
    {
        copyClassFrom(other);
    }

    EventCollection& operator=(const EventCollection& other)
    {
        copyClassFrom(other);
    }

    const Event* getEvents() const
    {
        return this->events;
    }

    const unsigned getEventsCount() const
    {
        return this->eventCount;
    }

    void setEvents(const Event*& others, size_t eventsCount)
    {
        copyEventFrom(others, eventCount);
    }

    void setEventsCount(const unsigned eventsCount)
    {
        this->eventCount = eventCount;
    }

    void addEvent(const Event& newEvent)
    {
        events[eventCount++] = newEvent;
    }

    const Event& findLongestEvent() const 
    {
        int biggestDuration = INT_MIN;
        int biggestIndex = 0;
        for (size_t i = 0; i < eventCount; i++)
        {
            int currentDuration = events[i].getDuration();
            if(currentDuration > biggestDuration)
            {
                biggestDuration = currentDuration;
                biggestIndex = i;
            }
        }
        return this->events[biggestIndex];
    }

    const unsigned getMaxVisitableEventsCount(const Date& targetDate)
    {
        const EventCollection matchingDates = getMatchingDates(targetDate);
        unsigned matchDatesCount = matchingDates.getEventsCount();

        unsigned maxVisitations = 0;

        for (size_t i = 0; i < matchDatesCount; i++)
        {
            unsigned currentVisitations = 0;
            for (size_t j = 0; j < matchDatesCount; j++)
            {
                if (i == j)
                    continue;
                else if (matchingDates.events[i].isNotIntersecting(matchingDates.events[j]))
                {
                    currentVisitations++;
                }
            }
            if (currentVisitations > maxVisitations)
                maxVisitations = currentVisitations;
        }

        return maxVisitations;
    }

    void removeEvent(const char* targetName)
    {
        for (size_t i = 0; i < this->eventCount; i++)
        {
            if (!strcmp(this->events[i].getName(), targetName))
            {
                if (i == this->eventCount - 1)
                {
                    this->events[i].setName("");
                    Date defaultDate = { 0,0,0 };
                    this->events[i].setDate(defaultDate);
                    this->events[i].setStartHour(0);
                    this->events[i].setEndHour(0);
                    break;
                }
                for (size_t j = i; j < this->eventCount-1; j++)
                {
                    this->events[j] = this->events[j + 1];
                }
            }
        }
        this->eventCount--;
    }

};

int main()
{
    EventCollection col;

    Date firstDate = { 12,12,2021 };


    Event exampleEvent1("delulu1", firstDate, 9,10);
    Event exampleEvent2("delulu2", firstDate, 11,12);
    Event exampleEvent3("delulu3", firstDate, 13,19);
    Event exampleEvent4("delulu4", firstDate, 14,16);
    Event exampleEvent5("delulu5", firstDate, 17,19);

    col.addEvent(exampleEvent1);
    col.addEvent(exampleEvent2);
    col.addEvent(exampleEvent3);
    col.addEvent(exampleEvent4);
    col.addEvent(exampleEvent5);


    std::cout << col.findLongestEvent().getName() << std::endl;

    std::cout << col.getMaxVisitableEventsCount(firstDate);

    col.removeEvent("delulu5");

}