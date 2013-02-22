#include <sstream>
#include <cstdlib>
#include "DamageModelFactory.h"
#include "LagomarsinoDamageModel.h"
#include "OliveroDamageModel.h"
#include "PreviousDamagedDiamondModel.h"
#include "UndamagedDiamondModel.h"
#include "IndependentExponentialModel.h"

DamageModelInterface * DamageModelFactory::GetModelFromString(const std::string & name)
{
  std::string upper_name = to_upper(name);

  std::vector <DamageModelInterface *> models = GetAllModels();
  int found_model_id = -1;
  for (unsigned int i = 0; i < models.size(); i++)
    {
      if (upper_name == to_upper(models[i]->name()))
	{
	  found_model_id = i;
	  i = models.size();
	} 
    }
  if (found_model_id != -1)
    {
      for (unsigned int i = 0; i < models.size(); i++)
	{
	  if ((int)i != found_model_id) delete models[i];
	}
      return models[found_model_id];
    }
  else
    {
      std::cerr << "Error: DamageModelFactory: unknown damage model: " << name << std::endl;
      std::cerr << "Please specify a damage model.  Available models:" << std::endl;
      std::vector <DamageModelInterface *> models = GetAllModels();
      for (unsigned int i = 0; i < models.size(); i++)
	{
	  std::cerr << std::endl;
	  std::cerr << "[" << models[i]->name() << "] - " << models[i]->ParameterCount() << " parameter(s)" << std::endl << models[i]->description() << std::endl;
	}
      exit(1);
    }
}

std::vector <DamageModelInterface *> DamageModelFactory::GetAllModels()
{
  std::vector <DamageModelInterface *> output;
  output.push_back(new LagomarsinoDamageModel());
  output.push_back(new OliveroDamageModel());
  output.push_back(new PreviousDamagedDiamondModel());
  output.push_back(new UndamagedDiamondModel());
  output.push_back(new IndependentExponentialModel());
  return output;
}

std::string DamageModelFactory::to_upper(const std::string & s)
{
  std::string out = s;
  for (unsigned int i = 0; i < s.length(); i++)
    {
      if (s[i] >= 'a' || s[i] <= 'z') out[i] = out[i] + ('A' - 'a');
    }
  return out;
}

DamageModelInterface * DamageModelFactory::ParseCommandLine(const std::string & model_string)
{
  std::string this_arg;
  std::vector <std::string> arguments;
  std::stringstream ss;
  ss.str(model_string);
  while (!ss.eof())
    {
      ss >> this_arg;
      arguments.push_back(this_arg);
    }  
  DamageModelInterface * model = GetModelFromString(arguments[0]);
  if (arguments.size() - 1 != model->ParameterCount())
    {
      std::cerr << "Error: model " << model->name() << " expects " << model->ParameterCount() << " parameters." << std::endl;
      std::cerr << model->name() << ": " << model->description() << std::endl;
      std::cerr << "Parameters:" << std::endl;
      std::vector <Parameter> param_list = model->parameters();
      for (unsigned int i = 0; i < param_list.size(); i++)
	{
	  std::cerr << "  " << i+1 << ": " << param_list[i].name;
	  if (param_list[i].units != "")
	    {
	      std::cerr << " (" << param_list[i].units << ")";
	    }
	  std::cerr << std::endl;
	}
      std::cerr << "Example: \"" << model->name();
      for (unsigned int i = 0; i < param_list.size(); i++)
	{
	  std::cerr << " " << param_list[i].value;
	}
      std::cerr << "\"" << std::endl;
      exit(1);
    }
  std::vector <double> parameters;
  parameters.resize(model->ParameterCount());
  for (unsigned int i = 0; i < model->ParameterCount(); i++)
    {
      ss.clear();
      ss.str(arguments[i+1]);
      ss >> parameters[i];
    }
  model->set_parameters(parameters);
  return model;
}
