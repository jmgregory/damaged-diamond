#ifndef JMG_LAGOMARSINO_DAMAGE_MODEL_H
#define JMG_LAGOMARSINO_DAMAGE_MODEL_H

#include <string>
#include "DamageModelInterface.h"

class LagomarsinoDamageModel : public DamageModelInterface
{
 private:
  double _n_0, _kappa_0, _p12_0;
  double _A, _B;

 public:
  LagomarsinoDamageModel();

  double n(double vacancy_concentration) const;
  double kappa(double vacancy_concentration) const;
  double p12(double vacancy_concentration) const;
  std::string description() const;
  std::string name() const;
  unsigned int ParameterCount() const;
  std::vector <Parameter> parameters() const;
  void _set_parameters(const std::vector <double> & new_parameters);
};

#endif
