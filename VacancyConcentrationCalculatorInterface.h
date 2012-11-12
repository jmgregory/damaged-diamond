#ifndef JMG_VACANCY_CONCENTRATION_CALCULATOR_INTERFACE_H
#define JMG_VACANCY_CONCENTRATION_CALCULATOR_INTERFACE_H

#include <string>

class VacancyConcentrationCalculatorInterface
{
 public:
  virtual double vacancy_concentration(double depth) = 0;
  virtual std::string description() = 0;
};

#endif
