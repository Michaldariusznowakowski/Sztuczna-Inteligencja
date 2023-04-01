
/**
 * @file main.cc
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief Main file for lab1. This file is responsible for running the program.
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <memory>

#include "gui.h"
#include "logger.h"
#include "stats.h"
int main() {
  std::ios_base::sync_with_stdio(false);
  auto ptrLogger = std::make_shared<Logger>();
  auto ptrStats = std::make_shared<Stats>();
  Gui gui(ptrLogger, ptrStats);
  gui.runLoop();
}