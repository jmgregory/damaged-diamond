#ifndef JMG_UNDAMAGED_DIAMOND_MODEL_H
#define JMG_UNDAMAGED_DIAMOND_MODEL_H

#include <complex>
#include <string>
#include <sstream>
#include "DamageModelInterface.h"

using std::complex;

class UndamagedDiamondModel : public DamageModelInterface
{
 private:
  double _n, _kappa, _p12;
 
 public:
  
  UndamagedDiamondModel();
  UndamagedDiamondModel(double n, double kappa, double p12);
  
  double n(double vacancy_concentration) const
  {
    return _n;
  }
  
  double kappa(double vacancy_concentration) const
  {
    return _kappa;
  }

  double p12(double vacancy_concentration) const
  {
    return _p12;
  }

  std::string description() const
  {
    std::stringstream ss;
    ss << "No damage dependence, n = " << _n << ", kappa = " << _kappa << ", p12 = " << _p12;
    return ss.str();
  }
};

#endif
