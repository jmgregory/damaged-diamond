#include <tr1/unordered_map>
#include "ImplantedDiamond.h"

ImplantedDiamond::ImplantedDiamond(DamageModelInterface *model, double fluence)
  : _model(model), 
    _fluence(fluence), 
    _trim_calculator("1-MeV-He-in-Diamond.dat", _fluence),
    _transducing_layer(TransducingLayer())
{ 
  _vacancy_map = new std::tr1::unordered_map<double,double>();
}

ImplantedDiamond::~ImplantedDiamond()
{
  delete _vacancy_map;
}

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
  if (z < 0) return 0.0;
  return _model->p12(VacancyConcentration(z));
}

double ImplantedDiamond::n(double z, double lambda) const
{
  if (z < 0) return 1.0;
  return _model->n(VacancyConcentration(z));
}

double ImplantedDiamond::kappa(double z, double lambda) const
{
  if (z < 0) return 0.0;
  return _model->kappa(VacancyConcentration(z));
}

std::string ImplantedDiamond::description() const
{
  return std::string("Implanted diamond sample using damage model: ") + _model->description();
}

void ImplantedDiamond::PrintCustomParameters(std::ostream & out, std::string tag) const
{
  out << tag << "                         Fluence: " << _fluence << " cm-2" << std::endl;
  out << tag << "                 TRIM Calculator: " << _trim_calculator.description() << std::endl;
}

TransducingLayer ImplantedDiamond::transducing_layer() const
{
  return _transducing_layer;
}

double ImplantedDiamond::VacancyConcentration(double depth) const
{
  std::tr1::unordered_map<double,double>::const_iterator got = _vacancy_map->find(depth);
  if (got == _vacancy_map->end())
    {
      double result = _trim_calculator.vacancy_concentration(depth);
      _vacancy_map->insert(std::pair<double,double>(depth, result));
      return result;
    }
  return got->second;
}

void ImplantedDiamond::set_transducing_layer(const TransducingLayer & tl)
{
  _transducing_layer = tl;
}

CapMaterialInterface * ImplantedDiamond::clone() const
{
  ImplantedDiamond * output = new ImplantedDiamond(_model, _fluence);
  output->set_transducing_layer(_transducing_layer);
  return output;
}
