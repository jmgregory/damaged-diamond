#ifndef JMG_UNDAMAGED_DIAMOND_MODEL_H
#define JMG_UNDAMAGED_DIAMOND_MODEL_H

#include <complex>
#include "DiamondModelInterface.h"

using std::complex;

class UndamagedDiamondModel : public DiamondModelInterface
{
 public:
  double n(double vacancy_concentration) const
  {
    return 2.4;
  }

  double kappa(double vacancy_concentration) const
  {
    return 0.0;
  }

  double dndeta(double vacancy_concentration) const
  {
    // Equation from O. Matsuda and O. B. Wright, J. Opt. Soc. Am. B, vol. 19, pp. 3028-3041, Dec 2002.
    double p12 = 0.032; // L. S. Hounsome, R. Jones, M. J. Shaw, and P. R. Briddon, physica status solidi (a), vol. 203, no. 12, pp. 3088-3093 (2006)
    complex <double> index(n(vacancy_concentration), kappa(vacancy_concentration));
    return -real(index*index*index)/2.0*p12;
  }

  double dkappadeta(double vacancy_concentration) const
  {
    // Could use imag() of same eqn. as dndeta, but the result will always be zero while kappa is zero
    return 0.0;
  }
};

#endif
