#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\Led.h"
#ifndef __LED__
#define __LED__

#include "Light.h"

class Led: public Light { 
public:
  Led(int pin);
  void switchOn();
  void switchOff();    
private:
  int pin;  
};

#endif
