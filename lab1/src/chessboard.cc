#include "chessboard.h"

#include <memory>
#include <string>
#include <vector>

bool Chessboard::checkIfCanAttack(const std::vector<int> &vec) {
  this->ptr_stats_->incrementVariable("checkedStates");
  // check if same row
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i] == -1) {
      continue;
    }
    for (size_t j = 0; j < vec.size(); j++) {
      if (vec[j] == -1) {
        continue;
      }
      if (i != j) {
        if (vec[i] == vec[j]) {
          return true;
        }
      }
    }
  }
  // check if diagonal using absolute value
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i] == -1) {
      continue;
    }
    for (size_t j = 0; j < vec.size(); j++) {
      if (vec[j] == -1) {
        continue;
      }
      if (i != j) {
        if (abs(vec[i] - vec[j]) == abs(i - j)) {
          return true;
        }
      }
    }
  }
  return false;
}
int Chessboard::generateNextColumn(const std::vector<int> &chessboard,
                                   std::queue<std::vector<int>> *queue,
                                   unsigned short column) {
  if (column < 0) {
    this->ptr_logger_->critical("Chessboard::generateNextColumn",
                                "column cannot be smaller than 0!");
    return 1;
  }
  if (column > chessboard.size()) {
    this->ptr_logger_->critical(
        "Chessboard::generateNextColumn",
        "Selected column number is bigger than vector max size!");
    return 1;
  }
  for (int i = 0; i < chessboard.size(); i++) {
    std::vector<int> copy(chessboard);
    copy[column] = i;
    queue->push(copy);
    this->ptr_stats_->incrementVariable("generatedStates");
  }
  return 0;
}
std::string Chessboard::dumpChessboard() {
  if (this->cheesboard_pos_.size() == 0) {
    this->ptr_logger_->error("Chessboard::dumpChessboard",
                             "chessboard_pos_ is empty! Nothing to dump!");
    return "";
  }
  std::string output = "";
  size_t size = cheesboard_pos_.size();
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      if (j == cheesboard_pos_[i]) {
        output += " ♛";
      } else {
        output += " ☐";
      }
    }
    output += "\n";
  }
  return output;
}
int Chessboard::DFSprocess(const std::vector<int> &vec,
                           const unsigned short &skip) {
  size_t size = vec.size();
  if (skip == size) {
    this->cheesboard_pos_ = vec;
    return 0;
  }
  for (size_t i = skip; i < size; i++) {
    std::queue<std::vector<int>> queue;
    this->generateNextColumn(vec, &queue, i);
    bool found = false;
    for (size_t i = 0; i < size; i++) {
      auto vecNew = queue.front();
      queue.pop();
      if (!checkIfCanAttack(vecNew)) {
        if (DFSprocess(vecNew, skip + 1) == 0) {
          return 0;
        } else {
          found = false;
        }
      }
    }
    if (found == false) {
      return 1;
    }
  }
  return 1;
}
void Chessboard::DFS(unsigned short size) {
  this->ptr_stats_->startTimer();
  std::vector<int> vec;
  for (size_t i = 0; i < size; i++) {
    vec.emplace_back(-1);
  }
  this->cheesboard_pos_ = vec;
  this->DFSprocess(vec, 0);
  this->ptr_stats_->stopTimer();
}
std::queue<std::vector<int>> Chessboard::BFSProcess(
    std::queue<std::vector<int>> *queue, int skip, int vecSize) {
  int size = queue->size();
  // if (skip == vecSize) {
  //   return ;
  // }
  std::queue<std::vector<int>> queueOutput;
  std::queue<std::vector<int>> queueCopy(*queue);
  for (size_t i = 0; i < size; i++) {
    auto vec = queueCopy.front();
    queueCopy.pop();
    this->generateNextColumn(vec, &queueOutput, skip);
  }
  if (skip == vecSize) {
    return queueOutput;
  } else {
    auto newQueue = this->BFSProcess(&queueOutput, skip + 1, vecSize);
    for (size_t i = 0; i < newQueue.size(); i++) {
      queue->push(newQueue.front());
      newQueue.pop();
    }
    return *queue;
  }
}
void Chessboard::BFS(unsigned short size) {
  std::vector<int> vec;
  for (size_t i = 0; i < size; i++) {
    vec.emplace_back(-1);
  }
  this->cheesboard_pos_ = vec;
  std::queue<std::vector<int>> queue;
  this->ptr_stats_->startTimer();
  queue.push(vec);
  this->BFSProcess(&queue, 0, size);
  size_t queueSize = queue.size();
  for (size_t i = 0; i < queueSize; i++) {
    auto vec = queue.front();
    queue.pop();
    if (!this->checkIfCanAttack(vec)) {
      this->cheesboard_pos_ = vec;
      break;
    }
  }
  this->ptr_stats_->stopTimer();
}
Chessboard::Chessboard(std::shared_ptr<LoggerInterface> logger,
                       std::shared_ptr<StatsInterface> stats) {
  this->ptr_logger_ = logger;
  this->ptr_stats_ = stats;
}
