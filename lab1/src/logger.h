#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H
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