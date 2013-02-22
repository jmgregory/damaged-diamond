#include <iostream>
#include <sstream>
#include <math.h>
#include "IndependentExponentialModel.h"

IndependentExponentialModel::IndependentExponentialModel()
  :_n_0(2.4542), _n_inf(2.4), _kappa_0(0.004), _kappa_inf(1.4), _p12_0(0.032), _p12_inf(-0.04), _a(1.5e21), _b(1.5e21), _c(1.5e21)
{}

double IndependentExponentialModel::n(double vacancy_concentration) const
{
  return _n_0 + (_n_inf - _n_0) * (1.0 - exp(-(vacancy_concentration) / _a));
}

double IndependentExponentialModel::kappa(double vacancy_concentration) const
{
  return _kappa_0 + (_kappa_inf - _kappa_0) * (1.0 - exp(-(vacancy_concentration) / _b));
}

double IndependentExponentialModel::p12(double vacancy_concentration) const
{
  return _p12_0 + (_p12_inf - _p12_0) * (1.0 - exp(-(vacancy_concentration) / _c));
}

std::string IndependentExponentialModel::description() const
{
  return "Exponential function model for complex index with independent slopes for n, kappa and p12.  N(C_V) = (n_0 + kappa_0 i) + ((n_inf + kappa_inf i) - (n_0 + kappa_0 i)) * (1 - exp(-C_V / (a + bi)), p12(C_V) = p12_0 + (p12_inf - p12_0) * (1 - exp(-C_V / c))";
}

std::vector <Parameter> IndependentExponentialModel::parameters() const
{
  std::vector <Parameter> out;
  out.resize(ParameterCount());
  out[0].name = "n_0";
  out[0].value = _n_0;
  out[0].units = "";
  out[1].name = "n_inf";
  out[1].value = _n_inf;
  out[1].units = "";
  out[2].name = "kappa_0";
  out[2].value = _kappa_0;
  out[2].units = "";
  out[3].name = "kappa_inf";
  out[3].value = _kappa_inf;
  out[3].units = "";
  out[4].name = "p12_0";
  out[4].value = _p12_0;
  out[4].units = "";
  out[5].name = "p12_inf";
  out[5].value = _p12_inf;
  out[5].units = "";
  out[6].name = "a";
  out[6].value = _a;
  out[6].units = "cm^-3";
  out[7].name = "b";
  out[7].value = _b;
  out[7].units = "cm^-3";
  out[8].name = "c";
  out[8].value = _c;
  out[8].units = "cm^-3";
  return out;
}

void IndependentExponentialModel::_set_parameters(const std::vector <double> & new_parameters)
{
  _n_0 = new_parameters[0];
  _n_inf = new_parameters[1];
  _kappa_0 = new_parameters[2];
  _kappa_inf = new_parameters[3];
  _p12_0 = new_parameters[4];
  _p12_inf = new_parameters[5];
  _a = new_parameters[6];
  _b = new_parameters[7];
  _c = new_parameters[8];
}

unsigned int IndependentExponentialModel::ParameterCount() const
{
  return 9;
}

IndependentExponentialModel * IndependentExponentialModel::clone() const
{
  IndependentExponentialModel * out = new IndependentExponentialModel();
  std::vector <Parameter> params_all = parameters();
  std::vector <double> params_values;
  for (unsigned int i = 0; i < ParameterCount(); i++)
    {
      params_values.push_back(params_all[i].value);
    }
  out->set_parameters(params_values);
  return out;
}

std::string IndependentExponentialModel::name() const
{
  return "independent-exponential";
}
