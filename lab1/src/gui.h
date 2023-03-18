/**
 * @file gui.h
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief Implementation of gui class. This class is responsible for creating
 * gui.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef GUI_H
#define GUI_H
#include <memory>

#include "chessboard.h"
#include "loggerinterface.h"
#include "nana/gui.hpp"
#include "statsinterface.h"
class Gui {
 private:
  /**
   * @brief Pointer to logger class.
   *
   */
  std::shared_ptr<LoggerInterface> ptr_logger_;
  /**
   * @brief Pointer to stats class.
   *
   */
  std::shared_ptr<StatsInterface> ptr_stats_;
  /**
   * @brief Pointer to chessboard class.
   *
   */
  std::unique_ptr<Chessboard> ptr_chessboard_;
  /**
   * @brief This method will call DFS method from chessboard class.
   *
   * @param size
   * @return std::string
   */
  std::string findSolutionDFS(const unsigned int &size);
  /**
   * @brief This method will call BFS method from chessboard class.
   *
   * @param size
   * @return std::string
   */
  std::string findSolutionBFS(const unsigned int &size);
  /**
   * @brief This method will call DFS method from chessboard class multiple
   * times and will create plot with stats.
   *
   * @param start
   * @param end
   */
  void graphSolutionDFS(const unsigned int &start, const unsigned int &end);
  /**
   * @brief This method will call BFS method from chessboard class multiple
   * times and will create plot with stats.
   *
   * @param start
   * @param end
   */
  void graphSolutionBFS(const unsigned int &start, const unsigned int &end);
  /**
   * @brief Helper method to show result in message box.
   *
   * @param result
   * @param fm
   */
  void showResult(const std::string &result, const nana::form &fm);

 public:
  /**
   * @brief Construct a new Gui object.
   *
   * @param logger
   * @param stats
   */
  Gui(const std::shared_ptr<LoggerInterface> &logger,
      const std::shared_ptr<StatsInterface> &stats);
  /**
   * @brief Destroy the Gui object
   *
   */
  ~Gui();
  /**
   * @brief This method will create gui. And will run it. It will be blocking.
   *
   */
  void runLoop();
};

#endif
