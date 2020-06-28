#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid); 
  int Pid();                                // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  void Calc_CpuUtil();
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  bool operator>(Process const& a) const;

  // TODO: Declare any necessary private members
 private:
  int pid;
  float cpu_util = 0.0;
  std::vector<std::string> cpu_values{};
  double uptime, time_secs, prev_uptime = 0.0, prev_time_secs = 0.0;
  double utime, prev_utime , stime, prev_stime, cutime, prev_cutime, cstime, prev_cstime, start_time, total_time, prev_total_time = 0, prev_start_time;
  //long totald = 0;
};

#endif