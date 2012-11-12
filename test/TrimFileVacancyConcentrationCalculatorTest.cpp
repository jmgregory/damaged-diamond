#include "../TrimFileVacancyConcentrationCalculator.h"

struct TrimFileVacancyConcentrationCalculatorTestFixture
{
  TrimFileVacancyConcentrationCalculatorTestFixture()
    : calculator("1-MeV-He-in-Diamond.dat", 1e15)
  { }

  TrimFileVacancyConcentrationCalculator calculator;
};

TEST_FIXTURE(TrimFileVacancyConcentrationCalculatorTestFixture, DescriptionProducesText)
{
  CHECK(calculator.description().length() > 0);
}

TEST_FIXTURE(TrimFileVacancyConcentrationCalculatorTestFixture, NoVacanciesWithNoFluence)
{
  TrimFileVacancyConcentrationCalculator null_calculator("1-MeV-He-in-Diamond.dat", 0.0);
  CHECK_EQUAL(0.0, null_calculator.vacancy_concentration(0.0));
  CHECK_EQUAL(0.0, null_calculator.vacancy_concentration(100e-9));
  CHECK_EQUAL(0.0, null_calculator.vacancy_concentration(17200e-10));
  CHECK_EQUAL(0.0, null_calculator.vacancy_concentration(5e-6));
}

TEST_FIXTURE(TrimFileVacancyConcentrationCalculatorTestFixture, VacancyConcentrationValues)
{
  CHECK_EQUAL(4.20042e18, calculator.vacancy_concentration(0.0));
  CHECK_CLOSE(3.36537e19, calculator.vacancy_concentration(100e-9), 0.0001e19);
  CHECK_EQUAL(2.69534e21, calculator.vacancy_concentration(17200e-10));
  CHECK_EQUAL(0.0, calculator.vacancy_concentration(5e-6));
}
