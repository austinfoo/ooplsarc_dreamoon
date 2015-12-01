
// ----------------------------
// projects/twobuttons/Twobuttons.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <list>
#include <limits>
#include <iomanip>

#include "Dreamoon.h"

// ------------
// dreamoon_eval
// ------------

double dreamoon_eval (const std::vector<char>& drazil, const std::vector<char>& dreamoon)
{
  // Compute drazil's final position
  int drazil_final_pos = 0;
  for (char c : drazil) {
    if (c == '+') {
      ++drazil_final_pos;
    } else {
      --drazil_final_pos;
    }
  }

  // Compute dreamoon's partial position ignoring question marks
  int dreamoon_partial_pos = 0;
  int num_question_marks = 0;
  for (char c : dreamoon) {
    if (c == '+') {
      ++dreamoon_partial_pos;
    } else if (c == '-') {
      --dreamoon_partial_pos;
    } else {
      ++num_question_marks;
    }
  }

  // The number of paths
  int num_paths = 1 << num_question_marks;

  // The number of paths that get to the same final pos as drazil
  int num_success = 0;

  // Enumerate the paths
  for (int path = 0; path < num_paths; ++path) {

    // Count the number of plusses in this path
    int val = path;
    int num_plus = 0;
    for (int bit = 0; bit < num_question_marks; ++bit) {
      if (val & 1) ++num_plus;
      val = val >> 1;
    }

    // Determine dreammon's final position for this path
    int num_minus = num_question_marks - num_plus;
    int dreamoon_final_pos = dreamoon_partial_pos + num_plus - num_minus;

    // Success if dreamoon's final pos is the same as drazil's final pos
    if (dreamoon_final_pos == drazil_final_pos) {
      ++num_success;
    }
  }

  // Compute the probability of success
  double prob = static_cast<double>(num_success) / num_paths;

  return prob;
}

// -------------
// dreamoon_print
// -------------

void dreamoon_print (std::ostream& w, double answer)
{
  w << std::fixed << std::setprecision(12) << answer << std::endl;
}

// -------------
// dreamoon_solve
// -------------

void dreamoon_solve (std::istream& r, std::ostream& w) 
{
  std::string s;

  // Get the drazil string
  std::string drazil_str;
  if (std::getline(r, s)) {
    std::istringstream sin(s);
    sin >> drazil_str;
  }

  // Get the dreamoon string
  std::string dreamoon_str;
  if (std::getline(r, s)) {
    std::istringstream sin(s);
    sin >> dreamoon_str;
  }

  // Parse the drazil string into a vector
  std::vector<char> drazil;
  for (char c : drazil_str) {
    drazil.push_back(c);
  }

  // Parse the dreamoon string into a vector
  std::vector<char> dreamoon;
  for (char c : dreamoon_str) {
    dreamoon.push_back(c);
  }

  // Determine the answer
  double answer = dreamoon_eval(drazil, dreamoon);

  // Print the result
  dreamoon_print(w, answer);
}
