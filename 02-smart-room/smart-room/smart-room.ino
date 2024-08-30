#include "src/Scheduler.h"
#include "src/TemperatureSensorImpl.h"
#include "src/Led.h"
#include "src/ClimaTask.h"
#include "src/ProximitySensor.h"
#include "src/DoorTask.h"
#include "src/Motor.h"
#include "src/SimpleButton.h"
#include "src/SmartLampTask.h"
#include "src/LightSensorImpl.h"

#define SERVO_PIN 3

#define ECHO_PIN 6
#define TRIG_PIN 7
#define BUTTON_PIN 8
#define SMARTLAMP_PIN 9

#define COOLER_FULL_PIN 10
#define COOLER_HALF_PIN 11

#define HEATER_HALF_PIN 12
#define HEATER_FULL_PIN 13

#define DOOR_TASK_PERIOD 200
#define CLIMA_TASK_PERIOD 50
#define SMARTLAMP_TASK_PERIOD 200
#define SCHED_PERIOD 50

#define TEMP_PIN A0
#define LIGHTSENSOR_PIN A1

Scheduler sched;

void setup() {
    Serial.begin(115200);
    Serial.println("---- Avvio programma smart-room ----");

    SimpleButton *button = new Button(BUTTON_PIN);
    LightSensor *lightSensor = new LightSensorImpl(LIGHTSENSOR_PIN);
    Light *smartLamp = new Led(SMARTLAMP_PIN);

    TemperatureSensor *tempSensor = new TemperatureSensorImpl(TEMP_PIN);
    ProximitySensor *nearSensor = nearSensor;

    Light *cooler_half = new Led(COOLER_HALF_PIN);
    Light *cooler_full = new Led(COOLER_FULL_PIN);

    Light *heater_half = new Led(HEATER_HALF_PIN);
    Light *heater_full = new Led(HEATER_FULL_PIN);

    ClimaTask *climaTask = new ClimaTask(tempSensor, cooler_half, cooler_full, heater_half, heater_full);
    SmartLampTask *smartLampTask = new SmartLampTask(smartLamp, lightSensor, button);

    Presence *presence = new ProximitySensor(ECHO_PIN, TRIG_PIN);
    MyServo *servo = new Motor(SERVO_PIN);

    DoorTask *doorTask = new DoorTask(presence, servo);

    climaTask->init(CLIMA_TASK_PERIOD);
    doorTask->init(DOOR_TASK_PERIOD);
    smartLampTask->init(SMARTLAMP_TASK_PERIOD);

    sched.init(SCHED_PERIOD);

    sched.addTask(climaTask);
    sched.addTask(doorTask);
    sched.addTask(smartLampTask);
}

void loop() {
    sched.schedule();
}