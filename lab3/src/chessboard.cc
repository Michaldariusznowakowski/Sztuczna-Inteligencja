/**
 * @file chessboard.cc
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief  Implementation of chessboard class.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
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
                                   unsigned short column,
                                   const bool &boostMode) {
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
  if (boostMode == true) {
    for (int i = 0; i < chessboard.size(); i++) {
      std::vector<int> copy(chessboard);
      // skip if queen is already in this row
      if (column != 0 && chessboard[column - 1] == i) {
        continue;
      }
      // Skip if queen is diagonal to previous queen
      if (column != 0 && abs(chessboard[column - 1] - i) == 1) {
        continue;
      }
      copy[column] = i;
      queue->push(copy);
      this->ptr_stats_->incrementVariable("generatedStates");
    }
  } else {
    for (int i = 0; i < chessboard.size(); i++) {
      std::vector<int> copy(chessboard);
      copy[column] = i;
      queue->push(copy);
      this->ptr_stats_->incrementVariable("generatedStates");
    }
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
std::vector<int> Chessboard::getCheesboardPos() {
  return this->cheesboard_pos_;
}
int Chessboard::DFSprocess(const std::vector<int> &vec,
                           const unsigned short &skip, const bool &boostMode) {
  size_t size = vec.size();
  if (skip == size) {
    this->cheesboard_pos_ = vec;
    return 0;
  }
  for (size_t i = skip; i < size; i++) {
    std::queue<std::vector<int>> queue;
    this->generateNextColumn(vec, &queue, i, boostMode);
    bool found = false;
    while (!queue.empty()) {
      auto vecNew = queue.front();
      queue.pop();
      std::string output = "[";
      for (size_t i = 0; i < vecNew.size(); i++) {
        output += std::to_string(vecNew[i]) + " ";
      }
      output += "]";
      this->ptr_logger_->info("Chessboard::DFSprocess", "Checking: " + output);
      if (!checkIfCanAttack(vecNew)) {
        if (DFSprocess(vecNew, skip + 1, boostMode) == 0) {
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
void Chessboard::DFS(unsigned short size, const bool &boostMode) {
  this->ptr_stats_->startTimer();
  std::vector<int> vec;
  for (size_t i = 0; i < size; i++) {
    vec.emplace_back(-1);
  }
  this->cheesboard_pos_ = vec;
  this->DFSprocess(vec, 0, boostMode);
  this->ptr_stats_->stopTimer();
}
std::queue<std::vector<int>> Chessboard::BFSProcess(int skip,
                                                    std::vector<int> vec,
                                                    const bool &boostMode) {
  if (skip == vec.size()) {
    std::queue<std::vector<int>> queue;
    return queue;
  }
  std::queue<std::vector<int>> queue;
  this->generateNextColumn(vec, &queue, skip, boostMode);
  std::queue<std::vector<int>> copy(queue);
  while (!copy.empty()) {
    auto vec = copy.front();
    copy.pop();
    auto qFromRec = this->BFSProcess(skip + 1, vec, boostMode);
    while (!qFromRec.empty()) {
      queue.push(qFromRec.front());
      qFromRec.pop();
    }
  }
  return queue;
}

void Chessboard::BFS(unsigned short size, const bool &boostMode) {
  std::vector<int> vec;
  for (size_t i = 0; i < size; i++) {
    vec.emplace_back(-1);
  }
  this->cheesboard_pos_ = vec;
  this->ptr_stats_->startTimer();
  auto queue = this->BFSProcess(0, vec, boostMode);
  while (!queue.empty()) {
    auto vec = queue.front();
    queue.pop();
    std::string output = "[";
    for (size_t i = 0; i < vec.size(); i++) {
      output += std::to_string(vec[i]) + " ";
    }
    output += "]";
    this->ptr_logger_->info("Chessboard::BFS", "Checking: " + output);
    if (vec.back() == -1) {
      continue;
    }
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
