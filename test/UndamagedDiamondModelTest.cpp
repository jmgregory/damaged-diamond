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

TEST(p12)
{
  CHECK_EQUAL(0.032, UndamagedDiamondModel().p12(0.0));
  CHECK_EQUAL(0.032, UndamagedDiamondModel().p12(1e15));
}

TEST(Description)
{
  CHECK(UndamagedDiamondModel().description().length() > 0);
}
