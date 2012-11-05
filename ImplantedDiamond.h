#ifndef JMG_IMPLANTED_DIAMOND_H
#define JMG_IMPLANTED_DIAMOND_H

#include <iostream>
#include <string>
#include <tr1/unordered_map>
#include "CapMaterialInterface.h"
#include "DiamondModelInterface.h"

class ImplantedDiamond : public CapMaterialInterface
{
 private:
  DiamondModelInterface *_model;
  double _fluence;

  double VacancyConcentration(double depth) const;

 public:
  ImplantedDiamond(DiamondModelInterface * model, double fluence);

  CapMaterialInterface * clone() const;
  
  double smallest_feature() const;
  double max_interesting_depth() const;
  double speed_of_sound(double z) const;
  double dndeta(double z, double lambda) const;
  double dkappadeta(double z, double lambda) const;
  double n(double z, double lambda) const;
  double kappa(double z, double lambda) const;
  void PrintCustomParameters(std::ostream & out = std::cout, std::string tag = "") const;
  TransducingLayer transducing_layer() const;  
};

#endif
