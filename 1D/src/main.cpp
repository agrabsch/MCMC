#include <iostream>
#include <fstream>
#include <sstream>

#include <complex>

#include "mcmc.hpp"

using namespace std;

const int N = 100 ;

const int M = 10*N ;

const int Nsamples = 10000 ;


int main()
{

  MCMC sim(N) ;

  // forget init cdt
  sim.Iterate(2*M) ;

  // values of interest
  // largest eigenvalue
  double LargEig(0) ;

  // sum squares
  double sx2(0) ;

  // output files
  ostringstream filename;
  filename << "Sum_x2_N=" << N  << ".dat" ;
  ofstream outX2(filename.str()) ;

  ostringstream filename2;
  filename2 << "Largest_N=" << N  << ".dat" ;
  ofstream outLarg(filename2.str()) ;
  


  // get samples
  for(int i=0; i<Nsamples; i++)
    {
      sim.Iterate(2*M) ;

      vector<double> x = sim.get_points() ;

      // sum x2 and largest
      sx2 = 0 ;
      LargEig = 0 ;
      for(int j=0; j<N; j++)
	{
	  if(x[j] > LargEig) LargEig = x[j] ;
	  
	  sx2 += x[j]*x[j] ;
	}
      outX2 << sx2 << endl ;
      outLarg << LargEig << endl ;
    }

  outX2.close() ;
  outLarg.close() ;

  return 0 ;
}




