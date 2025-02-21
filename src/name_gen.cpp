#include "name_gen.h"

std::vector<std::string> animals = {
    "Aardvark",     "Albatross",    "Alligator",    "Alpaca",       "Ant",
    "Baboon",       "Badger",       "Barracuda",    "Bat",          "Bear",
    "Camel",        "Capybara",     "Caribou",      "Cassowary",    "Cat",
    "Deer",         "Dinosaur",     "Dog",          "Dogfish",      "Dolphin",
    "Eagle",        "Echidna",      "Eel",          "Eland",        "Elephant",
    "Falcon",       "Ferret",       "Finch",        "Fish",         "Flamingo",
    "Gaur",         "Gazelle",      "Gerbil",       "Giraffe",      "Gnat",
    "Hare",         "Hawk",         "Hedgehog",     "Heron",        "Herring",
    "Ibex",         "Ibis",         "Jackal",       "Jaguar",       "Jay",
    "Kangaroo",     "Kingfisher",   "Koala",        "Kookabura",    "Kouprey",
    "Lapwing",      "Lark",         "Lemur",        "Leopard",      "Lion",
    "Magpie",       "Mallard",      "Manatee",      "Mandrill",     "Meerkat",
    "Narwhal",      "Newt",         "Nightingale",  "Octopus",      "Okapi",
    "Opossum",      "Oryx",         "Ostrich",      "Otter",        "Owl",
    "Panther",      "Parrot",       "Partridge",    "Peafowl",      "Pelican",
    "Quail",        "Quelea",       "Quetzal",      "Rabbit",       "Raccoon",
    "Rail",         "Ram",          "Rat",          "Raven",        "Red deer",
    "Salamander",   "Salmon",       "Sand dollar",  "Sandpiper",    "Sardine",
    "Tapir",        "Tarsier",      "Termite",      "Tiger",        "Toad",
    "Viper",        "Vulture",      "Wallaby",      "Walrus",       "Wasp",
    "Yak",          "Zebra"
};

std::vector<std::string> adjectives = {
    "Adorable",     "Adventurous",  "Aggressive",   "Agreeable",        "Alert",
    "Baboon",       "Badger",       "Barracuda",    "Bat",              "Bear",
    "Calm",         "Careful",      "Cautious",     "Charming",         "Cheerful",
    "Dangerous",    "Dark",         "Dead",         "Defeated",         "Defiant",
    "Eager",        "Easy",         "Elated",       "Elegant",          "Embarrassed",
    "Fair",         "Faithful",     "Famous",       "Fancy",            "Fantastic",
    "Gentle",       "Gifted",       "Glamorous",    "Gleaming",         "Glorious",
    "Handsome",     "Happy",        "Healthy",      "Helpful",          "Helpless",
    "Important",    "Impossible",   "Inexpensive",  "Innocent",         "Inquisitive",
    "Jealous",      "Jittery",      "Jolly",        "Joyous",           "Kind",
    "Lazy",         "Light",        "Lively",       "Lonely",           "Long",
    "Magnificent",  "Misty",        "Modern",       "Motionless",       "Muddy",
    "Nasty",        "Naughty",      "Nervous",      "Nice",             "Nutty",
    "Obedient",     "Obnoxious",    "Odd",          "Old-fashioned",    "Open",
    "Panicky",      "Perfect",      "Plain",        "Pleasant",         "Poised",
    "Real",         "Relieved",     "Repulsive",    "Rich",             "Scary",
    "Selfish",      "Shiny",        "Shy",          "Silly",            "Sleepy",
    "Sparkling",    "Splendid",     "Spotless",     "Stormy",           "Strange",
    "Successful",   "Super",        "Talented",     "Tame",             "Tender",
    "Ugly",         "Uninterested", "Unsightly",    "Unusual",          "Upset",
    "Vast",         "Victorious",   "Vivacious",    "Wandering",        "Weary",
    "Wicked",       "Wide-eyed",    "Wild",         "Witty",            "Worried",
    "Zany",         "Zealous"
};

std::vector<std::string> objects = {
    "Airplane",     "Apple",        "Balloon",      "Banana",       "Bicycle",
    "Boat",         "Book",         "Bottle",       "Bowl",         "Box",
    "Bus",          "Calculator",   "Calendar",     "Camera",       "Candle",
    "Car",          "Chair",        "Clock",        "Computer",     "Cup",
    "Desk",         "Door",         "Fan",          "Flag",         "Flower",
    "Fork",         "Guitar",       "Hammer",       "Hat",          "House",
    "Key",          "Knife",        "Lamp",         "Laptop",       "Leaf",
    "Light",        "Lock",         "Map",          "Microwave",    "Mirror",
    "Mug",          "Nail",         "Needle",       "Notebook",     "Oven",
    "Painting",     "Paper",        "Pen",          "Pencil",       "Phone",
    "Piano",        "Picture",      "Pillow",       "Plate",        "Radio",
    "Refrigerator", "Ring",         "Scissors",     "Shampoo",      "Shirt",
    "Shoe",         "Sofa",         "Spoon",        "Table",        "Television",
    "Towel",        "Truck",        "Umbrella",     "Vase",         "Watch",
    "Wheel",        "Window",       "Wrench"
};

std::string generateName(bool useAnimals = false) {
    randomSeed(time(NULL));
    std::vector<std::string> nounList = useAnimals ? animals : objects;
    std::string adjective = adjectives[random() % adjectives.size()];
    std::string noun = nounList[random() % nounList.size()];
    std::string name = adjective + " " + noun;
    while (name.length() == 0 || name.length() > 20) {
        Serial.println("Name too long, generating new one");
        name = generateName(useAnimals);
    }
    return name;
}
