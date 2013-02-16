#ifndef JMG_IMPLANTED_DIAMOND_H
#define JMG_IMPLANTED_DIAMOND_H

#include <iostream>
#include <string>
#include <tr1/unordered_map>
#include "CapMaterialInterface.h"
#include "DamageModelInterface.h"
#include "TrimFileVacancyConcentrationCalculator.h"

class ImplantedDiamond : public CapMaterialInterface
{
 private:
  DamageModelInterface *_model;
  double _fluence;
  TrimFileVacancyConcentrationCalculator _trim_calculator;
  TransducingLayer _transducing_layer;
  std::tr1::unordered_map<double,double> * _vacancy_map;

  double VacancyConcentration(double depth) const;
  double p12(double z, double lambda) const;

 public:
  ImplantedDiamond(DamageModelInterface * model, double fluence);
  ~ImplantedDiamond();

  CapMaterialInterface * clone() const;
  
  double smallest_feature() const;
  double max_interesting_depth() const;
  double speed_of_sound(double z) const;
  double n(double z, double lambda) const;
  double kappa(double z, double lambda) const;
  std::string description() const;
  void PrintCustomParameters(std::ostream & out = std::cout, std::string tag = "") const;
  TransducingLayer transducing_layer() const;
  void set_transducing_layer(const TransducingLayer & tl);
};

#endif
