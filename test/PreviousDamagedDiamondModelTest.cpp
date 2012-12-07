#include "../PreviousDamagedDiamondModel.h"

struct PreviousDamagedDiamondModelTestFixture
{
  PreviousDamagedDiamondModel model;
};

TEST_FIXTURE(PreviousDamagedDiamondModelTestFixture, RealIndex)
{
  CHECK_EQUAL(2.4, model.n(0.0));
  CHECK_EQUAL(2.4, model.n(1e14));
  CHECK_EQUAL(2.4, model.n(1e17));
  CHECK_CLOSE(2.3933, model.n(1e20), 1e-3);
  CHECK_CLOSE(2.3519, model.n(1e23), 1e-3);
}

TEST_FIXTURE(PreviousDamagedDiamondModelTestFixture, ImaginaryIndex)
{
  CHECK_EQUAL(0.0, model.kappa(0.0));
  CHECK_CLOSE(6.711e-10, model.kappa(1e14), 1e-13);
  CHECK_CLOSE(6.711e-7, model.kappa(1e17), 1e-10);
  CHECK_CLOSE(6.711e-4, model.kappa(1e20), 1e-7);
  CHECK_CLOSE(6.711e-1, model.kappa(1e23), 1e-4);
}

TEST_FIXTURE(PreviousDamagedDiamondModelTestFixture, p12)
{
  CHECK_CLOSE(-0.1447, model.p12( 0.0), 1e-4);
  CHECK_CLOSE(-0.1447, model.p12(1e14), 1e-4);
  CHECK_CLOSE(-0.1446, model.p12(1e17), 1e-4);
  CHECK_CLOSE(-0.1118, model.p12(1e20), 1e-4);
  CHECK_CLOSE( 0.1841, model.p12(1e23), 1e-4);
}

TEST_FIXTURE(PreviousDamagedDiamondModelTestFixture, Description)
{
  CHECK(model.description().length() > 0);
}
