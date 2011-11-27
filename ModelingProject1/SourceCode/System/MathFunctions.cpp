
#include "MathFunctions.h"

#include <math.h>

int nextPowerOfTwo(int value)
{
  double logbase2 = log( double(value) ) / log( double(2) );
  return round( pow( 2, ceil(logbase2) ) );
}

int round(double value)
{
  return (int)(value + 0.5);
}
