#include <string>
#include <vector>
#include <iostream>
#include "processor.h"
#include "linux_parser.h"
using std::vector;
using std::string;

Processor::Processor(){
  user = 0;
  nice = 0; 
  system = 0;
  idle = 0;
  ioWait = 0;
  irq = 0;
  softIrq = 0;
  steal = 0;
  guest = 0;
  guest_nice = 0;

}

Processor::Processor(vector <string> cpu_values){ // constructor
     user = stoi(cpu_values[0]);
     nice = stoi(cpu_values[1]); 
     system = stoi(cpu_values[2]);
     idle = stoi(cpu_values[3]);
     ioWait = stoi(cpu_values[4]);
     irq = stoi(cpu_values[5]);
     softIrq = stoi(cpu_values[6]);
     steal = stoi(cpu_values[7]);
     guest = stoi(cpu_values[8]);
     guest_nice = stoi(cpu_values[9]);
     prevNonIdle = 0;
     prevUser = 0;
     prevNice = 0; 
     prevSystem = 0;
     prevIrq = 0; 
     prevSoftIrq = 0; 
     prevSteal= 0;
  }


// TODO: Return the aggregate CPU utilization


float Processor::Utilization() { 
  
  prevNonIdle = prevUser + prevNice + prevSystem + prevIrq + prevSoftIrq + prevSteal;
  nonIdle = user + nice + system + irq + softIrq + steal;
  
  prevTotal = prevIdle + prevNonIdle;
  total = idle + nonIdle;

// differentiate: actual value minus the previous one
  totald = total - prevTotal;
  idled = idle - prevIdle;

  cpu_percentage = (float)(totald - idled) / totald; //typecast into float for percentage
 
  prevUser = user;
  prevNice = nice;
  prevSystem = system;
  prevIrq = irq;
  prevSoftIrq = softIrq;
  prevSteal = steal;
  prevIdle = idle;
  prevNonIdle = nonIdle;

  
  return cpu_percentage; 
}