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

        virtual void selectNext() {}
        virtual void selectPrevious() {}
        virtual void selectLock() {}
        virtual void selectClear() {}
        virtual void selectBank() {}
        virtual void selectBust() {}
        virtual void select01() {}
        virtual void select02() {}
        virtual void select03() {}
        virtual void select04() {}
        virtual void select05() {}
        virtual void select06() {}
};

#endif
