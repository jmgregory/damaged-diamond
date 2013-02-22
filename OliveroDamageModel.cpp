#include "OliveroDamageModel.h"
#include "UndamagedDiamondModel.h"

OliveroDamageModel::OliveroDamageModel()
  : _n_0(2.47), _c(4.3e-23)
{ }

double OliveroDamageModel::n(double vacancy_concentration) const
{
  return _n_0 + _c * vacancy_concentration;
}

double OliveroDamageModel::kappa(double vacancy_concentration) const
{
  UndamagedDiamondModel model;
  return model.kappa(vacancy_concentration);
}

double OliveroDamageModel::p12(double vacancy_concentration) const
{
  UndamagedDiamondModel model;
  return model.p12(vacancy_concentration);
}

std::string OliveroDamageModel::description() const
{
  return "Damage model for real index from Olivero et al Diamond and Related Materials 19, 428 (2010). n(C_V) = n_0 + c * C_V.  Imaginary index and p12 are same as undamaged diamond.";
}

std::string OliveroDamageModel::name() const
{
  return "olivero";
}

unsigned int OliveroDamageModel::ParameterCount() const
{
  return 2;
}

std::vector <Parameter> OliveroDamageModel::parameters() const
{
  std::vector <Parameter> out;
  out.resize(2);
  out[0].name = "n_0";
  out[0].value = _n_0;
  out[0].units = "";
  out[1].name = "c";
  out[1].value = _c;
  out[1].units = "cm^3";
  return out;
}

void OliveroDamageModel::_set_parameters(const std::vector <double> & new_parameters)
{
  _n_0 = new_parameters[0];
  _c = new_parameters[1];
}

OliveroDamageModel * OliveroDamageModel::clone() const
{
  OliveroDamageModel * out = new OliveroDamageModel();
  std::vector <Parameter> params_all = parameters();
  std::vector <double> params_values;
  for (unsigned int i = 0; i < ParameterCount(); i++)
    {
      params_values.push_back(params_all[i].value);
    }
  out->set_parameters(params_values);
  return out;
}
