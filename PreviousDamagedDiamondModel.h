#ifndef JMG_PREVIOUS_DAMAGED_DIAMOND_MODEL_H
#define JMG_PREVIOUS_DAMAGED_DIAMOND_MODEL_H

#include <complex>
#include <string>
#include <sstream>
#include "DamageModelInterface.h"
#include "UndamagedDiamondModel.h"

using std::complex;

class PreviousDamagedDiamondModel : public DamageModelInterface
{
 private:
  double _A, _B;
  double _c;
  double _n0, _kappa0;

 public:
  PreviousDamagedDiamondModel()
   :_A(-6e-3), _B(3.3e19), _c(1.0/1.49e23), _n0(2.4542), _kappa0(0.0)
    { }

 PreviousDamagedDiamondModel(double A, double B, double c, double n0, double kappa0)
   :_A(A), _B(B), _c(c), _n0(n0), _kappa0(kappa0)
    { }

  double A() const { return _A; }
  double B() const { return _B; }
  double c() const { return _c; }
  
  void set_parameters(double A, double B, double c, double n0, double kappa0)
  {
    _A = A;
    _B = B;
    _c = c;
    _n0 = n0;
    _kappa0 = kappa0;
  }

  double n(double vacancy_concentration) const
  {
    if (vacancy_concentration < _B) return _n0;
    return _n0 + _A * log(vacancy_concentration / _B);
  }
  
  double kappa(double vacancy_concentration) const
  {
    return _c * vacancy_concentration;
  }

  double p12(double vacancy_concentration) const
  {
    /*    if (vacancy_concentration <= 1e21)
      {
	return -2.0 / (2.4 * 2.4 * 2.4) * (1.0 - vacancy_concentration / 4.4e20);
      }
      return p12(1e21);*/
    return UndamagedDiamondModel().p12(vacancy_concentration);
  }

  std::string description() const
  {
    std::stringstream ss;
    ss << "Damage model from older CAP Simulation code. ";
    ss << "A = " << _A << ", ";
    ss << "B = " << _B << ", ";
    ss << "c = " << _c << ", ";
    ss << "n0 = " << _n0 << ", ";
    ss << "kappa0 = " << _kappa0;
    return ss.str();
  }
};

#endif
