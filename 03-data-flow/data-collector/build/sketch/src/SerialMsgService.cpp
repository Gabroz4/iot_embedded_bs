#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\SerialMsgService.cpp"
#include "SerialMsgService.h"

#include "Arduino.h"

SerialMsgService::SerialMsgService(String name, unsigned long baudRate) : MsgService(name) {
    Serial.begin(baudRate);
    Serial.flush();
}

void SerialMsgService::sendMsg(String msg) {
    Serial.println(msg);
    Serial.flush();
}

void SerialMsgService::sendMsg(float msg) {
    Serial.println(msg);
    Serial.flush();
}

void SerialMsgService::sendMsg(int msg) {
    Serial.println(msg);
    Serial.flush();
}

bool SerialMsgService::isChannelAvailable() {
    return Serial.available();
}

bool SerialMsgService::isConnected() {
    return true;
}

char SerialMsgService::read() {
    return (char)Serial.read();
}
