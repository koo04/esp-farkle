#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <LiquidCrystal_I2C.h>
#include <map>
#include <vector>
#include "lobby.h"
#include "custom_chars.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

class Screen {
    private:
        std::string name = "screen";
    public:
        int prevSelected = 0;
        int selected = 0;

        Screen() {
            lcd.init();
            lcd.backlight();
        };

        LiquidCrystal_I2C getLcd() {
            return lcd;
        }

        virtual std::string getName() {
            return name;
        };

        virtual void show(bool force = false) {};

        virtual void selectBust() {}
        virtual void selectClear() {}
        virtual void selectLock() {}
        virtual void selectBank() {}
        virtual void selectNum(int num) {}
};

#endif
