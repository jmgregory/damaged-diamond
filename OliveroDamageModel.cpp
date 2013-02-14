#include "OliveroDamageModel.h"
#include "UndamagedDiamondModel.h"

double OliveroDamageModel::n(double vacancy_concentration) const
{
  return 2.47 + 4.3e-23 * vacancy_concentration;
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
  return "Damage model for real index from Olivero et al Diamond and Related Materials 19, 428 (2010). Imaginary index and p12 are same as undamaged diamond.";
}

