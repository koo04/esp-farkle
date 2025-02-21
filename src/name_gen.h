#include <vector>
#include <string>
#include <cstdlib>
#include <Arduino.h>

extern std::vector<std::string> animals;
extern std::vector<std::string> objects;
extern std::vector<std::string> adjectives;

std::string generateName(bool useAnimals);
