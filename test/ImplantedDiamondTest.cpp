#include <sstream>
#include <UnitTest++.h>
#include "../ImplantedDiamond.h"
#include "../UndamagedDiamondModel.h"
#include "../PreviousDamagedDiamondModel.h"

struct ImplantedDiamondTestFixture
{
  ImplantedDiamondTestFixture() 
    : undamaged_model(), 
      unimplanted(ImplantedDiamond(&undamaged_model, 0.0)) 
  {}
  
  UndamagedDiamondModel undamaged_model;
  ImplantedDiamond unimplanted;
  std::stringstream string_stream;
};

TEST_FIXTURE(ImplantedDiamondTestFixture, SmallestFeature)
{
  CHECK_EQUAL(20e-9, unimplanted.smallest_feature());
}

TEST_FIXTURE(ImplantedDiamondTestFixture, MaxInterestingDepth)
{
  CHECK_EQUAL(3.51e-6, unimplanted.max_interesting_depth());
}

TEST_FIXTURE(ImplantedDiamondTestFixture, SpeedOfSound)
{
  CHECK_EQUAL(17520.0, unimplanted.speed_of_sound(0.0));
}

TEST_FIXTURE(ImplantedDiamondTestFixture, IndexValues)
{
  CHECK_EQUAL(2.4, unimplanted.n(0.0, 0.0));
  CHECK_EQUAL(2.4, unimplanted.n(100e-9, 850e-9));
  CHECK_EQUAL(0.0, unimplanted.kappa(0.0, 0.0));
  CHECK_EQUAL(0.0, unimplanted.kappa(100e-9, 850e-9));
  CHECK_EQUAL(-0.221184, unimplanted.dndeta(0.0, 0.0));
  CHECK_EQUAL(-0.221184, unimplanted.dndeta(100e-9, 850e-9));
  CHECK_EQUAL(0.0, unimplanted.dkappadeta(0.0, 0.0));
  CHECK_EQUAL(0.0, unimplanted.dkappadeta(100e-9, 850-9));
}

TEST_FIXTURE(ImplantedDiamondTestFixture, DescriptionProducesText)
{
  CHECK(unimplanted.description().length() > 0);
}

TEST_FIXTURE(ImplantedDiamondTestFixture, ParameterOutputProducesText)
{
  unimplanted.PrintCustomParameters(string_stream);
  CHECK(string_stream.str().length() > 0);
}

TEST_FIXTURE(ImplantedDiamondTestFixture, ParameterOutputUsesCustomTag)
{
  unimplanted.PrintCustomParameters(string_stream, "myTAG");
  CHECK_EQUAL("myTAG", string_stream.str().substr(0, 5));
}
