#include "LagomarsinoDamageModel.h"
#include "UndamagedDiamondModel.h"

LagomarsinoDamageModel::LagomarsinoDamageModel()
  :_n_0(2.41),
   _kappa_0(0.0),
   _p12_0(0.032),
   _A(4.34e-23),
   _B(2.86e-23)
{}

double LagomarsinoDamageModel::n(double vacancy_concentration) const
{
  UndamagedDiamondModel model;
  return _n_0 + _A * vacancy_concentration;
}

double LagomarsinoDamageModel::kappa(double vacancy_concentration) const
{
  return _kappa_0 + _B * vacancy_concentration;
}

double LagomarsinoDamageModel::p12(double vacancy_concentration) const
{
  return _p12_0;
}

std::string LagomarsinoDamageModel::description() const
{
  return "Damage model for complex index from Lagomarsino et al Opt. Express 20, 19382 (2012), n = (n_0 + kappa_0 i) + (A + B i) * C_V, p12 = p12_0.";
}

std::string LagomarsinoDamageModel::name() const
{
  return "lagomarsino";
}

unsigned int LagomarsinoDamageModel::ParameterCount() const
{
  return 5;
}

std::vector <Parameter> LagomarsinoDamageModel::parameters() const
{
  std::vector <Parameter> out;
  out.resize(ParameterCount());
  out[0].name = "n_0";
  out[0].value = _n_0;
  out[0].units = "";
  out[1].name = "kappa_0";
  out[1].value = _kappa_0;
  out[1].units = "";
  out[2].name = "p12_0";
  out[2].value = _p12_0;
  out[2].units = "";
  out[3].name = "A";
  out[3].value = _A;
  out[3].units = "cm^3";
  out[4].name = "B";
  out[4].value = _B;
  out[4].units = "cm^3";
  return out;
}

void LagomarsinoDamageModel::_set_parameters(const std::vector <double> & new_parameters)
{
  _n_0 = new_parameters[0];
  _kappa_0 = new_parameters[1];
  _p12_0 = new_parameters[2];
  _A = new_parameters[3];
  _B = new_parameters[4];
}
