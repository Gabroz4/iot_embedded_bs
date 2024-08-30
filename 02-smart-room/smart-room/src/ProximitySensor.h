#ifndef __PROXIMITY_SENSOR__
#define __PROXIMITY_SENSOR__

#include "Presence.h"

class ProximitySensor : public Presence { 
public:
    ProximitySensor(int echoPin, int trigPin);
    bool isNear();
private:
  int echoPin, trigPin;  
};

#endif