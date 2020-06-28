#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"
#include "format.h"
using std::ifstream;

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}                   

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key; 
  string value;
  float memUsed;
  float memTotal;
  float memFree; 
  float memAvail;
  float buffer;
  float cache; 
  float slab;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key=="MemTotal:"){
          memTotal = stoi(value);
        }
        else if(key=="MemFree:"){
          memFree = stoi(value);
        }
        else if(key=="MemAvailable:"){
          memAvail = stoi(value);
        }
        else if(key=="Buffers:"){
          buffer = stoi(value);
        }
        else if(key=="Cached:"){
          cache = stoi(value);
        }
        else if(key=="Slab:"){
          slab = stoi(value);
        }
      }
    }
  }
  memUsed = memTotal - memFree - memAvail - buffer - cache - slab;
  memUsed = memUsed /memTotal;
  return memUsed; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  long totalUptime;
  double uptime1;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    linestream >> uptime1;
  }
  totalUptime = (long) uptime1;// + uptime2;
  return totalUptime; 
}
std::vector<std::string> LinuxParser::CpuUtilization(int pid) { 
  string line, value;
  vector<string> cpu_values{};
  string fname = kProcDirectory + to_string(pid) + kStatFilename;
  std::ifstream filestream(fname);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    while(linestream >> value){
      cpu_values.push_back(value);    
    }
  }
  return cpu_values; 
}

// TODO: Read and return the number of jiffies for the system
/* long LinuxParser::Jiffies() { 
  return 0; 
}

// TODO: Read and return the number of active jiffies for a PID

// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; } */
// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUsage() { 

  string cpu;
  string line;
  string arr_cpu[10];
  vector<string> cpu_values{};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> arr_cpu[kUser_] >> arr_cpu[kNice_] >> arr_cpu[kSystem_] >> arr_cpu[kIdle_] >> arr_cpu[kIOwait_] >> arr_cpu[kIRQ_] >> arr_cpu[kSoftIRQ_] >> arr_cpu[kSteal_] >> arr_cpu[kGuest_] >> arr_cpu[kGuestNice_];
    for (int i = 0; i < 11; i++){
        cpu_values.push_back(arr_cpu[i]);
    }
  } 
  return cpu_values;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  int total_processes = 0;
  string line,  key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while(getline(filestream, line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key=="processes"){
          total_processes = stoi(value);
        }
      }
    }
  }
  return total_processes; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  int run_procs =0;
  string line,  key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while(getline(filestream, line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key=="procs_running"){
          run_procs = stoi(value);
        }
      }
    } 
  }
  return run_procs;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string cmdline, key;
  string line;
  string fname = (kProcDirectory + to_string(pid) + kStatusFilename);
  std::ifstream filestream(fname);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream istream(line);
    istream >> key >> cmdline;
  }
  return cmdline; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string ram;
  string line, key, value;
  string fname = kProcDirectory + to_string(pid) + kStatusFilename;
  std::ifstream filestream(fname);
  if (filestream.is_open()) {
    while(getline(filestream, line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key=="VmSize:"){
          ram = value;
          return std::to_string(stoi(ram) / 1024);
        }
      }
    }
  }
  return string("0"); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string uid;
  string line, key, value;
  string fname = kProcDirectory + to_string(pid) + kStatusFilename;
  std::ifstream filestream(fname);
  if (filestream.is_open()) {
    while(getline(filestream, line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "Uid:"){
          uid = value;
        }
      }
    }
  }
  return uid; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string username, userid;
  string uid = LinuxParser::Uid(pid);
  string line, user, x, extra;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> user >> x >> userid){
        if(userid == uid){
          username = user;
        }
      }
    }
  }
  return username; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  long uptime;
  string line, value;
  string fname = kProcDirectory + to_string(pid) + kStatFilename;
  std::ifstream filestream(fname);
  if (filestream.is_open()) {
    while(getline(filestream, line)){
      std::istringstream linestream(line);
      for(int i = 0; i < 22; i++){
        linestream >> value;
      }
    }
  }
  uptime = stol(value);
  return uptime; 
}