#include <sstream>
#include <UnitTest++.h>
#include "../ImplantedDiamond.h"
#include "../UndamagedDiamondModel.h"

struct ImplantedDiamondTestFixture
{
  ImplantedDiamondTestFixture() 
    : model(), fluence(1e10), implanted(ImplantedDiamond(&model, fluence)), unimplanted(ImplantedDiamond(&model, 0.0)) {}
  
  double fluence;
  ImplantedDiamond implanted;
  ImplantedDiamond unimplanted;
  UndamagedDiamondModel model;
  std::stringstream string_stream;
};

TEST_FIXTURE(ImplantedDiamondTestFixture, SmallestFeature)
{
  CHECK_EQUAL(20e-9, unimplanted.smallest_feature());
}

TEST_FIXTURE(ImplantedDiamondTestFixture, MaxInterestingDepth)
{
  CHECK_EQUAL(2e-6, unimplanted.max_interesting_depth());
}

TEST_FIXTURE(ImplantedDiamondTestFixture, SpeedOfSound)
{
  CHECK_EQUAL(17520.0, unimplanted.speed_of_sound(0.0));
  CHECK_EQUAL(17520.0, implanted.speed_of_sound(900e-9));
}

TEST_FIXTURE(ImplantedDiamondTestFixture, IndexValues)
{
  CHECK_EQUAL(2.4, unimplanted.n(0.0, 0.0));
  CHECK_EQUAL(2.4, unimplanted.n(850e-9, 100e-9));

  double A = -6.01e-3;
  double B = 3.03e-20; // cm3                                                                                                                              
  double Vc = (2695.34E-05 * 1e8 * fluence);
  std::cerr << Vc << std::endl;
  std::cerr << B*Vc << std::endl;
  std::cerr << log(B*Vc) << std::endl;
  //CHECK_EQUAL(2.4 + (A * log(B * Vc)), implanted.n(1.72e-6, 0.0));

  //CHECK_EQUAL(2.4, implanted.n(1.99e-6, 0.0));
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
