/**
 * @file plotstats.h
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief Header file for plotstats class. This class is responsible for
 * plotting stats.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef PLOTSTATS_H
#define PLOTSTATS_H
#include <matplot/matplot.h>

#include <string>
#include <vector>

class PlotStats {
 private:
  PlotStats() = default;

 public:
  /**
   * @brief Plot stats for queens problem.
   *
   * @param title
   * @param times
   * @param generatedStates
   * @param checkedStates
   */
  static void plotQueensStats(const std::string &title,
                              const std::vector<unsigned long int> &times,
                              const std::vector<int> &generatedStates,
                              const std::vector<int> &checkedStates,
                              const std::vector<unsigned int> &sizes) {
    auto figure = matplot::figure();
    figure->title(title);
    auto ax = matplot::subplot(3, 1, 0);
    matplot::bar(ax, sizes, times);
    matplot::title(ax, "Time duration");

    auto ax2 = matplot::subplot(3, 1, 1);
    matplot::bar(ax2, sizes, generatedStates);
    matplot::title(ax2, "States generated");

    auto ax3 = matplot::subplot(3, 1, 2);
    matplot::bar(ax3, sizes, checkedStates);
    matplot::title(ax3, "States checked");

    // show the plot without blocking the execution
    figure->draw();
  }
};
#endif