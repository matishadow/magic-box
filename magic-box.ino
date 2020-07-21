#include <Arduino.h>
#include <Servo.h>

#include "magic-box-h.h"

const int analogPinInputWaiting = A4;
const int ledInputWaiting = 6;

int turnNumber;
Servo myServo;

struct Turn {
    int guessStatusLedPin;
    int digitToGuess;
};

Turn turns[] = {{guessStatusLedPin: 5, digitToGuess: 0},
                {guessStatusLedPin: 4, digitToGuess: 0},
                {guessStatusLedPin: 3, digitToGuess: 0},
                {guessStatusLedPin: 2, digitToGuess: 0}};

void setup() {
    myServo.attach(9);
    closeBox();

    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    Serial.begin(9600);
}

void loop() {
    if (isInputReady()) {
        turnOnInputLed();
        int digit = getDigit();

        Turn currentTurn = turns[turnNumber];
        if (digit == currentTurn.digitToGuess){
            digitalWrite(currentTurn.guessStatusLedPin, HIGH);
            turnNumber++;
        }
        else resetTurns();

        turnOffInputLed();

        if (areAllNumbersGuessed())
            openBox();

        while(isInputReady()){};
    }
}

void turnOnInputLed(){
    digitalWrite(ledInputWaiting, HIGH);
    delay(3000);
}

void turnOffInputLed(){
    digitalWrite(ledInputWaiting, LOW);
}

void openBox() { myServo.write(0); }

void closeBox() { myServo.write(92); }

bool areAllNumbersGuessed() {return turnNumber >= sizeof(turns) / sizeof(Turn);}

bool resetTurns () {
    turnNumber = 0;

    for (auto turn : turns) {
        digitalWrite(turn.guessStatusLedPin, LOW);
    }
}

byte getDigitalFromAnalog(int pinNumber){
    int value = analogRead(pinNumber);

    if (value > 650)
        return 1;
    else
        return 0;
}

int getDigit(){
    byte value0 = getDigitalFromAnalog(A0);
    byte value1 = getDigitalFromAnalog(A1);
    byte value2 = getDigitalFromAnalog(A2);
    byte value3 = getDigitalFromAnalog(A3);

    byte digit = value0 | value1 << 1u | value2 << 2u | value3 << 3u;

    return digit;
}

bool isInputReady() {
    bool isInputReady = getDigitalFromAnalog(analogPinInputWaiting);

    return isInputReady;
}
