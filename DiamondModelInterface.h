#ifndef JMG_DIAMOND_MODEL_INTERFACE_H
#define JMG_DIAMOND_MODEL_INTERFACE_H

class DiamondModelInterface
{
 public:
  virtual double n(double vacancy_concentration) const = 0;
  virtual double kappa(double vacancy_concentration) const = 0;
  virtual double dndeta(double vacancy_concentration) const = 0;
  virtual double dkappadeta(double vacancy_concentration) const = 0;
};

#endif
