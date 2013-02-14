#ifndef JMG_LAGOMARSINO_DAMAGE_MODEL_H
#define JMG_LAGOMARSINO_DAMAGE_MODEL_H

#include <string>
#include "DamageModelInterface.h"

class LagomarsinoDamageModel : public DamageModelInterface
{
 private:
  double _n0, _kappa0, _p12;

 public:
  LagomarsinoDamageModel();
  LagomarsinoDamageModel(double n0, double kappa0, double p12);

  double n(double vacancy_concentration) const;
  double kappa(double vacancy_concentration) const;
  double p12(double vacancy_concentration) const;
  std::string description() const;
};

#endif
