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

#include <algorithm>
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
  if (column >= chessboard.size()) {
    this->ptr_logger_->critical(
        "Chessboard::generateNextColumn",
        "Selected column number is greater than or equal to vector max size!");
    return 1;
  }
  if (boostMode) {
    for (int i = 0; i < chessboard.size(); i++) {
      bool skip = false;
      std::vector<int> copy(chessboard);
      for (int j = 0; j < column; j++) {
        // Check if copy has i in one of values
        if (copy[j] == i) {
          skip = true;
          break;
        }
        // check if copy i is diagonal to j
        if (abs(copy[j] - i) == abs(j - column)) {
          skip = true;
          break;
        }
      }
      if (!skip) {
        copy[column] = i;
        queue->push(copy);
        this->ptr_stats_->incrementVariable("generatedStates");
      }
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
int Chessboard::H2Calculate(const std::vector<int> &vec,
                            const unsigned short &column) {
  int vecSize = vec.size();
  if (column == vecSize) {
    return 0;
  }
  int columnToCheck = vecSize - column - 1;
  int sum = 0;
  sum += columnToCheck;
  int row = vec[column];
  for (size_t k = 0; k < columnToCheck; k++) {
    for (size_t i = 0; i < vecSize; i++) {
      if (row + 1 + k == i) {
        sum++;
      } else if (abs(row - vecSize + int(k)) == i) {
        sum++;
      }
    }
  }
  return sum;
}
void Chessboard::H2(unsigned short size, const bool &boostMode) {
  std::vector<int> vec;
  for (size_t i = 0; i < size; i++) {
    vec.emplace_back(-1);
  }
  this->cheesboard_pos_ = vec;
  std::queue<std::vector<int>> queue;
  this->ptr_stats_->startTimer();
  auto vecOutput = this->H2Process(0, vec, boostMode);
  this->cheesboard_pos_ = vecOutput;
  this->ptr_stats_->stopTimer();
}
std::vector<int> Chessboard::H2Process(int skip, std::vector<int> vec,
                                       const bool &boostMode) {
  std::string textTest = "[";
  for (size_t i = 0; i < vec.size(); i++) {
    textTest += std::to_string(vec[i]) + " ";
  }
  textTest += "]";
  this->ptr_logger_->info("Chessboard::H2Process", "Checking: " + textTest);
  std::vector<int> output;
  if (skip == vec.size()) {
    if (!this->checkIfCanAttack(vec)) {
      return vec;
    }
    return output;
  }
  std::vector<std::pair<std::vector<int>, int>> vecPair;
  std::queue<std::vector<int>> queueNextColumn;
  this->generateNextColumn(vec, &queueNextColumn, skip, boostMode);
  if (queueNextColumn.empty()) {
    return output;
  }
  while (!queueNextColumn.empty()) {
    auto vec = queueNextColumn.front();
    queueNextColumn.pop();
    vecPair.emplace_back(vec, this->H2Calculate(vec, skip));
  }
  std::sort(vecPair.begin(), vecPair.end(),
            [](const std::pair<std::vector<int>, int> &a,
               const std::pair<std::vector<int>, int> &b) {
              return a.second < b.second;
            });
  size_t sizeVecPair = vecPair.size();
  for (size_t i = 0; i < sizeVecPair; i++) {
    std::vector<int> vecNew(vecPair[i].first);
    std::vector<int> outputNew;
    outputNew = this->H2Process(skip + 1, vecNew, boostMode);
    if (!outputNew.empty()) {
      return outputNew;
    } else {
      continue;
    }
  }
  return output;
}
int Chessboard::H3Calculate(const std::vector<int> &vec,
                            const unsigned short &column) {
  int vecSize = vec.size();
  if (column == vecSize) {
    return 0;
  }
  int sum = 0;
  for (size_t i = 0; i <= column; i++) {
    for (size_t j = i + 1; j <= column; j++) {
      if (vec[i] == vec[j]) {
        sum++;
      } else if (abs(vec[i] - vec[j]) == abs(int(i) - int(j))) {
        sum++;
      }
    }
  }
  return sum;
}
void Chessboard::H3(unsigned short size, const bool &boostMode) {
  std::vector<int> vec;
  for (size_t i = 0; i < size; i++) {
    vec.emplace_back(-1);
  }
  this->cheesboard_pos_ = vec;
  std::queue<std::vector<int>> queue;
  this->ptr_stats_->startTimer();
  auto vecOutput = this->H3Process(0, vec, boostMode);
  this->cheesboard_pos_ = vecOutput;
  this->ptr_stats_->stopTimer();
}
std::vector<int> Chessboard::H3Process(int skip, std::vector<int> vec,
                                       const bool &boostMode) {
  std::string textTest = "[";
  for (size_t i = 0; i < vec.size(); i++) {
    textTest += std::to_string(vec[i]) + " ";
  }
  textTest += "]";
  this->ptr_logger_->info("Chessboard::H3Process", "Checking: " + textTest);
  std::vector<int> output;
  if (skip == vec.size()) {
    if (!this->checkIfCanAttack(vec)) {
      return vec;
    }
    return output;
  }
  std::vector<std::pair<std::vector<int>, int>> vecPair;
  std::queue<std::vector<int>> queueNextColumn;
  this->generateNextColumn(vec, &queueNextColumn, skip, boostMode);
  if (queueNextColumn.empty()) {
    return output;
  }
  while (!queueNextColumn.empty()) {
    auto vec = queueNextColumn.front();
    queueNextColumn.pop();
    vecPair.emplace_back(vec, this->H3Calculate(vec, skip));
  }
  std::sort(vecPair.begin(), vecPair.end(),
            [](const std::pair<std::vector<int>, int> &a,
               const std::pair<std::vector<int>, int> &b) {
              return a.second > b.second;
            });
  size_t sizeVecPair = vecPair.size();
  for (size_t i = 0; i < sizeVecPair; i++) {
    std::vector<int> vecNew(vecPair[i].first);
    std::vector<int> outputNew;
    outputNew = this->H3Process(skip + 1, vecNew, boostMode);
    if (!outputNew.empty()) {
      return outputNew;
    } else {
      continue;
    }
  }
  return output;
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
    if (!this->checkIfCanAttack(vec)) {
      if (vec.back() == -1) {
        continue;
      }
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
// P ← P0
// evaluate(P)
// gen ← 0
// best ← min(evaluate(P))
// while {gen < genmax ∧ evaluate(P(best)) > ffmax} do
// Pn ← selection(P)
// crossover(Pn)
// mutation(Pn)
// evaluate(Pn)
// best ← min(evaluate(Pn))
// P ← Pn
// gen ← gen + 1
// end while
// return P(best), evaluate(P(best))

int Chessboard::evolutionAlgorithm(const unsigned short &size,
                                   const unsigned short &populationSize,
                                   const unsigned short &mutationRate,
                                   const unsigned short &maxIterations) {}
