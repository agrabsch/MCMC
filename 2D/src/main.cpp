#include <iostream>
#include <fstream>
#include <sstream>

#include "mcmc.hpp"

using namespace std;

const int N = 1000 ;

const int M = 10*N ;

const int Nsamples = 10000 ;


int main()
{

  MCMC sim(N) ;

  sim.write_points("Init.dat") ;

  // forget init cdt
  sim.Iterate(20*M) ;

  sim.write_points("Dist.dat") ;

  /*
  // largest eigenvalue
  double LargEig(0) ;

 
  ostringstream filename2;
  filename2 << "Largest_N=" << N  << ".dat" ;
  ofstream outLarg(filename2.str()) ;
  


  // get samples
  for(int i=0; i<Nsamples; i++)
    {
      sim.Iterate(2*M) ;

      vector<complex<double> > z = sim.get_points() ;

      // largest
      LargEig = 0 ;
      for(int j=0; j<N; j++)
      	{
      	  if(abs(z[j]) > LargEig) LargEig = abs(z[j]) ;
      	}
      outLarg << LargEig << endl ;
    }

  outLarg.close() ;

  */

  return 0 ;
}




