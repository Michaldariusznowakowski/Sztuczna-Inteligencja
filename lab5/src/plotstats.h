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
                              const std::string &titles1,
                              const std::string &titles2,
                              const std::vector<long long unsigned int> &x1,
                              const std::vector<double> &x2)
                              {
    std::vector<unsigned int> sizes;
    for (unsigned int i = 0; i < x1.size(); i++) {
      sizes.push_back(i + 1);
    }
    auto figure = matplot::figure();
    figure->title(title);
    auto ax = matplot::subplot(2, 1, 0);
    auto ax2 = matplot::subplot(2, 1, 1);
    matplot::bar(ax2, sizes, x1);
    matplot::title(ax2, titles1);
    
    std::vector<unsigned int> sizes2;
    for (unsigned int i = 0; i < x2.size(); i++) {
      sizes2.push_back(i + 1);
    }
    auto ax3 = matplot::subplot(2, 1, 2);
    matplot::bar(ax3, sizes2, x2);
    matplot::title(ax3, titles2);

    // show the plot and block the execution
    figure->draw();
    std::cout << "Press enter to continue..." << std::endl;
    std::cin.get();
    std::cin.get();

  }
};
#endif