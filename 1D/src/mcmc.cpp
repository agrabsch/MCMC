#include "mcmc.hpp"
using namespace std ;

MCMC::MCMC(const int N0) : N(N0)
{
    
  // initialization
  eng.seed(time(NULL));

  x = vector<double>(N,0) ;

  int_distr = uniform_int_distribution<int>(0,N-1) ;
  unif01 = uniform_real_distribution<double>(0,1) ;

  epsilon = 0.1 ;

  // initialize the positions
  // from Gaussian iid
  normal_distribution<double> init_distr(0,1.) ;
  for(int i=0; i<N; i++)
    {
      x[i] = -1 + 2.*i/N ; //init_distr(eng) ; 
    }
	
}

// compute total energy
double MCMC::E() const
{
  double e0 = 0 ;
  
  for(int i=0; i<N; i++)
    {
      for(int j=0; j<i; j++)
	{
	  e0 -= 2.*log(fabs(x[i]-x[j])) ;
	}

      e0 += N*V(x[i]) ;
    }

  return e0 ;
}

// variation of energy when moving point i to xi
double MCMC::dE(int i, double xi)
{
  double de = 0 ;
  de += N*(V(xi)-V(x[i])) ;

  for(int j=0; j<i; j++)
    {
      de -= 2.*log(fabs((xi-x[j])/(x[i]-x[j]))) ;
    }
  for(int j=i+1; j<N; j++)
    {
      de -= 2.*log(fabs((xi-x[j])/(x[i]-x[j]))) ;
    }

  return de ;
}


// Metropolis-Hastings algorithm
void MCMC::MetropolisHastings()
{
  // pick point to move
  int i = int_distr(eng) ;

  // new position
  normal_distribution<double> dist(x[i], epsilon) ;
  double xi = dist(eng) ;

  // variation of energy for this step
  double de = dE(i,xi) ;

  // acceptance probability
  double pa = min(1.,exp(-de)) ;

  // pick random number in [0,1]
  double u = unif01(eng) ;

  // check if accept change
  if( u < pa )
  //if( de < 0 )
    {
      x[i] = xi ;
    }  
}


void MCMC::write_points(const string &filename)
{
  ofstream out(filename);

    for(int i=0; i<N; i++)
    {
      out << x[i] << endl ;
    }

  out.close() ;
}

void MCMC::Iterate(int M)
{
  for(int i=0; i<M; i++)
    {
      MetropolisHastings() ;
    }
}


vector<double> MCMC::get_points()
{
  return x ;
}


// ************************************************************
// ************************************************************
// ************************************************************
// ************************************************************


double MCMC::V(double x) const
{
  return x*x ;
}


