/*
*
*
*		MCMC pour generer points selon Gibbs Coulomb
*
*			
*
*
*
*
*/

#ifndef MCMC_H_
#define MCMC_H_

#include<vector>
#include<fstream>
#include<cmath>
#include<string>

// #include <iostream>

#include <ctime>
#include <random>


class MCMC{

  private:
  std::vector<double> x ;
  // std::vector<double> y ;

  // number of points
  int N ;

  // potential
  double V(double x) const ;

  // energy difference when moving one point
  // pt i, new pt x_i
  double dE(int i, double xi) ;



  // generateur de nb aleatoires
  std::mt19937 eng;

  std::uniform_int_distribution<int> int_distr ;
  std::uniform_real_distribution<double> unif01 ;

  // small step to move
  double epsilon ;

 public:
  // constructor
  MCMC(const int N) ;

  // one iteration
  void MetropolisHastings() ;

  // run M iterations
  void Iterate(int M) ;

  // write data points
  void write_points(const std::string &filename) ;

  // get points
  std::vector<double> get_points() ;

  // compute energy
  double E() const ;
    
    
} ;


#endif
