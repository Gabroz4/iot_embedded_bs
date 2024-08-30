#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\ProximitySensor.cpp"
#include "ProximitySensor.h"
#include "Arduino.h"

ProximitySensor::ProximitySensor(int echoPin, int trigPin) {
    this->echoPin = echoPin;
    this->trigPin = trigPin;
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
}

int ProximitySensor::getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    int duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2;
    
    return distance;
}