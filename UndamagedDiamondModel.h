#ifndef JMG_UNDAMAGED_DIAMOND_MODEL_H
#define JMG_UNDAMAGED_DIAMOND_MODEL_H

#include <complex>
#include <string>
#include "DamageModelInterface.h"

using std::complex;

class UndamagedDiamondModel : public DamageModelInterface
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

  double p12(double vacancy_concentration) const
  {
    // L. S. Hounsome, R. Jones, M. J. Shaw, and P. R. Briddon, physica status solidi (a), vol. 203, no. 12, pp. 3088-3093 (2006)
    return 0.032;
  }

  std::string description() const
  {
    return "No damage dependence";
  }
};

#endif
