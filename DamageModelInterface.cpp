#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "DamageModelInterface.h"

void DamageModelInterface::set_parameters(const std::vector <double> & new_parameters)
{
  if (new_parameters.size() != ParameterCount())
    {
      std::cerr << "Error: Incorrect number of parameters to set_parameters(). Expected: " << ParameterCount() << ", actual: " << new_parameters.size() << std::endl;
      exit(1);
    }
  _set_parameters(new_parameters);
}

void DamageModelInterface::print_parameters(std::ostream & out, std::string tag) const
{
  out << tag << "                Model Parameters:";
  if (ParameterCount() == 0)
    {
      out << " (none)" << std::endl;
      return;
    }
  out << std::endl;
  std::vector <Parameter> params = parameters();
  unsigned int biggest_param_name = 0;
  unsigned int biggest_param_value = 0;
  unsigned int lead_space;
  std::stringstream ss;
  for (unsigned int i = 0; i < params.size(); i++)
    {
      if (params[i].name.length() > biggest_param_name) biggest_param_name = params[i].name.length();
      ss.clear();
      ss.str("");
      ss << std::setprecision(15) << params[i].value;
      if (ss.str().length() > biggest_param_value) biggest_param_value = ss.str().length();
    }
  if (biggest_param_name > 32) lead_space = 0;
  else lead_space = 32 - biggest_param_name;
  for (unsigned int i = 0; i < params.size(); i++)
    {
      out << tag;
      for (unsigned int j = 0; j < lead_space; j++) out << " ";
      out << std::setw(biggest_param_name) << params[i].name << " = " << std::setw(biggest_param_value) << std::right << std::setprecision(15) << params[i].value << " " << params[i].units << std::endl;
    }
}
