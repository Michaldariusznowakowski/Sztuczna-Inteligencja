/**
 * @file stats.h
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief Header file for stats class. This class is responsible for storing and
 * manipulating statistics.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef STATS_H
#define STATS_H
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
  void reset() override;
  void startTimer() override;
  void stopTimer() override;
  unsigned long int getDuration() override;
  void setVariable(const std::string &name, const int &num) override;
  void incrementVariable(const std::string &name) override;
  int getVariable(const std::string &name, int *output) override;
};
#endif
