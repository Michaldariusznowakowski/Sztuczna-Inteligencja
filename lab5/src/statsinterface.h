/**
 * @file statsinterface.h
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief  Header file for stats interface. This class is responsible for
 * storing  and displaying statistics.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef STATSINTERFACE_H
#define STATSINTERFACE_H
#include <string>

class StatsInterface {
 public:
  /**
   * @brief Reset timer
   *
   */
  virtual void reset() = 0;
  /**
   * @brief Start timer
   *
   */
  virtual void startTimer() = 0;
  /**
   * @brief Stop timer
   *
   */
  virtual void stopTimer() = 0;
  /**
   * @brief Get duration of timer
   *
   * @return unsigned long int
   */
  virtual unsigned long int getDuration() = 0;
  /**
   * @brief Set variable
   *
   * @param name
   * @param num
   */
  virtual void setVariable(const std::string &name, const int &num) = 0;
  /**
   * @brief Increment variable
   *
   * @param name
   */
  virtual void incrementVariable(const std::string &name) = 0;
  /**
   * @brief Get variable
   *
   * @param name
   * @param output
   * @return int
   */
  virtual int getVariable(const std::string &name, int *output) = 0;
};
#endif