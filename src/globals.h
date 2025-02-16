#ifndef GLOBALS_H
#define GLOBALS_H

#include "player.h"
#include "lobby.h"
#include "screens.h"

Player me;
Lobby* currentLobby;
std::map<uint32_t, Lobby *> lobbies;

Screen* currentScreen;

#endif
