#include <iostream>
#include <sstream>
#include <string>
#include "DamageModelFactory.h"

int main(int argc, char * argv[])
{
  std::stringstream ss;
  ss.str("");
  for (unsigned int i = 1; i < (unsigned int)argc; i++)
    {
      ss << argv[i];
      if (i < (unsigned int)argc - 1) ss << " ";
    }
  DamageModelInterface * model = DamageModelFactory::ParseCommandLine(ss.str());

  double start = 1e18;
  double stop = 1e25;
  double step = 1.005;

  model->print_parameters(std::cout, "# ");
  std::cout << "# Column 1: vacancy concentration (cm^-2)" << std::endl;
  std::cout << "# Column 2: n" << std::endl;
  std::cout << "# Column 3: kappa" << std::endl;
  std::cout << "# Column 4: p12" << std::endl;
  for (double C_V = start; C_V <= stop; C_V *= step)
    {
      std::cout << C_V << '\t';
      std::cout << model->n(C_V) << '\t';
      std::cout << model->kappa(C_V) << '\t';
      std::cout << model->p12(C_V);
      std::cout << std::endl;
    }

  return 0;
}
