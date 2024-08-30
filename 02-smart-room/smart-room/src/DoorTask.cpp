#include "DoorTask.h"
#include "ProximitySensor.h"
#include "Motor.h"

#define OPENED_ANGLE 180
#define OPENED_PERIOD 30000 // 30 secondi
#define CLOSED_ANGLE 0
#define STEP 10

DoorTask::DoorTask(Presence *presence, MyServo *servo) {
    this->servo = servo;
    this->presence = presence;

    this->taskPeriod = taskPeriod;

    state = CLOSED;
    openedTimeElapsed = 0;
}

void DoorTask::tick() {
        switch (state)
        {
        case CLOSED:
            closed();
            break;
        case OPENING:
            opening();
            break;
        case CLOSING:
            closing();
            break;      
        case OPENED:
            opened();
            break;       
        }
}

void DoorTask::closed() {
    if (presence->isNear())  {
        Serial.println("Presenza rilevata. Durata apertura circa 30s da ultimo movimento");
        state = OPENING;
    }
}

void DoorTask::opening() {
    int curr = servo->getAngle();
    int newPos = curr + STEP;
    servo->setAngle(newPos);

    if (newPos == OPENED_ANGLE) {
        openedTimeElapsed = 0;
        state = OPENED;
    }
}

void DoorTask::opened() {
    openedTimeElapsed += this->taskPeriod;

    bool isNear = presence->isNear();

    if (openedTimeElapsed >= OPENED_PERIOD && isNear) {
        openedTimeElapsed = 0;
    }

    if (openedTimeElapsed >= OPENED_PERIOD && !isNear) {
        Serial.println("Chiusura porta");
        state = CLOSING;
    }
}

void DoorTask::closing() {
    int curr = servo->getAngle();
    int newPos = curr - STEP;
    servo->setAngle(newPos);

    if (newPos == CLOSED_ANGLE) {
        state = CLOSED;
    }  
}