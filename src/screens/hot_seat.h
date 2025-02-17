#ifndef HOT_SEAT_SCREEN_H
#define HOT_SEAT_SCREEN_H

#include "globals.h"
#include "screen.h"

class HotSeatScreen : public Screen
{
private:
    bool showing = false;
    int numOfPlayers = 2;

public:
    std::string name = "hot_seat";
    HotSeatScreen() : Screen()
    {
        show();
    }

    void show(bool force = false)
    {
        if (!showing || force)
        {
            lcd.clear();

            lcd.setCursor(1, 0);
            lcd.print("Hot Seat");
            lcd.setCursor(1, 1);
            lcd.print("How many players: ");

            showing = true;
        }

        lcd.setCursor(18, 1);
        lcd.print(numOfPlayers);
    }

    void onNumButton(int num)
    {
        numOfPlayers = num;
        show();
    }

    void selectBank() override
    {
        currentScreen = previousScreen;
        currentScreen->show(true);

        previousScreen = nullptr;
    }

    void selectNum(int num) override
    {

        numOfPlayers = num;

        if (numOfPlayers < 2)
        {
            numOfPlayers = 2;
        }

        show();
    }
};

#endif
