#include "LagomarsinoDamageModel.h"
#include "UndamagedDiamondModel.h"

double LagomarsinoDamageModel::n(double vacancy_concentration) const
{
  UndamagedDiamondModel model;
  return model.n(vacancy_concentration) + 4.34e-23 * vacancy_concentration;
}

double LagomarsinoDamageModel::kappa(double vacancy_concentration) const
{
  UndamagedDiamondModel model;
  return model.kappa(vacancy_concentration) + 2.86e-23 * vacancy_concentration;
}

double LagomarsinoDamageModel::p12(double vacancy_concentration) const
{
  UndamagedDiamondModel model;
  return model.p12(vacancy_concentration);
}

std::string LagomarsinoDamageModel::description() const
{
  return "Damage model for complex index from Lagomarsino et al Opt. Express 20, 19382 (2012). p12 is same as undamaged diamond";
}

