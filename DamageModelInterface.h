#ifndef JMG_DIAMOND_MODEL_INTERFACE_H
#define JMG_DIAMOND_MODEL_INTERFACE_H

#include <string>
#include <vector>

struct Parameter
{
  std::string name;
  std::string units;
  double value;
};

class DamageModelInterface
{
 public:
  virtual std::string name() const = 0;
  virtual std::string description() const = 0;
  virtual std::vector <Parameter> parameters() const = 0;

  virtual double n(double vacancy_concentration) const = 0;
  virtual double kappa(double vacancy_concentration) const = 0;
  virtual double p12(double vacancy_concentration) const = 0;
  virtual void _set_parameters(const std::vector <double> & new_parameters) = 0;
  virtual unsigned int ParameterCount() const = 0;
  //  virtual DamageModelInterface * clone() const = 0;

  void set_parameters(const std::vector <double> & new_parameters);
  void print_parameters(std::ostream & out = std::cout, std::string tag = "") const;
};

#endif
