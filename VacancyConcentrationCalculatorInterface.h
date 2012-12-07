#ifndef JMG_VACANCY_CONCENTRATION_CALCULATOR_INTERFACE_H
#define JMG_VACANCY_CONCENTRATION_CALCULATOR_INTERFACE_H

#include <string>

class VacancyConcentrationCalculatorInterface
{
 public:
  virtual double vacancy_concentration(double depth) const = 0;
  virtual std::string description() const = 0;
};

#endif
