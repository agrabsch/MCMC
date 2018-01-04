#include <iostream>
#include <fstream>
#include <sstream>

#include "mcmc.hpp"

using namespace std;

const int N = 100 ;

const int M = 20*N ;

int main()
{

  // generate N points
  MCMC sim(N) ;

  // forget init cdt: run M iterations
  sim.Iterate(M) ;

  // output files
  ostringstream filename;
  filename << "pts_N=" << N  << ".dat" ;
  ofstream out(filename.str()) ;

  vector<double> x = sim.get_points() ;

  for(int j=0; j<N; j++)
    {
      out << x[j] << endl ;
    }

  out.close() ;

  return 0 ;
}




