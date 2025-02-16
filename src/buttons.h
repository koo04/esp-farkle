#ifndef BUTTONS_H
#define BUTTONS_H

#include <InterruptButton.h>
#include "globals.h"

#define BUTTON_BUST_PIN 16
#define BUTTON_CLEAR_PIN 17
#define BUTTON_LOCK_PIN 4
#define BUTTON_BANK_PIN 18

#define BUTTON_01_PIN 33
#define BUTTON_02_PIN 32
#define BUTTON_03_PIN 27
#define BUTTON_04_PIN 26
#define BUTTON_05_PIN 25
#define BUTTON_06_PIN 14

InterruptButton button_bust(BUTTON_BUST_PIN, LOW);
InterruptButton button_clear(BUTTON_CLEAR_PIN, LOW);
InterruptButton button_lock(BUTTON_LOCK_PIN, LOW);
InterruptButton button_bank(BUTTON_BANK_PIN, LOW);

InterruptButton button_01(BUTTON_01_PIN, LOW);
InterruptButton button_02(BUTTON_02_PIN, LOW);
InterruptButton button_03(BUTTON_03_PIN, LOW);
InterruptButton button_04(BUTTON_04_PIN, LOW);
InterruptButton button_05(BUTTON_05_PIN, LOW);
InterruptButton button_06(BUTTON_06_PIN, LOW);

void setupButtons();
void buttonBustPressed();
void buttonClearPressed();
void buttonLockPressed();
void buttonBankPressed();
void button01Pressed();
void button02Pressed();
void button03Pressed();
void button04Pressed();
void button05Pressed();
void button06Pressed();

void setupButtons()
{
    pinMode(BUTTON_BUST_PIN, INPUT_PULLUP);
    pinMode(BUTTON_CLEAR_PIN, INPUT_PULLUP);
    pinMode(BUTTON_LOCK_PIN, INPUT_PULLUP);
    pinMode(BUTTON_BANK_PIN, INPUT_PULLUP);
    pinMode(BUTTON_01_PIN, INPUT_PULLUP);
    pinMode(BUTTON_02_PIN, INPUT_PULLUP);
    pinMode(BUTTON_03_PIN, INPUT_PULLUP);
    pinMode(BUTTON_04_PIN, INPUT_PULLUP);
    pinMode(BUTTON_05_PIN, INPUT_PULLUP);
    pinMode(BUTTON_06_PIN, INPUT_PULLUP);

    button_bust.bind(Event_KeyPress, &buttonBustPressed);
    button_clear.bind(Event_KeyPress, &buttonClearPressed);
    button_lock.bind(Event_KeyPress, &buttonLockPressed);
    button_bank.bind(Event_KeyPress, &buttonBankPressed);
    button_01.bind(Event_KeyPress, &button01Pressed);
    button_02.bind(Event_KeyPress, &button02Pressed);
    button_03.bind(Event_KeyPress, &button03Pressed);
    button_04.bind(Event_KeyPress, &button04Pressed);
    button_05.bind(Event_KeyPress, &button05Pressed);
    button_06.bind(Event_KeyPress, &button06Pressed);
}

void buttonBustPressed()
{
    currentScreen->selectBust();
}

void buttonClearPressed()
{
    currentScreen->selectClear();
}

void buttonLockPressed()
{
    currentScreen->selectLock();
}

void buttonBankPressed()
{
    currentScreen->selectBank();
}
void button01Pressed()
{
    Serial.println("Button 01 pressed");
}
void button02Pressed()
{
    Serial.println("Button 02 pressed");
}
void button03Pressed()
{
    Serial.println("Button 03 pressed");
}
void button04Pressed()
{
    Serial.println("Button 04 pressed");
}
void button05Pressed()
{
    Serial.println("Button 05 pressed");
}
void button06Pressed()
{
    Serial.println("Button 06 pressed");
}

#endif
