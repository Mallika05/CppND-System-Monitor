#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
#include <vector>
using namespace std;

class Processor {
 public:
  float Utilization();  // TODO : See src/processor.cpp
  Processor(vector<string> cpu_values); // constructor
  Processor();
     
  // TODO: Declare any necessary private members
 private:
   float cpu_percentage;
   int user, nice, system, idle, ioWait, irq, softIrq, steal, guest, guest_nice;
   int idled, total, totald, nonIdle, prevTotal = 0;
   int prevUser = 0, prevNice = 0, prevSystem = 0, prevIdle = 0, prevNonIdle = 0, prevIoWait = 0, prevIrq = 0, prevSoftIrq = 0, prevSteal = 0, prevGuest = 0, prevGuest_nice = 0;
};

#endif