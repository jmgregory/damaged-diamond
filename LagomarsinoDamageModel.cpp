#include <sstream>
#include "LagomarsinoDamageModel.h"
#include "UndamagedDiamondModel.h"

LagomarsinoDamageModel::LagomarsinoDamageModel()
  :_n0(2.41),
   _kappa0(0.0),
   _p12(UndamagedDiamondModel().p12(0))
{}

LagomarsinoDamageModel::LagomarsinoDamageModel(double n0, double kappa0, double p12)
  :_n0(n0), _kappa0(kappa0), _p12(p12)
{}

double LagomarsinoDamageModel::n(double vacancy_concentration) const
{
  UndamagedDiamondModel model;
  return _n0 + 4.34e-23 * vacancy_concentration;
}

double LagomarsinoDamageModel::kappa(double vacancy_concentration) const
{
  return _kappa0 + 2.86e-23 * vacancy_concentration;
}

double LagomarsinoDamageModel::p12(double vacancy_concentration) const
{
  return _p12;
}

std::string LagomarsinoDamageModel::description() const
{
  std::stringstream ss;
  ss << "Damage model for complex index from Lagomarsino et al Opt. Express 20, 19382 (2012), " 
     << "n = (" << _n0 << " + " << _kappa0 << "i) + (4.34e-23 cm^3 + 2.86e-23i cm^3) * C_V, p12 = " << _p12 << ".";
  return ss.str();
}

