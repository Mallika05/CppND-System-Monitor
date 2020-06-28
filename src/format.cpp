#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long const seconds) { 
    long uptime_secs = seconds;
    string str_secs;
    string str_mins;
    string str_hrs;
    string elapsed_time;
    int hours = uptime_secs / 3600;
    uptime_secs = uptime_secs % 3600;
    int minutes = uptime_secs / 60;
    uptime_secs = uptime_secs % 60;
    if(hours < 10)
        str_hrs = DoubleDigit(to_string(hours));
    else 
        str_hrs = to_string(hours);

    if(minutes < 10)
        str_mins = DoubleDigit(to_string(minutes));
    else 
        str_mins = to_string(minutes);

    if(uptime_secs < 10)
        str_secs = DoubleDigit(to_string(uptime_secs));
    else 
        str_secs = to_string(uptime_secs);

    elapsed_time = str_hrs + ":" + str_mins + ":" + str_secs;
    return elapsed_time;
}
string Format::DoubleDigit(string s){
    string doub = s.insert(0, 2 - s.length(), '0');
    return doub;
}