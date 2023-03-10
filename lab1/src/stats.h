#ifndef STATS_STATS_H
#define STATS_STATS_H
#include <chrono>
#include <map>
#include <string>

#include "statsinterface.h"
class Stats : public StatsInterface {
 private:
  std::map<std::string, int> variables_;
  std::chrono::_V2::system_clock::time_point start_time_;
  std::chrono::nanoseconds total_time_;

 public:
  void startTimer() override;
  void stopTimer() override;
  unsigned long int getDuration() override;
  void setVariable(const std::string &name, const int &num) override;
  void incrementVariable(const std::string &name) override;
  int getVariable(const std::string &name, int *output) override;
};
#endif
