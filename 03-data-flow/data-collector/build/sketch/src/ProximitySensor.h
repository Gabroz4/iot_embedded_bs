#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\ProximitySensor.h"
#ifndef __PROXIMITY_SENSOR__
#define __PROXIMITY_SENSOR__


class ProximitySensor { 
public:
    ProximitySensor(int echoPin, int trigPin);
    int getDistance();
private:
  int echoPin, trigPin;  
};

#endif