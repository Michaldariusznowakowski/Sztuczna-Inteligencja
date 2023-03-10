#ifndef CHESSBOARD_CHESSBOARD_H
#define CHESSBOARD_CHESSBOARD_H
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
  int DFSprocess(const std::vector<int> &vec, const unsigned short &skip = 0);

  void DFS(unsigned short size);
  std::queue<std::vector<int>> BFSProcess(std::queue<std::vector<int>> *queue,
                                          int skip, int vecSize);
  void BFS(unsigned short size);
};
#endif