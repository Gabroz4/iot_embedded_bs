#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\Light.h"
#ifndef __LIGHT__
#define __LIGHT__

class Light {
public:
  virtual void switchOn() = 0;
  virtual void switchOff() = 0;    
};

#endif

