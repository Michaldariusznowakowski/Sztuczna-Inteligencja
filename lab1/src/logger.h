/**
 * @file logger.h
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief Header file for logger class. This class is responsible for logging
 * messages.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef LOGGER_H
#define LOGGER_H
#include "loggerinterface.h"
class Logger : public LoggerInterface {
 private:
  void sendMsg(const std::string &msg);

 public:
  void critical(const std::string &from, const std::string &msg) override;
  void error(const std::string &from, const std::string &msg) override;
  void info(const std::string &from, const std::string &msg) override;
};
#endif