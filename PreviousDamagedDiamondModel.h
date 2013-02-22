#ifndef JMG_PREVIOUS_DAMAGED_DIAMOND_MODEL_H
#define JMG_PREVIOUS_DAMAGED_DIAMOND_MODEL_H

#include <complex>
#include <string>
#include "DamageModelInterface.h"

class PreviousDamagedDiamondModel : public DamageModelInterface
{
 private:
  double _A, _B;
  double _c;
  double _d;
  double _n_0, _kappa_0;
  double _p12_0;

 public:
 PreviousDamagedDiamondModel()
   :_A(-6e-3), _B(3.3e19), _c(1.0/1.49e23), _d(4.4e20), _n_0(2.4542), _kappa_0(0.00248801), _p12_0(0.032)
    { }

  double n(double vacancy_concentration) const
  {
    if (vacancy_concentration < _B) return _n_0;
    return _n_0 + _A * log(vacancy_concentration / _B);
  }
  
  double kappa(double vacancy_concentration) const
  {
    return _kappa_0 + _c * vacancy_concentration;
  }
  
  double p12(double vacancy_concentration) const
  {
    if (vacancy_concentration <= 1e21)
      {
	return _p12_0 * (1.0 - vacancy_concentration / _d);
      }
    else
      {
	return p12(1e21);
      }
  }
  
  std::string description() const
    {
      return "Damage model from older CAP Simulation code. n(C_V) = n_0 + A * ln(C_V / B) if C_V >= B, n_0 otherwise. kappa(C_V) = c * C_V. p12(C_V) = p12_0 * (1 - (C_V / d))";
    }

  std::string name() const
    {
      return "previous";
    }
  
  unsigned int ParameterCount() const
  {
    return 7;
  }

  std::vector <Parameter> parameters() const
    {
      std::vector <Parameter> out;
      out.resize(ParameterCount());
      out[0].value = _A;
      out[0].name = "A";
      out[0].units = "";
      out[1].value = _B;
      out[1].name = "B";
      out[1].units = "cm^-3";
      out[2].value = _c;
      out[2].name = "c";
      out[2].units = "cm^3";
      out[3].value = _d;
      out[3].name = "d";
      out[3].units = "cm^3";
      out[4].value = _n_0;
      out[4].name = "n_0";
      out[4].units = "";
      out[5].value = _kappa_0;
      out[5].name = "kappa_0";
      out[5].units = "";
      out[6].value = _p12_0;
      out[6].name = "p12_0";
      out[6].units = "";
      return out;
    }

  void _set_parameters(const std::vector <double> & new_parameters)
  {
    _A = new_parameters[0];
    _B = new_parameters[1];
    _c = new_parameters[2];
    _d = new_parameters[3];
    _n_0 = new_parameters[4];
    _kappa_0 = new_parameters[5];
    _p12_0 = new_parameters[6];
  }

  PreviousDamagedDiamondModel * clone() const
    {
      PreviousDamagedDiamondModel * out = new PreviousDamagedDiamondModel();
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
