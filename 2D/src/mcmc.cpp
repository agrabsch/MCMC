#include "mcmc.hpp"
using namespace std ;

MCMC::MCMC(const int N0) : N(N0)
{
    
  // initialization
  eng.seed(time(NULL));

  z = vector<complex<double> >(N,0) ;

  int_distr = uniform_int_distribution<int>(0,N-1) ;
  unif01 = uniform_real_distribution<double>(0,1) ;

  epsilon = 0.1 ;

  // initialize the positions with unif point in unit disk

  for(int i=0; i<N; i++)
    {
      double theta = 2*PI*unif01(eng) ;
      double r2 = unif01(eng) ;
      
      z[i] = complex<double>(sqrt(r2)*cos(theta), sqrt(r2)*sin(theta)) ; 
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
	  e0 -= 2.*log(abs(z[i]-z[j])) ;
	}

      e0 += N*V(z[i]) ;
    }

  return e0 ;
}

// variation of energy when moving point i to xi
double MCMC::dE(int i, complex<double> zi)
{
  double de = 0 ;
  de += N*(V(zi)-V(z[i])) ;

  for(int j=0; j<i; j++)
    {
      de -= 2.*log(abs((zi-z[j])/(z[i]-z[j]))) ;
    }
  for(int j=i+1; j<N; j++)
    {
      de -= 2.*log(abs((zi-z[j])/(z[i]-z[j]))) ;
    }

  return de ;
}


// Metropolis-Hastings algorithm
void MCMC::MetropolisHastings()
{
  // pick point to move
  int i = int_distr(eng) ;

  // new position
  // real part
  normal_distribution<double> distR(real(z[i]), epsilon) ;
  double xi = distR(eng) ;
  // imag part
  normal_distribution<double> distI(imag(z[i]), epsilon) ;
  double yi = distI(eng) ;

  complex<double>  zi(xi, yi) ;

  // variation of energy for this step
  double de = dE(i,zi) ;

  // acceptance probability
  double pa = min(1.,exp(-de)) ;

  // pick random number in [0,1]
  double u = unif01(eng) ;

  // check if accept change
  if( u < pa )
    {
      z[i] = zi ;
    }  
}


void MCMC::write_points(const string &filename)
{
  ofstream out(filename);

    for(int i=0; i<N; i++)
    {
      out << real(z[i]) << " " << imag(z[i]) << endl ;
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


vector<complex<double> > MCMC::get_points()
{
  return z ;
}


// ************************************************************
// ************************************************************
// ************************************************************
// ************************************************************


double MCMC::V(complex<double> z) const
{
  
  double nu = 1. ;
  return abs(z) < 1 ? -nu/N*log(1-abs(z)*abs(z)) : 1.e10 ;

  // return abs(z)*abs(z) ;
}


