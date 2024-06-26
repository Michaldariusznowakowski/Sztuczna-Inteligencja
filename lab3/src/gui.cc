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
    this->ptr_chessboard_->BFS(i, boostMode);
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
    this->ptr_chessboard_->DFS(i, boostMode);
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
void Gui::graphSolutionH2(const unsigned int &start, const unsigned int &end,
                           const bool &boostMode) {
  std::vector<unsigned long int> times;
  std::vector<int> checkedStates;
  std::vector<int> generatedStates;
  std::vector<unsigned int> sizes;
  for (unsigned int i = start; i <= end; i++) {
    sizes.push_back(i);
    this->ptr_stats_->reset();
    this->ptr_chessboard_->H2(i, boostMode);
    times.push_back(this->ptr_stats_->getDuration());
    int checkedStatesTmp = 0;
    int generatedStatesTmp = 0;
    this->ptr_stats_->getVariable("checkedStates", &checkedStatesTmp);
    this->ptr_stats_->getVariable("generatedStates", &generatedStatesTmp);
    checkedStates.push_back(checkedStatesTmp);
    generatedStates.push_back(generatedStatesTmp);
    this->ptr_logger_->info(
        "Gui::graphSolutionH2",
        "Graphed H2 solution for size: " + std::to_string(i));
  }
  this->ptr_logger_->info(
      "Gui::graphSolutionH2",
      "Plotting stats for H2 size:" + std::to_string(times.size()));
  PlotStats::plotQueensStats("Stats for H2", times, checkedStates,
                             generatedStates, sizes);
}
void Gui::graphSolutionH3(const unsigned int &start, const unsigned int &end,
                           const bool &boostMode) {
  std::vector<unsigned long int> times;
  std::vector<int> checkedStates;
  std::vector<int> generatedStates;
  std::vector<unsigned int> sizes;
  for (unsigned int i = start; i <= end; i++) {
    sizes.push_back(i);
    this->ptr_stats_->reset();
    this->ptr_chessboard_->H3(i, boostMode);
    times.push_back(this->ptr_stats_->getDuration());
    int checkedStatesTmp = 0;
    int generatedStatesTmp = 0;
    this->ptr_stats_->getVariable("checkedStates", &checkedStatesTmp);
    this->ptr_stats_->getVariable("generatedStates", &generatedStatesTmp);
    checkedStates.push_back(checkedStatesTmp);
    generatedStates.push_back(generatedStatesTmp);
    this->ptr_logger_->info(
        "Gui::graphSolutionH3",
        "Graphed H3 solution for size: " + std::to_string(i));
  }
  this->ptr_logger_->info(
      "Gui::graphSolutionH3",
      "Plotting stats for H3 size:" + std::to_string(times.size()));
  PlotStats::plotQueensStats("Stats for H3", times, checkedStates,
                             generatedStates, sizes);
}
Gui::~Gui() { this->ptr_chessboard_ = nullptr; }
void Gui::runLoop() {
  this->ptr_logger_->info("Gui::runLoop", "Starting GUI loop.");
  nana::form fm;
  fm.caption("N-Queens problem");
  nana::checkbox boostMode{fm, nana::rectangle{200, 200, 200, 200}};
  nana::button findSolBFS(fm, "Find solution BFS");
  nana::button findSolH2(fm, "Find solution H2");
  nana::button findSolH3(fm, "Find solution H3");
  nana::button findSolDFS(fm, "Find solution DFS");
  nana::button graphSolBFS(fm, "Graph solutions BFS");
  nana::button graphSolDFS(fm, "Graph solutions DFS");
  nana::button graphSolH2(fm, "Graph solutions H2");
  nana::button graphSolH3(fm, "Graph solutions H3");
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
  findSolH2.events().click([&] {
    this->ptr_logger_->info("Gui::runLoop", "Clicked find solution H2.");
    this->ptr_stats_->reset();
    nana::inputbox ibox(fm, "Find solution H2");
    nana::inputbox::integer size("Size of chessboard", 4, 4, 20, 1);
    if (ibox.show(size)) {
      this->ptr_chessboard_->H2(size.value(), boostMode.checked());
      std::string result = this->ptr_chessboard_->dumpChessboard();
      this->showResult(result, fm);
    }
  });
  findSolH3.events().click([&] {
    this->ptr_logger_->info("Gui::runLoop", "Clicked find solution H3.");
    this->ptr_stats_->reset();
    nana::inputbox ibox(fm, "Find solution H3");
    nana::inputbox::integer size("Size of chessboard", 4, 4, 20, 1);
    if (ibox.show(size)) {
      this->ptr_chessboard_->H3(size.value(), boostMode.checked());
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
      this->ptr_chessboard_->DFS(size.value(), boostMode.checked());
      std::string result =
          this->ptr_chessboard_->dumpChessboard();
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
  graphSolH2.events().click([&] {
    this->ptr_logger_->info("Gui::runLoop", "Clicked graph solutions H2.");
    nana::inputbox ibox(fm, "Graph solutions H2");
    nana::inputbox::integer start("Start size", 4, 4, 20, 1);
    if (ibox.show(start)) {
      nana::inputbox::integer end("End size", start.value(), start.value(), 20,
                                  1);
      if (ibox.show(end)) {
        this->graphSolutionH2(start.value(), end.value(), boostMode.checked());
      }
    }
  });
  graphSolH3.events().click([&] {
    this->ptr_logger_->info("Gui::runLoop", "Clicked graph solutions H3.");
    nana::inputbox ibox(fm, "Graph solutions H3");
    nana::inputbox::integer start("Start size", 4, 4, 20, 1);
    if (ibox.show(start)) {
      nana::inputbox::integer end("End size", start.value(), start.value(), 20,
                                  1);
      if (ibox.show(end)) {
        this->graphSolutionH3(start.value(), end.value(), boostMode.checked());
      }
    }
  });

  exit.events().click([&fm] { fm.close(); });
  fm.div(
      "vert"
      "<<findSolBFS><findSolDFS><findSolH2><findSolH3>><<graphSolBFS><graphSolDFS><graphSolH2><graphSolH3>>"
      "<boostMode> "
      "<exit>");
  fm["findSolBFS"] << findSolBFS;
  fm["findSolDFS"] << findSolDFS;
  fm["findSolH2"] << findSolH2;
  fm["findSolH3"] << findSolH3;
  fm["graphSolBFS"] << graphSolBFS;
  fm["graphSolDFS"] << graphSolDFS;
  fm["graphSolH2"] << graphSolH2;
  fm["graphSolH3"] << graphSolH3;
  fm["boostMode"] << boostMode;
  fm["exit"] << exit;
  fm.collocate();

  fm.show();
  nana::exec();
}
