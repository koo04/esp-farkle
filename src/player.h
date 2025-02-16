#ifndef PLAYER_H
#define PLAYER_H

#include <ArduinoJson.h>
#include "name_gen.h"
#include "utils.h"
#include "lobby.h"

class Player {
    public:
        int id;
        std::string name;
        Player() : id(generateId()), name(generateName(false)) {}
        Player(const int& id, const std::string& name) : id(generateId()), name(name) {}
    
        void toJson(JsonObject& obj) const {
            obj["id"] = id;
            obj["name"] = name.c_str();
        }

        static Player fromJson(const JsonObject& obj) {
            return Player(obj["id"].as<int>(), obj["name"].as<std::string>());
        }
    };

#endif
