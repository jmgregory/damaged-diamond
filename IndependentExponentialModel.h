#ifndef JMG_INDEPENDENT_EXPONENTIAL_MODEL_H
#define JMG_INDEPENDENT_EXPONENTIAL_MODEL_H

#include <string>
#include <vector>
#include "DamageModelInterface.h"

class IndependentExponentialModel : public DamageModelInterface
{
 private:
  double _n_0;
  double _n_inf;
  double _kappa_0;   // Undamaged kappa
  double _kappa_inf; // Saturation kappa
  double _p12_0;
  double _p12_inf;
  double _a;
  double _b;         // Vacancy concentration at 63% saturation (1 - 1/e)
  double _c;

 public:
  IndependentExponentialModel();

  std::string name() const;
  std::string description() const;
  unsigned int ParameterCount() const;

  double n(double vacancy_concentration) const;
  double kappa(double vacancy_concentration) const;
  double p12(double vacancy_concentration) const;
  std::vector <Parameter> parameters() const;
  void _set_parameters(const std::vector <double> & new_parameters);
  IndependentExponentialModel * clone() const;
};

#endif
