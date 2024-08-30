#include "SmartLampTask.h"

#define MANUAL_CHAR 'm'
#define AUTO_CHAR 'a'
#define MAX_LUX 500
#define MIN_LUX 100


SmartLampTask::SmartLampTask(Light *smartLamp, LightSensor *lightSensor, SimpleButton *button) {
    this->smartLamp = smartLamp;
    this->lightSensor = lightSensor;
    this->button = button;
    this->ledState = ledState;

    this->taskPeriod = taskPeriod;
    this->pressedTime = pressedTime;

    state = AUTOMATIC;
}

void SmartLampTask::tick() {
        switch (state)
        {
        case AUTOMATIC:
            automatic();
            break;
        case MANUAL:
            manual();
            break;          
        }
}

void SmartLampTask::automatic() {
    int intensity = lightSensor->getLightIntensity();
    char serialInput;

    if(Serial.available() > 0){
        Serial.println("Input rilevato, passaggio a modalità manuale");
        serialInput = Serial.read();
    }

    if (serialInput == MANUAL_CHAR)  {
        state = MANUAL;
    }

    if(intensity <= MIN_LUX) {
        smartLamp->switchOn();
    } else if(intensity >= MAX_LUX) {
        smartLamp->switchOff();
    }
}

void SmartLampTask::manual() {
    bool buttonState = button->isPressed();
    pressedTime += taskPeriod;
    char serialInput;

    if(Serial.available() > 0){
        Serial.println("Input rilevato, passaggio a modalità automatica");
        serialInput = Serial.read();
    }
    
    if (serialInput == AUTO_CHAR)  {
        state = AUTOMATIC;
    }

    if(!buttonState && !ledState && pressedTime > DEBOUNCE_TIME) {
        smartLamp->switchOff();
    } else if(buttonState && pressedTime > DEBOUNCE_TIME) {
        pressedTime = 0;
        smartLamp->switchOn();
        ledState = !ledState;
    }
}