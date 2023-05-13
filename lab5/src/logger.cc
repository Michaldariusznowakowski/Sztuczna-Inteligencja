/**
 * @file logger.cc
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief  Implementation of logger class. This class is responsible for logging
 * messages.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "logger.h"

#include <iostream>
#include <string>
void Logger::sendMsg(const std::string &msg) {
  std::cout << "[Logger] " + msg << std::endl;
}

void Logger::critical(const std::string &from, const std::string &msg) {
  this->sendMsg("[Critical] [" + from + "]: " + msg);
};
void Logger::error(const std::string &from, const std::string &msg) {
  this->sendMsg("[Error] [" + from + "]: " + msg);
}
void Logger::info(const std::string &from, const std::string &msg) {
  this->sendMsg("[Info] [" + from + "]: " + msg);
}
