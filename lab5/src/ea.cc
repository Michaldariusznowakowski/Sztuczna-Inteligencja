/**
 * @file ea.cc
 * @author Michał Nowakowski (michaldariusznowakowski@protonmail.com)
 * @brief Lab 5 - Evolutionary algorithm
 * @version 0.1
 * @date 2023-05-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "plotstats.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
/**
 * @brief Size of chessboard and number of queens.  n - rozmiar szachownicy i liczba hetmanów
 * 
 */
const int N = 8;
/**
 * @brief Number of individuals in population. pop - liczba osobników w populacji: np. 10 lub 100
 * 
 */
const int POP = 100;
/**
 * @brief Maximum number of generations. genmax - maksymalna liczba generacji np. 1000 lub 10000
 * 
 */
const int GENMAX = 10000;
/**
 * @brief Crossover probability. pc - dyskryminator krzyżowania np. 0.7 lub 0.9
 * 
 */
const double PC = 0.9;
/**
 * @brief Mutation probability. pm - dyskryminator mutacji np. 0.2 lub 0.5
 * 
 */
const double PM = 0.5;

/**
 * @brief FFMAX - ffmax jest wartością oczekiwaną funkcji przystosowania/użyteczności dla rozwiązania.
 * Dla problemu n-hetmanów jest to najmniejsza liczba ataków, tj. 0
 * 
 */
const size_t FFMAX = 0;
/**
 * @brief generatePopulation to początkowa populacja, która jest tablicą o wielkości pop z n-hetmanami, których
 * pszycje są losowe - (losowanie wykonać poprzez losowanie permutacji z n).
 * 
 * @return std::vector<std::vector<size_t>> 
 */

std::vector<std::vector<size_t>> generatePopulation() {
    std::vector<std::vector<size_t>> P;
    for (size_t i = 0; i < POP; i++) {
        std::vector<size_t> Pn;
        for (size_t j = 0; j < N; j++) {
            Pn.push_back(j);
        }
        std::random_shuffle(Pn.begin(), Pn.end());
        P.push_back(Pn);
    }
    return P;
}
/**
 * @brief random() - zwraca wartości rzeczywiste od 0 do 1. 
 * 
 * @return float 
 */
float random() {
  return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}

/**
 * @brief evaluate(P) oblicza funkcję przystosowania dla problemu n-hemtanów
 * która zwraca liczbę ataków. Wykonaj dla każdego osobnika w populacji, by dowiedzieć się jak skutecznym jest rozwiązaniem.
 * @param P 
 * @return size_t 
 */
size_t evaluate(const std::vector<size_t> &vec) {
  size_t attack = 0;
  for (size_t i = 0; i < vec.size(); i++) {
    for (size_t j = 0; j < vec.size(); j++) {
      if (i != j) {
        if (vec[i] == vec[j]) {
        attack++;
        }
      }
    }
  }
  // check if diagonal using absolute value
  for (size_t i = 0; i < vec.size(); i++) {
    for (size_t j = 0; j < vec.size(); j++) {
      if (i != j) {
        auto diff = long(vec[i] - vec[j]);
        if (abs(diff) == abs(long(i - j))) {
          attack++;
        }
      }
    }
  }
  return attack;
}

/**
 * @brief  crossover(Pn) zmienia osobniki wymieniając informacje zawarte w dwóch losowo wybranych osobnikach.
 * funkcja crossover(Pn) zmienia osobniki wymieniając informacje zawarte w dwóch losowo wybranych osobnikach.
 * while i < pop − 2 do
 * if random() ≤ pc then
 * cross(P(i), P(i+1))
 * i ← i + 2
 * end if
 * end while
 * @param Pn 
 */
void crossover(std::vector<std::vector<size_t>> &Pn) {
    size_t pnPOP = Pn.size();
    for (size_t i = 0; i < pnPOP-2; i++) {
        if (random() <= PC) {
            size_t i1 = rand() % N;
            size_t i2 = rand() % N;
            std::swap(Pn[i][i1], Pn[i][i2]);
        }
    }
}

/**
 * @brief  mutation(Pn) zmienia losowo osobniki wg schematu.
 * while i < pop do
 * if random() ≤ pm then
 * mutate(P(i))
 * i ← i + 1
 * end if
 * end while
 * @param Pn 
 */
void mutation(std::vector<std::vector<size_t>> &Pn) {
    size_t pnPOP = Pn.size();
    for (size_t i = 0; i < pnPOP; i++) {
        if (random() <= PM) {
            size_t i1 = rand() % N;
            size_t i2 = rand() % N;
            std::swap(Pn[i][i1], Pn[i][i2]);
        }
    }
}

/**
 * @brief selection(P) selekcja turniejowa:
 * selection(P) selekcja turniejowa:
 * while i < pop do
 * i1 ← random(pop)
 * i2 ← random(pop)
 * if i1 6= i2 then
 * if evaluate(P(i1)) ≤ evaluate(P(i2)) then
 * Pn(i) ← P(i1)
 * else
 * Pn(i) ← P(i2)
 * end if
 * i ← i + 1
 * end if
 * end while
 * @param P 
 * @return std::vector<std::vector<size_t>> 
 */
std::vector<std::vector<size_t>> selection(std::vector<std::vector<size_t>> &P) {
    std::vector<std::vector<size_t>> Pn;
    size_t pPOP = P.size();
    for (size_t i = 0; i < pPOP; i++) {
        size_t i1 = rand() % pPOP;
        size_t i2 = rand() % pPOP;
        if (i1 != i2) {
            if (evaluate(P[i1]) <= evaluate(P[i2])) {
                Pn.push_back(P[i1]);
            } else {
                Pn.push_back(P[i2]);
            }
        }
    }
    return Pn;
}

/**
 * @brief minEvaluate(P) zwraca osobnika o najmniejszej wartości funkcji przystosowania.
 * 
 * @param P 
 * @return std::vector<size_t> 
 */
std::vector<size_t> minEvaluate(std::vector<std::vector<size_t>> &P) {
    size_t min = evaluate(P[0]);
    size_t min_index = 0;
    size_t pPOP = P.size();
    for (size_t i = 1; i < pPOP; i++) {
        if (evaluate(P[i]) < min) {
            min = evaluate(P[i]);
            min_index = i;
        }
    }
    return P[min_index];
}

// evolutionary algorithm
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

/**
 * @brief EvolutionaryAlgorithm - algorytm ewolucyjny
 * @param Pbest 
 * @param evaluatePbest
 * @return pair
 */
std::pair<std::vector<size_t>,std::vector<double>> evolutionaryAlgorithm(std::vector<size_t> &Pbest, size_t &evaluatePbest) {
    std::vector<std::vector<size_t>> P = generatePopulation();
    size_t gen = 0;
    Pbest = minEvaluate(P);
    evaluatePbest = evaluate(Pbest);
    std::vector<size_t> listOfPbest;
    std::vector<double> means;
    while (gen < GENMAX && evaluatePbest > FFMAX) {
        std::vector<std::vector<size_t>> Pn = selection(P);
        crossover(Pn);
        mutation(Pn);
        Pbest = minEvaluate(Pn);
        evaluatePbest = evaluate(Pbest);
        P = Pn;
        gen++;
        listOfPbest.push_back(evaluatePbest);
        double mean = 0;
        for (size_t i = 0; i < Pn.size(); i++) {
            mean += evaluate(Pn[i]);
        }
        mean /= Pn.size();
        means.push_back(mean);
    }
    return std::make_pair(Pbest,means);
}


std::string dumpChessboard(std::vector<size_t> &cheesboard_pos_) {
  if (cheesboard_pos_.size() == 0) {
    return "";
  }
  std::string output = "";
  size_t size = cheesboard_pos_.size();
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      if (j == cheesboard_pos_[i]) {
        output += " q";
      } else {
        output += " .";
      }
    }
    output += "\n";
  }
  return output;
}

int main() {
    std::cout << "Start" << std::endl;
    srand(time(NULL));
    std::vector<size_t> Pbest;
    size_t evaluatePbest;
    auto pair = evolutionaryAlgorithm(Pbest, evaluatePbest);
    std::cout << "Pbest: ";
    size_t PbestN = Pbest.size();
    for (size_t i = 0; i < PbestN; i++) {
        std::cout << Pbest[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "evaluate(Pbest): " << evaluatePbest << std::endl;
    size_t canAttack = evaluate(Pbest);
    if (canAttack == 0) {
        std::cout << "canAttack: false" << std::endl;
    } else {
        std::cout << "canAttack: true" << std::endl;
    }
    std::cout << dumpChessboard(Pbest) << std::endl;
    PlotStats::plotQueensStats("Algorytm Ewolucyjny", "najlepsze osobniki w generacjach", "średnia wartości funkcji przystosowania z danej populacji", pair.first, pair.second);
    return 0;
}




