
#ifndef Dreamoon_h
#define Dreamoon_h

// --------
// includes
// --------

#include <iostream>
#include <string>
#include <vector>
#include <cinttypes>

// ------------
// dreamoon_eval
// ------------

double dreamoon_eval (std::vector<char> drazil, std::vector<char> dreamoon);

// -------------
// dreamoon_print
// -------------

void dreamoon_print (std::ostream& w, double answer);

// -------------
// dreamoon_solve
// -------------

void dreamoon_solve (std::istream& r, std::ostream& w);

#endif
