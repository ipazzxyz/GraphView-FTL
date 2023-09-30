#include "utils.h"

bool tool::isZero(double x, double error_k = 1) {
  return fabs(x) <= error_k * kErrorRate;
}

double tool::fabs(double x) { return x < 0 ? x * -1 : x; }

double tool::pow2(double x) { return x * x; }
