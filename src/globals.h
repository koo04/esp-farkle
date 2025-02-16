#ifndef GLOBALS_H
#define GLOBALS_H

#include "player.h"
#include "lobby.h"
#include "screens.h"

Player me;
Lobby* currentLobby;
std::map<uint32_t, Lobby *> lobbies;

Screen* mainScreen = new MainScreen();
Screen* createLobbyScreen = new CreateLobbyScreen();
Screen* hotSeatScreen = new HotSeatScreen();
Screen* lobbyListScreen = new LobbyListScreen();
Screen* joinedLobbyScreen = new JoinedLobbyScreen();

Screen& currentScreen = *mainScreen;

#endif
