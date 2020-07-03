#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int p) : pid(p) {
   Calc_CpuUtil();
}

// TODO: Return this process's ID
int Process::Pid() { 
   return pid; 
}

// TODO: Return this process's CPU utilization
void Process::Calc_CpuUtil() { 
  vector<string> cpu_values{};
  cpu_values = LinuxParser::CpuUtilization(pid);
  float hertz = (float) sysconf(_SC_CLK_TCK);
  utime = stol(cpu_values[13]);
  stime = stol(cpu_values[14]);
  cutime = stol(cpu_values[15]);
  cstime = stol(cpu_values[16]);
  start_time = stol(cpu_values[17]);
  total_time = utime + stime + cutime + cstime;
  prev_total_time = prev_utime + prev_stime + prev_cutime + prev_cstime;
  float totald = total_time - prev_total_time;
  uptime = (float) LinuxParser::UpTime();
  time_secs = (uptime - (start_time/hertz)) - prev_time_secs;
  cpu_util = (totald/hertz) / time_secs;
}

float Process::CpuUtilization() const{
   return cpu_util;
}

// TODO: Return the command that generated this process
string Process::Command() { 
   string command = LinuxParser::Command(pid);
   return command; 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
   string ram = LinuxParser::Ram(pid);
   return ram; 
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
   string user = LinuxParser::User(pid);
   return user;
}

// TODO: Return the age of this process (in seconds)
long Process::UpTime() { 
   long uptime = LinuxParser::UpTime(pid);
   long sys_uptime = LinuxParser::UpTime();
   return sys_uptime - uptime;
}

// TODO: Overload the "less than" comparison operator for Process objsects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
   return (this->CpuUtilization() > a.CpuUtilization()); 
}

bool Process::operator>(Process const& a) const {
  return (this->CpuUtilization() < a.CpuUtilization());
}