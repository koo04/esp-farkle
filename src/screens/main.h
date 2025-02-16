#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H
#include "screen.h"
#include "hot_seat.h"
#include "create_lobby.h"
#include "lobby_list.h"

class MainScreen : public Screen
{
    private:
        std::string name = "main";
        bool showing = false;
        enum selectedNames {
            HOTSEAT,
            CREATELOBBY,
            JOINLOBBY
        };
    public:
        MainScreen() : Screen() {
            show(true);
        }

        void init() {}

        std::string getName() override {
            return name;
        };

        void show(bool force = false) override {
            Serial.println("Showing Main");
            if (!showing || force) {
                lcd.clear();

                lcd.setCursor(6, 0);
                lcd.print("Farkle!");

                lcd.setCursor(1, 1);
                lcd.print("Hot Seat");
                lcd.setCursor(1, 2);
                lcd.print("Create Lobby");
                lcd.setCursor(1, 3);
                lcd.print("Join Lobby");

                showing = true;
                selected = 1;
            }

            if (selected < 1) {
                selected = 3;
            }

            if (selected > 3) {
                selected = 1;
            }

            lcd.setCursor(0, prevSelected);
            lcd.print(" ");

            lcd.setCursor(0, selected);
            lcd.print(">");
        }

        Screen* select() override {
            switch (selected-1) {
                case HOTSEAT:
                    return new HotSeatScreen();
                case CREATELOBBY:
                    return new CreateLobbyScreen();
                case JOINLOBBY:
                    return new LobbyListScreen();
            }

            return this;
        }
};

#endif
