#ifndef JMG_TRIM_FILE_VACANCY_CONCENTRATION_CALCULATOR_H
#define JMG_TRIM_FILE_VACANCY_CONCENTRATION_CALCULATOR_H

#include <vector>
#include <string>
#include "VacancyConcentrationCalculatorInterface.h"

class TrimFileVacancyConcentrationCalculator : public VacancyConcentrationCalculatorInterface
{
 public:
  TrimFileVacancyConcentrationCalculator(std::string filename, double fluence);
  double vacancy_concentration(double depth);
  std::string description();

 private:
  double _fluence;
  std::string _filename;
  
  void LoadFromFile();
  static double Interpolate(double x, double x1, double y1, double x2, double y2);

  struct trim_point
  {
    double depth;
    double vacancy_density;
  };

  std::vector <trim_point> trim_points;
};

#endif
