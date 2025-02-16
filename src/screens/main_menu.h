#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "screen.h"
#include "hot_seat.h"
#include "create_lobby.h"
#include "lobby_list.h"
#include "globals.h"

class MainMenuScreen : public Screen
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
        MainMenuScreen() : Screen() {
            show(true);
        }

        void init() {}

        std::string getName() override {
            return name;
        };

        void show(bool force = false) override {
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

            lcd.setCursor(0, prevSelected);
            lcd.print(" ");

            lcd.setCursor(0, selected);
            lcd.print(">");
        }

        void selectBust() override {
            if (selected == 3) {
                return;
            }
            prevSelected = selected;
            selected++;

            show();
        }

        void selectClear() override {
            if (selected == 1) {
                return;
            }
            prevSelected = selected;
            selected--;

            show();
        }

        void selectLock() override {
            switch (selected-1) {
                case HOTSEAT:
                    currentScreen = new HotSeatScreen();
                    break;
                case CREATELOBBY:
                    currentScreen = new CreateLobbyScreen();
                    break;
                case JOINLOBBY:
                    currentScreen = new LobbyListScreen();
                    break;
            }
        }
};

#endif
