/**
 * @file chessboard.h
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief  Class for chessboard representation and operations on it.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <memory>
#include <queue>
#include <vector>

#include "loggerinterface.h"
#include "statsinterface.h"
class Chessboard {
 private:
  std::shared_ptr<LoggerInterface> ptr_logger_;
  std::shared_ptr<StatsInterface> ptr_stats_;
  std::vector<int> cheesboard_pos_;

 public:
  Chessboard(std::shared_ptr<LoggerInterface> logger,
             std::shared_ptr<StatsInterface> stats);
  /**
   * @brief Check if the queen can attack another queen
   *
   * @return true  One of the queens can attack the other
   * @return false  The queens cannot attack each other
   */
  bool checkIfCanAttack(const std::vector<int> &vec);
  /**
   * @brief Generate every variant of selected column.
   *
   * @param chessboard Input.
   * @param queue Output.
   * @param column Column to be generated.
   * @retval 1 Failure.
   * @retval 0 Success.
   */
  int generateNextColumn(const std::vector<int> &chessboard,
                         std::queue<std::vector<int>> *queue,
                         unsigned short column);
  /**
   * @brief Convert chessboard to string output.
   *
   * @return std::string
   */
  std::string dumpChessboard();
  /**
   * @brief DFS algorithm. Recursive function.
   *
   * @param vec
   * @param skip
   * @return int
   */
  int DFSprocess(const std::vector<int> &vec, const unsigned short &skip = 0);
  /**
   * @brief DFS algorithm.
   *
   * @param size
   */
  void DFS(unsigned short size);
  /**
   * @brief BFS algorithm. Recursive function.
   *
   * @param size
   */
  std::queue<std::vector<int>> BFSProcess(int skip, std::vector<int> vec);
  /**
   * @brief Get the Cheesboard Pos object
   *
   * @return std::vector<int>
   */
  std::vector<int> getCheesboardPos();
  /**
   * @brief BFS algorithm.
   *
   * @param size
   */
  void BFS(unsigned short size);
};
#endif