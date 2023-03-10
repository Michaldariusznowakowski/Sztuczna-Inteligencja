#include <matplot/matplot.h>
#include <windows.h>

#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "chessboard.h"
#include "logger.h"
#include "stats.h"
int main() {
  auto ptrLogger = std::make_shared<Logger>();
  auto ptrStats = std::make_shared<Stats>();
  auto cd = std::make_shared<Chessboard>(ptrLogger, ptrStats);
  SetConsoleOutputCP(CP_UTF8);
  cd->BFS(4);
  int generated, checked;
  ptrStats->getVariable("generatedStates", &generated);
  ptrStats->getVariable("checkedStates", &checked);

  std::cout << "Solution:" << std::endl;
  std::cout << cd->dumpChessboard() << std::endl;
  std::cout << "Time:" << std::to_string(ptrStats->getDuration())
            << " microseconds." << std::endl;
  std::cout << "Generated states:" << std::to_string(generated) << std::endl;
  std::cout << "Checked states:" << std::to_string(checked) << std::endl;

  // std::vector<int> generatedStates;
  // std::vector<int> checkedStates;
  // std::vector<std::string> solutions;
  // std::vector<unsigned long int> time;
  // std::vector<int> x;
  // int MIN = 4;
  // int MAX = 19;
  // for (int i = MIN; i < MAX; i++) {
  //   ptrStats->setVariable("generatedStates", 0);
  //   ptrStats->setVariable("checkedStates", 0);

  //   cd->BFS(i);
  //   int generated, checked;
  //   ptrStats->getVariable("generatedStates", &generated);
  //   generatedStates.push_back(generated);
  //   ptrStats->getVariable("checkedStates", &checked);
  //   checkedStates.push_back(checked);
  //   time.push_back(ptrStats->getDuration());
  //   x.push_back(i);
  // }

  // using namespace matplot;
  // tiledlayout(3, 1);
  // auto ax1 = nexttile();
  // plot(ax1, x, time);
  // title(ax1, "Time duration");
  // auto ax2 = nexttile();
  // plot(ax2, x, generatedStates);
  // title(ax2, "States generated");
  // auto ax3 = nexttile();
  // plot(ax3, x, checkedStates);
  // title(ax3, "States checked");
  // show();
}