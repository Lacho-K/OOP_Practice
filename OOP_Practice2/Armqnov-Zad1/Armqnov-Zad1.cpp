#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable:4996)

enum Color
{
    Red,
    Black,
    Blue,
    White,
    Green,
    ColorCount
};

const char* colorToString(Color c)
{
    switch (c)
    {
    case Red: return "Red";
    case Black: return "Black";
    case Blue: return "Blue";
    case White: return "White";
    case Green: return "Green";
    default: return "";
    }
}

Color stringToColor(const char* s)
{
    if (strcmp(s, "Red") == 0) return Red;
    if (strcmp(s, "Black") == 0) return Black;
    if (strcmp(s, "Blue") == 0) return Blue;
    if (strcmp(s, "White") == 0) return White;
    if (strcmp(s, "Green") == 0) return Green;
    return ColorCount;
}

struct Player
{
    char name[128];
    unsigned short id;

    void setName(const char* n)
    {
        strncpy(name, n, 127);
        name[127] = '\0';
    }
};

struct Card
{
    char name[64];
    unsigned short id;
    Color color;

    void setName(const char* n)
    {
        strncpy(name, n, 63);
        name[63] = '\0';
    }
};

struct Deck
{
    unsigned short playerId;
    Color color;
    unsigned short cardIds[60];
};

class Database
{
private:
    std::fstream playersFile;
    std::fstream cardsFile;
    std::fstream decksFile;

public:
    Database()
    {
        openFile(playersFile, "players.dat");
        openFile(cardsFile, "cards.dat");
        openFile(decksFile, "decks.dat");
    }

    void openFile(std::fstream& f, const char* name)
    {
        f.open(name, std::ios::in | std::ios::out | std::ios::binary);
        if (!f)
        {
            f.open(name, std::ios::out | std::ios::binary);
            f.close();
            f.open(name, std::ios::in | std::ios::out | std::ios::binary);
        }
    }

    void createPlayer(const char* name)
    {
        Player p;
        p.setName(name);
        playersFile.seekp(0, std::ios::end);
        p.id = playersFile.tellp() / sizeof(Player);
        playersFile.write((char*)&p, sizeof(Player));
    }

    void createCard(const char* name, const char* color)
    {
        Color c = stringToColor(color);
        if (c == ColorCount) return;

        Card card;
        card.setName(name);
        card.color = c;
        cardsFile.seekp(0, std::ios::end);
        card.id = cardsFile.tellp() / sizeof(Card);
        cardsFile.write((char*)&card, sizeof(Card));
    }

    void createDeck(const char* playerName, char cardNames[60][64])
    {
        Player p;
        bool found = false;
        playersFile.clear();
        playersFile.seekg(0);
        while (playersFile.read((char*)&p, sizeof(Player)))
        {
            if (strcmp(p.name, playerName) == 0)
            {
                found = true;
                break;
            }
        }
        if (!found) return;

        Card cardsList[1000];
        int cardCount = 0;
        cardsFile.clear();
        cardsFile.seekg(0);
        while (cardsFile.read((char*)&cardsList[cardCount], sizeof(Card))) cardCount++;

        Deck d;
        d.playerId = p.id;
        int colorFreq[ColorCount] = { 0 };

        for (int i = 0; i < 60; i++)
        {
            bool match = false;
            for (int j = 0; j < cardCount; j++)
            {
                if (strcmp(cardNames[i], cardsList[j].name) == 0)
                {
                    d.cardIds[i] = cardsList[j].id;
                    colorFreq[cardsList[j].color]++;
                    match = true;
                    break;
                }
            }
            if (!match) return;
        }

        int maxColor = 0;
        for (int i = 1; i < ColorCount; i++)
        {
            if (colorFreq[i] > colorFreq[maxColor]) maxColor = i;
        }
        d.color = (Color)maxColor;

        decksFile.seekp(0, std::ios::end);
        decksFile.write((char*)&d, sizeof(Deck));
    }

    void generateReport()
    {
        Player playersList[100];
        int playerCount = 0;
        playersFile.clear();
        playersFile.seekg(0);
        while (playersFile.read((char*)&playersList[playerCount], sizeof(Player))) playerCount++;

        Card cardsList[10000];
        int cardCount = 0;
        cardsFile.clear();
        cardsFile.seekg(0);
        while (cardsFile.read((char*)&cardsList[cardCount], sizeof(Card))) cardCount++;

        Deck decksList[1000];
        int deckCount = 0;
        decksFile.clear();
        decksFile.seekg(0);
        while (decksFile.read((char*)&decksList[deckCount], sizeof(Deck))) deckCount++;

        std::ofstream out("report.txt");

        for (int c = 0; c < ColorCount; c++)
        {
            out << colorToString((Color)c) << "\n";
            for (int i = 0; i < deckCount; i++)
            {
                if (decksList[i].color != c) continue;

                const char* owner = "";
                for (int j = 0; j < playerCount; j++)
                {
                    if (playersList[j].id == decksList[i].playerId)
                    {
                        owner = playersList[j].name;
                        break;
                    }
                }

                const char* cardName = "";
                Color cardColor;
                for (int j = 0; j < cardCount; j++)
                {
                    if (cardsList[j].id == decksList[i].cardIds[0])
                    {
                        cardName = cardsList[j].name;
                        cardColor = cardsList[j].color;
                        break;
                    }
                }

                out << "Owner: " << owner << " Card: " << cardName << " Color: " << colorToString(cardColor) << "\n";
            }
        }

        int usage[32768] = { 0 };
        for (int i = 0; i < deckCount; i++)
        {
            for (int j = 0; j < 60; j++)
            {
                usage[decksList[i].cardIds[j]]++;
            }
        }

        int maxId = 0;
        for (int i = 1; i < 32768; i++)
        {
            if (usage[i] > usage[maxId]) maxId = i;
        }

        for (int j = 0; j < cardCount; j++)
        {
            if (cardsList[j].id == maxId)
            {
                out << "Most common card: " << cardsList[j].name << " Color: " << colorToString(cardsList[j].color) << "\n";
                break;
            }
        }

        out.close();
    }

    void close()
    {
        playersFile.close();
        cardsFile.close();
        decksFile.close();
    }
};

int main()
{
    Database db;
    char command[10];

    while (std::cin >> command)
    {
        if (strcmp(command, "cp") == 0)
        {
            //std::cin.ignore();
            char name[128];
            std::cin.getline(name, 128);
            db.createPlayer(name);
        }

        else if (strcmp(command, "cc") == 0)
        {
            char color[10];
            char name[64];
            std::cin >> color;
            std::cin.ignore();
            std::cin.getline(name, 64);
            db.createCard(name, color);
        }

        else if (strcmp(command, "cd") == 0)
        {
            std::cin.ignore();
            char playerName[128];
            char cardNames[60][64];
            std::cin.getline(playerName, 128);
            for (int i = 0; i < 60; i++)
            {
                std::cin.getline(cardNames[i], 64);
            }
            db.createDeck(playerName, cardNames);
        }

        else if (strcmp(command, "report") == 0)
        {
            db.generateReport();
        }

        else
        {
            break;
        }
    }

    db.close();
    return 0;
}
