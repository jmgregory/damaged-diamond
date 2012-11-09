#include "ImplantedDiamond.h"

ImplantedDiamond::ImplantedDiamond(DamageModelInterface *model, double fluence)
  : _model(model), _fluence(fluence)
{ }

double ImplantedDiamond::smallest_feature() const
{
  return 20e-9; // m
}

double ImplantedDiamond::max_interesting_depth() const
{
  return 2e-6; // m
}

double ImplantedDiamond::speed_of_sound(double z) const
{
  return 17520.0; // m/s
}

double ImplantedDiamond::p12(double z, double lambda) const
{
  return _model->p12(VacancyConcentration(z));
}

double ImplantedDiamond::n(double z, double lambda) const
{
  return _model->n(VacancyConcentration(z));
}

double ImplantedDiamond::kappa(double z, double lambda) const
{
  return _model->kappa(VacancyConcentration(z));
}

std::string ImplantedDiamond::description() const
{
  return std::string("Implanted diamond sample using damage model: ") + _model->description();
}

void ImplantedDiamond::PrintCustomParameters(std::ostream & out, std::string tag) const
{
  out << tag << "           Fluence: " << _fluence << " cm-2" << std::endl;
}

TransducingLayer ImplantedDiamond::transducing_layer() const
{
  return TransducingLayer();
}

double ImplantedDiamond::VacancyConcentration(double depth) const
{
  return 0.0;
}

CapMaterialInterface * ImplantedDiamond::clone() const
{
  ImplantedDiamond * output = new ImplantedDiamond(_model, _fluence);
  return output;
}
