#include "ClimaTask.h"

#define HEATER_HALF_UPTHRESH 18
#define HEATER_FULL_UPTHRESH 15
#define COOLER_HALF_UPTHRESH 28
#define COOLER_FULL_UPTHRESH 32

#define COOLER_TURNOFF_TEMP 26
#define HEATER_TURNOFF_TEMP 20

#define COOLER_FULL_DOWNTHRESH 26
#define HEATER_FULL_DOWNTHRESH 20


ClimaTask::ClimaTask(TemperatureSensor *tempSensor, Light *cooler_half, Light *cooler_full, Light *heater_half, Light *heater_full) {
    this->tempSensor = tempSensor;
    this->cooler_full = cooler_full;
    this->cooler_half = cooler_half;
    this->heater_full = heater_full;
    this->heater_half = heater_half;
    state = IDLE;
}

void ClimaTask::tick() {
    switch (state)
    {
    case IDLE:
        idle();
        break;

    case HEATING_FULL:
        heating_full();
        break;

    case HEATING_HALF:
        heating_half();
        break;

    case COOLING_FULL:
        cooling_full();
        break;

    case COOLING_HALF:
        cooling_half();
        break;
    }
}

void ClimaTask::idle() {
    float temp = this->tempSensor->getTemperature();

    if (temp <= HEATER_HALF_UPTHRESH) {
        heater_half->switchOn();
        
        state = HEATING_HALF;
    } 
    
    if (temp > COOLER_HALF_UPTHRESH) {
        cooler_half->switchOn();
        state = COOLING_HALF;
    }
}

void ClimaTask::heating_half() {
    double temp = this->tempSensor->getTemperature();

    if (temp <= HEATER_FULL_UPTHRESH) {
        heater_full->switchOn();
        state = HEATING_FULL;
    }

    if (temp >= HEATER_TURNOFF_TEMP) {
        heater_half->switchOff();
        state = IDLE;
    }
}

void ClimaTask::heating_full() {
    float temp = this->tempSensor->getTemperature();

    if (temp < HEATER_FULL_DOWNTHRESH) {
        heater_full->switchOff();
        state = HEATING_HALF;
    }
}

void ClimaTask::cooling_half() {
    float temp = this->tempSensor->getTemperature();

    if (temp >= COOLER_FULL_UPTHRESH) {
        cooler_full->switchOn();
        state = COOLING_FULL;
    }

    if (temp <= COOLER_TURNOFF_TEMP) {
        cooler_half->switchOff();
        state = IDLE;
    }
}

void ClimaTask::cooling_full() {
    float temp = this->tempSensor->getTemperature();

    if (temp > COOLER_FULL_DOWNTHRESH) {
        cooler_full->switchOff();
        state = COOLING_HALF;
    }
}

ClimaTaskState ClimaTask::getState() {
    return state;
}