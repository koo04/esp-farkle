#ifndef HOSTED_LOBBY_SCREEN_H
#define HOSTED_LOBBY_SCREEN_H
#include "screen.h"
#include "name_gen.h"
#include "lobby.h"

class HostedLobbyScreen : public Screen
{
private:
    bool showing = false;
    Lobby* lobby = nullptr;
public:
    std::string name = "hosted_lobby";
    HostedLobbyScreen(Lobby* lobby) : Screen(), lobby(lobby)
    {
        show();
    }

    void init()
    {
        lobby->onChangeBind(Lobby::ON_CHANGE, [this]()
                                   { this->show(false); });
    }

    void show(bool force = false)
    {
        if (!showing || force)
        {
            lcd.clear();

            int pos = static_cast<int>(std::floor((20 - lobby->name.length()) / 2.0));
            lcd.setCursor(pos, 0);
            lcd.print(lobby->name.c_str());
            showing = true;
        }
    }
};

#endif
