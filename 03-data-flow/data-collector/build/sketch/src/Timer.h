#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\Timer.h"
#ifndef __TIMER__
#define __TIMER__

class Timer
{

public:
  Timer();
  void setupPeriod(int period);
  void waitForNextTick();
};

#endif
