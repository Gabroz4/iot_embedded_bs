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