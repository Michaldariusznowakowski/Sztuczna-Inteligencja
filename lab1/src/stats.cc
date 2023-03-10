#include "stats.h"
void Stats::startTimer() {
  this->start_time_ = std::chrono::system_clock::now();
}
void Stats::stopTimer() {
  this->total_time_ = std::chrono::system_clock::now() - this->start_time_;
}

void Stats::setVariable(const std::string &name, const int &num) {
  auto it = this->variables_.find(name);
  if (it == this->variables_.end()) {
    this->variables_.emplace(name, num);
  } else {
    it->second = num;
  }
}
unsigned long int Stats::getDuration() {
  return std::chrono::duration_cast<std::chrono::microseconds>(
             this->total_time_)
      .count();
}

void Stats::incrementVariable(const std::string &name) {
  auto it = this->variables_.find(name);
  if (it == this->variables_.end()) {
    this->variables_.emplace(name, 0);
  } else {
    it->second = it->second + 1;
  }
}
int Stats::getVariable(const std::string &name, int *output) {
  auto it = this->variables_.find(name);
  if (it == this->variables_.end()) {
    return -1;
  }
  *output = it->second;
  return 0;
}
