#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System(){
  kernel = "default";
  memUsed = 0.0;
  OS = "default";
  totalProcesses = 0;
  runningProcesses = 0;
  uptime = 0;
  processes_ = {};
}

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    vector <string> cpu_values = LinuxParser::CpuUsage();
    Processor proc1(cpu_values);
    this->cpu_ = proc1;
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    processes_.clear();
    vector<int> pids = LinuxParser::Pids();
    Process *proc = nullptr;
    int psize = pids.size();
    for(int i = 0; i < psize; i++){
        proc = new Process(pids[i]);
        processes_.emplace_back(*proc);
    }
    for (auto& process : processes_) { // update cpu utilization
        process.CpuUtilization();
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    kernel = LinuxParser::Kernel();
    return kernel; 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    memUsed = LinuxParser::MemoryUtilization();
    return memUsed; 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    OS = LinuxParser::OperatingSystem();
    return OS; 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    runningProcesses = LinuxParser::RunningProcesses();
    return runningProcesses; 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    totalProcesses = LinuxParser::TotalProcesses();
    return totalProcesses; 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    uptime = LinuxParser::UpTime();
    return uptime; 
}