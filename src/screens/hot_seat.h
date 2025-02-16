#ifndef HOT_SEAT_SCREEN_H
#define HOT_SEAT_SCREEN_H
#include "screen.h"

class HotSeatScreen : public Screen
{
    private:
        bool showing = false;
        int numOfPlayers = 2;
    public:
        std::string name = "hot_seat";
        HotSeatScreen() : Screen() {
            show();
        }

        void show(bool force = false) {
            if (!showing || force) {
                lcd.clear();
        
                lcd.setCursor(1, 0);
                lcd.print("Hot Seat");
                lcd.setCursor(1, 1);
                lcd.print("How many players: ");

                lcd.setCursor(18, 1);
                lcd.print(numOfPlayers);

                showing = true;
            }
        }

        void onNumButton(int num) {
            numOfPlayers = num;
            show();
        }
};

#endif
