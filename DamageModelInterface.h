#ifndef JMG_DIAMOND_MODEL_INTERFACE_H
#define JMG_DIAMOND_MODEL_INTERFACE_H

#include <string>

class DamageModelInterface
{
 public:
  virtual double n(double vacancy_concentration) const = 0;
  virtual double kappa(double vacancy_concentration) const = 0;
  virtual double p12(double vacancy_concentration) const = 0;
  virtual std::string description() const = 0;
};

#endif
