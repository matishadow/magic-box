//
// Created by matishadow on 11/07/2020.
//

#ifndef MAGIC_BOX_MAGIC_BOX_H_H
#define MAGIC_BOX_MAGIC_BOX_H_H

void openBox();
void closeBox();
bool areAllNumbersGuessed();
bool resetTurns ();
byte getDigitalFromAnalog(int pinNumber);
int getDigit();
void setup();
bool isInputReady();
void loop();
void turnOnInputLed();
void turnOffInputLed();

#endif //MAGIC_BOX_MAGIC_BOX_H_H
