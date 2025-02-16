#ifndef CREAT_LOBBY_SCREEN_H
#define CREAT_LOBBY_SCREEN_H
#include "screen.h"
#include "name_gen.h"
#include "globals.h"

class CreateLobbyScreen : public Screen
{
    private:
        bool showing = false;
        std::string lobbyName = generateName(false);
    public:
        std::string name = "create_lobby";
        CreateLobbyScreen() : Screen() {
            show();
        }

        void show(bool force = false) {
            if (!showing || force) {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Create Lobby");
                lcd.setCursor(1, 1);
                lcd.print("Lobby name:");
                int pos = static_cast<int>(std::floor((20 - lobbyName.length()) / 2.0));
                lcd.setCursor(pos, 2);
                lcd.print(lobbyName.c_str());
                lcd.setCursor(0, 3);
                lcd.print(">Press to create");
                showing = true;
            }
        }
};

#endif

