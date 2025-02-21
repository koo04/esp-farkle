#ifndef LOBBY_H
#define LOBBY_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ArduinoJson.h>
#include <sstream>
#include <atomic>
#include <thread>
#include <chrono>
#include "utils.h"
#include "player.h"

class Lobby {
private:
    time_t lastUpdated;
    std::array<std::function<void()>, 10> callbacks;
public:
    int id;
    std::string name;
    int age;
    Player& host;
    std::vector<Player> players;
    bool running{false};

    enum CALLBACK_TYPE {
        ON_CHANGE
    };

    Lobby() : host(*(new Player())) {}
    Lobby(std::string name, Player& host) : id(generateId()), name(name), age(0), host(host) {
        addPlayer(host);
    }
    Lobby(int id, std::string name, int age, Player& host) : id(id), name(name), age(age), host(host) {}

    void onChangeBind(CALLBACK_TYPE cbType, std::function<void()> callback) {
        callbacks[cbType] = callback;
    }

    void addPlayer(Player& player) {
        players.push_back(player);

        for (auto& callback : callbacks) {
            if (callback != nullptr) {
                callback();
            }
        }
    }

    void removePlayer(const std::string& playerName) {
        players.erase(std::remove_if(players.begin(), players.end(),
            [&playerName](const Player& player) {
                return player.name == playerName;
            }), players.end());

        for (auto& callback : callbacks) {
            if (callback != nullptr) {
                callback();
            }
        }
    }

    bool searchPlayer(const std::string& playerName) {
        return std::any_of(players.begin(), players.end(),
            [&playerName](const Player& player) {
                return player.name == playerName;
            });
    }

    void printPlayers() const {
        std::cout << "Players in Lobby " << id << ":\n";
        for (const auto& player : players) {
            std::cout << player.name << "\n";
        }
    }

    int getId() const {
        return id;
    }

    std::string getPlayersStr() const {
        std::string playersStr;
        int i = 0;
        for (const auto& player : players) {
            playersStr += player.name;
            if (i < players.size() - 1) {
                playersStr += ", ";
            }
            i++;
        }
        return playersStr;
    }

    std::string info() const {
        std::ostringstream oss;
        oss << "Lobby: " << id << "\n  age: " << age << "\n  with players: " << getPlayersStr();
        return oss.str();
    }

    void toJson(JsonObject& obj) const {
        obj["id"] = id;
        obj["name"] = name;
        obj["age"] = age;

        JsonArray playersArray = obj["players"].to<JsonArray>();
        for (const auto& player : players) {
            JsonObject playerObj = playersArray.add<JsonObject>();
            player.toJson(playerObj);
        }
    }

    static Lobby* fromJson(const JsonObject& obj) {
        int lobbyId = obj["id"].as<int>();
        std::string lobbyName = obj["name"].as<std::string>();
        int lobbyAge = obj["age"].as<int>();
        Player lobbyOwner = Player::fromJson(obj["owner"].as<JsonObject>());

        Lobby* lobby = new Lobby(lobbyId, lobbyName, lobbyAge, lobbyOwner);
        for (JsonObject playerObj : obj["players"].as<JsonArray>()) {
            Player player = Player::fromJson(playerObj);
            lobby->addPlayer(player);
        }
        return lobby;
    }

    void setAge(int a) {
        age = a;
    }

    bool isValid() {
        return players.size() > 0;
    }

    void updateLobbyAge() {
        age++;
    }

    void startAgeUpdater() {
        running = true;
        std::thread([this]() {
            while (running) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                updateLobbyAge();
            }
        }).detach();
    }

    void stopAgeUpdater() {
        running = false;
    }

    void setLastUpdated(time_t t) {
        lastUpdated = t;
    }

    time_t getLastUpdated() {
        return lastUpdated;
    }

    bool old() const {
        return time(NULL) - lastUpdated > 10;
    }
};

#endif
