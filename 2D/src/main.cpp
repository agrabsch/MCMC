#include <iostream>
#include <fstream>
#include <sstream>

#include "mcmc.hpp"

using namespace std;

const int N = 1000 ;

const int M = 200*N ;


int main()
{
  // realisation with N points
  MCMC sim(N) ;

  // forget init cdt
  sim.Iterate(M) ;

  // write result
  sim.write_points("pts.dat") ;


  return 0 ;
}




