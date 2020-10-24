#include <iostream>
#include <chrono>
#include <utility>
#include <vector>
#include <unordered_map>
#include <random>
#include <experimental/random>
#include <string>
#include <algorithm>    // std::swap
#include <fstream>

#include <cmath> // ceil, floor

//#include "randomness.h"
//#include "data_writer.h"
#include "math_operations.h"

using std::cout;
using std::cin;
using std::unordered_map;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;


int main(){
  int absc1 = 1, absc2 = 2;
  double conc1 = 10, conc2 = 14, absc = 1.9999;
  cout <<
  linear_interp((double) absc1, (double) absc2, conc1, conc2, absc)
  << "\n";
  return 0;
}
