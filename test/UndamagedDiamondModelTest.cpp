#include "../UndamagedDiamondModel.h"

struct UndamagedDiamondModelTestFixture
{
  UndamagedDiamondModel model;
};

TEST_FIXTURE(UndamagedDiamondModelTestFixture, RealIndex)
{
  CHECK_EQUAL(2.4, model.n(0.0));
  CHECK_EQUAL(2.4, model.n(1e15));
}

TEST_FIXTURE(UndamagedDiamondModelTestFixture, ImaginaryIndex)
{
  CHECK_EQUAL(0.0, model.kappa(0.0));
  CHECK_EQUAL(0.0, model.kappa(1e15));  
}

TEST_FIXTURE(UndamagedDiamondModelTestFixture, p12)
{
  CHECK_EQUAL(0.032, model.p12(0.0));
  CHECK_EQUAL(0.032, model.p12(1e15));
}

TEST_FIXTURE(UndamagedDiamondModelTestFixture, Description)
{
  CHECK(model.description().length() > 0);
}
