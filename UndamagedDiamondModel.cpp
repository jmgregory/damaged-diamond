#include "UndamagedDiamondModel.h"

UndamagedDiamondModel::UndamagedDiamondModel()
  :_n(2.4542), // Best fit to period of experimental data with vs = 17.52 nm/ps
   _kappa(0.0),
   _p12(0.032) // L. S. Hounsome, R. Jones, M. J. Shaw, and P. R. Briddon, physica status solidi (a), vol. 203, no. 12, pp. 3088-3093 (2006)
{}

UndamagedDiamondModel::UndamagedDiamondModel(double n, double kappa, double p12)
  :_n(n), _kappa(kappa), _p12(p12)
{}
  
