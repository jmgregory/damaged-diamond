#include "../UndamagedDiamondModel.h"

TEST(RealIndex)
{
  CHECK_EQUAL(2.4, UndamagedDiamondModel().n(0.0));
  CHECK_EQUAL(2.4, UndamagedDiamondModel().n(1e15));
}

TEST(ImaginaryIndex)
{
  CHECK_EQUAL(0.0, UndamagedDiamondModel().kappa(0.0));
  CHECK_EQUAL(0.0, UndamagedDiamondModel().kappa(1e15));  
}

TEST(DNDEta)
{
  CHECK_EQUAL(-0.221184, UndamagedDiamondModel().dndeta(0.0));
  CHECK_EQUAL(-0.221184, UndamagedDiamondModel().dndeta(1e15));
}

TEST(DKappaDEta)
{
  CHECK_EQUAL(0.0, UndamagedDiamondModel().dkappadeta(0.0));
  CHECK_EQUAL(0.0, UndamagedDiamondModel().dkappadeta(1e15));  
}
