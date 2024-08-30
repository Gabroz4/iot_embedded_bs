#include <Arduino.h>
#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino"
#include "src/ProximitySensor.h"
#include "src/BluetoothMsgService.h"
#include "src/ProducerTask.h"
#include "src/Scheduler.h"

#define BT_MSG_SERVICE_NAME "BT"
#define BT_MSG_SERVICE_BAUD_RATE 9600
#define BT_TXD_PIN 5
#define BT_RXD_PIN 6
#define BT_STATE_PIN 7
#define PRODUCER_TASK_PERIOD 5000
#define SCHED_PERIOD 100

#define TRIGGER_PIN 11
#define ECHO_PIN 10

Scheduler sched;

#line 19 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino"
void setup();
#line 30 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino"
void loop();
#line 19 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino"
void setup() {
    ProximitySensor *sensor = new ProximitySensor(ECHO_PIN, TRIGGER_PIN);
    BluetoothMsgService* bt =new BluetoothMsgService(BT_MSG_SERVICE_NAME, BT_TXD_PIN, BT_RXD_PIN, BT_STATE_PIN, BT_MSG_SERVICE_BAUD_RATE);

    ProducerTask* producerTask = new ProducerTask(bt, sensor);
    producerTask->init(PRODUCER_TASK_PERIOD);

    sched.init(SCHED_PERIOD);
    sched.addTask(producerTask);
}

void loop() {
    sched.schedule();
}

