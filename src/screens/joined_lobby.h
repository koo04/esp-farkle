#ifndef JOINED_LOBBY_SCREEN_H
#define JOINED_LOBBY_SCREEN_H
#include "screen.h"
#include "name_gen.h"
#include "lobby.h"
#include "globals.h"

class JoinedLobbyScreen : public Screen
{
private:
    bool showing = false;

public:
    std::string name = "joined_lobby";
    JoinedLobbyScreen() : Screen()
    {
        show();
    }

    void init()
    {
        currentLobby->onChangeBind(Lobby::ON_CHANGE, [this]()
                                   { this->show(false); });
    }

    void show(bool force = false)
    {
        if (!showing || force)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Name: ");
            lcd.print(currentLobby->name.c_str());
            lcd.setCursor(0, 1);
            lcd.print("Connected Players: ");
            lcd.setCursor(0, 3);
            lcd.print("Leave = bust");

            lcd.setCursor(0, 2);
            String p = "";
            for (int i = 0; i < currentLobby->players.size(); i++)
            {
                p += currentLobby->players[i].name.c_str();

                if (i != currentLobby->players.size() - 1)
                {
                    p += ", ";
                }
            }
            if (p.length() > 20)
            {
                p = p.substring(0, 20);
            }
            lcd.print(p);

            showing = true;
        }
    }

    void selectBust() override
    {
        mainScreen->show();
    }
};

#endif
