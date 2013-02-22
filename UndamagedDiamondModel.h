#ifndef JMG_UNDAMAGED_DIAMOND_MODEL_H
#define JMG_UNDAMAGED_DIAMOND_MODEL_H

#include <complex>
#include <string>
#include "DamageModelInterface.h"

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

  std::string name() const
    {
      return "undamaged";
    }

  unsigned int ParameterCount() const
  {
    return 0;
  }

  std::vector <Parameter> parameters() const
    {
      std::vector <Parameter> out;
      return out;
    }

  void _set_parameters(const std::vector <double> & new_parameters)
  {  }

  UndamagedDiamondModel * clone() const
  {
    UndamagedDiamondModel * out = new UndamagedDiamondModel();
    std::vector <Parameter> params_all = parameters();
    std::vector <double> params_values;
    for (unsigned int i = 0; i < ParameterCount(); i++)
      {
	params_values.push_back(params_all[i].value);
      }
    out->set_parameters(params_values);
    return out;
  }
};

#endif
