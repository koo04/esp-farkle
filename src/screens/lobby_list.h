#ifndef LOBBY_LIST_SCREEN_H
#define LOBBY_LIST_SCREEN_H
#include "screen.h"
#include "name_gen.h"
#include "main_menu.h"

class LobbyListScreen : public Screen
{
private:
    std::string name = "lobby_list";
    bool showing = false;
    int pos = 0;

public:
    LobbyListScreen() : Screen()
    {
        show();
    }

    void init() {}

    std::string getName() override
    {
        return name;
    };

    void show(bool force = false)
    {
        if (!showing || force)
        {
            lcd.clear();

            lcd.setCursor(0, 0);
            lcd.print("Lobbies");

            showing = true;
        }

        Serial.println("previously selected: " + String(prevSelected));
        Serial.println("selected: " + String(selected));

        if (selected < 0)
        {
            selected = 0;
            if (pos > 0)
            {
                pos--;
            }
        }

        if (selected > 2)
        {
            selected = 2;
            // if (pos < lobbies.size() - 3)
            // {
            //     pos++;
            // }
        }

        // if (lobbies.size() == 0)
        // {
        //     lcd.setCursor(5, 1);
        //     lcd.print("No lobbies");
        //     return;
        // }

        for (int i = 0; i < 3; i++)
        {
            lcd.setCursor(0, i + 1);
            if (i == selected)
            {
                lcd.print(">");
            }
            else
            {
                lcd.print(" ");
            }
            lcd.setCursor(1, i + 1);
            // lcd.print(lobbies[pos + i]->name.c_str());
        }
    }

    // void selectLock() override
    // {
    //     Lobby *lobby = lobbies[pos + selected];
    //     Serial.printf("Selected lobby: %s\n", lobby->name.c_str());
    //     currentLobby = lobby;
    //     joinedLobbyScreen->show();
    // }

    // void selectBust() override {
    //     currentScreen = new MainScreen();
    // }
};

#endif
