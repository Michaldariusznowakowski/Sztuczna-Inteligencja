/**
 * @file loggerinterface.h
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief  Header file for logger interface. This class is responsible for
 * logging messages.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef LOGGERINTERFACE_H
#define LOGGERINTERFACE_H
#include <string>
class LoggerInterface {
 public:
  /**
   * @brief Log critical message
   *
   * @param from
   * @param msg
   */
  virtual void critical(const std::string &from, const std::string &msg) = 0;
  /**
   * @brief Log error message
   *
   * @param from
   * @param msg
   */
  virtual void error(const std::string &from, const std::string &msg) = 0;
  /**
   * @brief Log info message
   *
   * @param from
   * @param msg
   */
  virtual void info(const std::string &from, const std::string &msg) = 0;
};
#endif