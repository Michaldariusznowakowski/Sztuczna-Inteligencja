#ifndef LOGGER_INTERFACE_LOGGERINTERFACE_H
#define LOGGER_INTERFACE_LOGGERINTERFACE_H
#include <string>
class LoggerInterface {
 public:
  virtual void critical(const std::string &from, const std::string &msg) = 0;
  virtual void error(const std::string &from, const std::string &msg) = 0;
  virtual void info(const std::string &from, const std::string &msg) = 0;
};
#endif