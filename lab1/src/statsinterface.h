#ifndef STATS_INTERFACE_STATSINTERFACE_H
#define STATS_INTERFACE_STATSINTERFACE_H
#include <string>

class StatsInterface {
 public:
  virtual void startTimer() = 0;
  virtual void stopTimer() = 0;
  virtual unsigned long int getDuration() = 0;
  virtual void setVariable(const std::string &name, const int &num) = 0;
  virtual void incrementVariable(const std::string &name) = 0;
  virtual int getVariable(const std::string &name, int *output) = 0;
};
#endif