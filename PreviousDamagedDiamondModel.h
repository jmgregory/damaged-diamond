#ifndef JMG_PREVIOUS_DAMAGED_DIAMOND_MODEL_H
#define JMG_PREVIOUS_DAMAGED_DIAMOND_MODEL_H

#include <complex>
#include <string>
#include "DamageModelInterface.h"

using std::complex;

class PreviousDamagedDiamondModel : public DamageModelInterface
{
 public:
  double n(double vacancy_concentration) const
  {
    double A = -6e-3;
    double B = 3.3e19;
    if (vacancy_concentration < B) return 2.4;
    return 2.4 + A * log(vacancy_concentration / B);
  }
  
  double kappa(double vacancy_concentration) const
  {
    return vacancy_concentration / 1.49e23;
  }

  double p12(double vacancy_concentration) const
  {
    if (vacancy_concentration <= 1e21)
      {
	return 2.0 / (2.4 * 2.4 * 2.4) * (1.0 - vacancy_concentration / 4.4e20);
      }
    return p12(1e21);
  }

  std::string description() const
  {
    return "Damage model from older CAP Simulation code";
  }
};

#endif
