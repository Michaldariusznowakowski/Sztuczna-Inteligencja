/**
 * @file gui.cc
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "gui.h"

#include <memory>
#include <nana/gui.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>

#include "chessboard.h"
#include "loggerinterface.h"
#include "plotstats.h"
#include "statsinterface.h"
std::string Gui::findSolutionBFS(const unsigned int &size,
                                 const bool &boostMode) {
  this->ptr_chessboard_->BFS(size, boostMode);
  return this->ptr_chessboard_->dumpChessboard();
}
std::string Gui::findSolutionDFS(const unsigned int &size,
                                 const bool &boostMode) {
  this->ptr_chessboard_->DFS(size, boostMode);
  return this->ptr_chessboard_->dumpChessboard();
}
Gui::Gui(const std::shared_ptr<LoggerInterface> &logger,
         const std::shared_ptr<StatsInterface> &stats)
    : ptr_logger_(logger), ptr_stats_(stats) {
  ptr_chessboard_ = std::make_unique<Chessboard>(ptr_logger_, ptr_stats_);
}
void Gui::showResult(const std::string &result, const nana::form &fm) {
  this->ptr_logger_->info("Gui::showResult", "Showing result.");
  nana::msgbox msg(fm, "Result");
  msg.icon(nana::msgbox::icon_information);
  int checkedStates = 0;
  if (this->ptr_stats_->getVariable("checkedStates", &checkedStates) == 0) {
    msg << "Checked states: " << checkedStates << std::endl;
  } else {
    msg << "Checked states: "
        << "N/A" << std::endl;
  }
  int generatedStates = 0;
  if (this->ptr_stats_->getVariable("generatedStates", &generatedStates) == 0) {
    msg << "Generated states: " << generatedStates << std::endl;
  } else {
    msg << "Generated states: "
        << "N/A" << std::endl;
  }
  unsigned long time = this->ptr_stats_->getDuration();
  msg << "Time: " << time << " nanoseconds." << std::endl;
  msg << "Solution: " << std::endl;
  msg << result;
  msg.show();
}
void Gui::graphSolutionBFS(const unsigned int &start, const unsigned int &end,
                           const bool &boostMode) {
  std::vector<unsigned long int> times;
  std::vector<int> checkedStates;
  std::vector<int> generatedStates;
  std::vector<unsigned int> sizes;
  for (unsigned int i = start; i <= end; i++) {
    sizes.push_back(i);
    this->ptr_stats_->reset();
    this->ptr_chessboard_->BFS(i);
    times.push_back(this->ptr_stats_->getDuration());
    int checkedStatesTmp = 0;
    int generatedStatesTmp = 0;
    this->ptr_stats_->getVariable("checkedStates", &checkedStatesTmp);
    this->ptr_stats_->getVariable("generatedStates", &generatedStatesTmp);
    checkedStates.push_back(checkedStatesTmp);
    generatedStates.push_back(generatedStatesTmp);
    this->ptr_logger_->info(
        "Gui::graphSolutionBFS",
        "Graphed BFS solution for size: " + std::to_string(i));
  }
  this->ptr_logger_->info(
      "Gui::graphSolutionBFS",
      "Plotting stats for BFS size:" + std::to_string(times.size()));
  PlotStats::plotQueensStats("Stats for BFS", times, checkedStates,
                             generatedStates, sizes);
}
void Gui::graphSolutionDFS(const unsigned int &start, const unsigned int &end,
                           const bool &boostMode) {
  std::vector<unsigned long int> times;
  std::vector<int> checkedStates;
  std::vector<int> generatedStates;
  std::vector<unsigned int> sizes;
  for (unsigned int i = start; i <= end; i++) {
    sizes.push_back(i);
    this->ptr_stats_->reset();
    this->ptr_chessboard_->DFS(i);
    times.push_back(this->ptr_stats_->getDuration());
    int checkedStatesTmp = 0;
    int generatedStatesTmp = 0;
    this->ptr_stats_->getVariable("checkedStates", &checkedStatesTmp);
    this->ptr_stats_->getVariable("generatedStates", &generatedStatesTmp);
    checkedStates.push_back(checkedStatesTmp);
    generatedStates.push_back(generatedStatesTmp);
    this->ptr_logger_->info(
        "Gui::graphSolutionDFS",
        "Graphed DFS solution for size: " + std::to_string(i));
  }
  this->ptr_logger_->info(
      "Gui::graphSolutionDFS",
      "Plotting stats for DFS size:" + std::to_string(times.size()));
  PlotStats::plotQueensStats("Stats for DFS", times, checkedStates,
                             generatedStates, sizes);
}
Gui::~Gui() { this->ptr_chessboard_ = nullptr; }
void Gui::runLoop() {
  this->ptr_logger_->info("Gui::runLoop", "Starting GUI loop.");
  nana::form fm;
  fm.caption("N-Queens problem");
  // Make check box for boost mode. Using nana library.
  nana::checkbox boostMode{fm, nana::rectangle{10, 10, 200, 20}};
  nana::button findSolBFS(fm, "Find solution BFS");
  nana::button findSolDFS(fm, "Find solution DFS");
  nana::button graphSolBFS(fm, "Graph solutions BFS");
  nana::button graphSolDFS(fm, "Graph solutions DFS");
  nana::button exit(fm, "Exit program. ❗");
  findSolBFS.events().click([&] {
    this->ptr_logger_->info("Gui::runLoop", "Clicked find solution BFS.");
    this->ptr_stats_->reset();
    nana::inputbox ibox(fm, "Find solution BFS");
    nana::inputbox::integer size("Size of chessboard", 4, 4, 20, 1);
    if (ibox.show(size)) {
      this->ptr_chessboard_->BFS(size.value(), boostMode.checked());
      std::string result = this->ptr_chessboard_->dumpChessboard();
      this->showResult(result, fm);
    }
  });
  findSolDFS.events().click([&] {
    this->ptr_logger_->info("Gui::runLoop", "Clicked find solution DFS.");
    this->ptr_stats_->reset();
    nana::inputbox ibox(fm, "Find solution DFS");
    nana::inputbox::integer size("Size of chessboard", 4, 4, 30, 1);
    if (ibox.show(size)) {
      std::string result =
          this->findSolutionDFS(size.value(), boostMode.checked());
      this->showResult(result, fm);
    }
  });
  graphSolBFS.events().click([&] {
    this->ptr_logger_->info("Gui::runLoop", "Clicked graph solutions BFS.");
    nana::inputbox ibox(fm, "Graph solutions BFS");
    nana::inputbox::integer start("Start size", 4, 4, 30, 1);
    if (ibox.show(start)) {
      nana::inputbox::integer end("End size", start.value(), start.value(), 20,
                                  1);
      if (ibox.show(end)) {
        this->graphSolutionBFS(start.value(), end.value(), boostMode.checked());
      }
    }
  });
  graphSolDFS.events().click([&] {
    this->ptr_logger_->info("Gui::runLoop", "Clicked graph solutions DFS.");
    nana::inputbox ibox(fm, "Graph solutions DFS");
    nana::inputbox::integer start("Start size", 4, 4, 20, 1);
    if (ibox.show(start)) {
      nana::inputbox::integer end("End size", start.value(), start.value(), 20,
                                  1);
      if (ibox.show(end)) {
        this->graphSolutionDFS(start.value(), end.value(), boostMode.checked());
      }
    }
  });

  exit.events().click([&fm] { fm.close(); });
  fm.div(
      "vert"
      "<<findSolBFS><findSolDFS>><<graphSolBFS><graphSolDFS><boostMode>> "
      "<exit>");
  fm["findSolBFS"] << findSolBFS;
  fm["findSolDFS"] << findSolDFS;
  fm["graphSolBFS"] << graphSolBFS;
  fm["graphSolDFS"] << graphSolDFS;
  fm["boostMode"] << boostMode;
  fm["exit"] << exit;
  fm.collocate();

  fm.show();
  nana::exec();
}
