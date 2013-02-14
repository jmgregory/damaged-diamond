#ifndef JMG_OLIVERO_DAMAGE_MODEL_H
#define JMG_OLIVERO_DAMAGE_MODEL_H

#include <string>
#include "DamageModelInterface.h"

class OliveroDamageModel : public DamageModelInterface
{
  double n(double vacancy_concentration) const;
  double kappa(double vacancy_concentration) const;
  double p12(double vacancy_concentration) const;
  std::string description() const;
};

#endif
