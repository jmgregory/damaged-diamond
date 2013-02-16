#include <cstdlib>
#include <iostream>
#include <vector>
#include <getopt.h>
#include "CapSimulation.h"
#include "ThreadedCapSimulationRunner.h"
#include "ImplantedDiamond.h"
#include "LagomarsinoDamageModel.h"
#include "UndamagedDiamondModel.h"

void print_data(const std::vector <CapPoint> & data, std::ostream & out = std::cout);
std::string to_upper(const std::string &);

int main(int argc, char *argv[])
{
  double start_time = 0e-12;
  double stop_time = 200e-12;
  double time_step = 0.25e-12;

  double fluence = 1e15;
  double reflectivity = 0.75;
  std::string model_name = "UNDAMAGED";
  bool quiet = false;
  int num_threads = 2;
  double n = UndamagedDiamondModel().n(0);
  double kappa = UndamagedDiamondModel().kappa(0);
  double p12 = UndamagedDiamondModel().p12(0);

  std::stringstream ss;
  int c;
  static struct option long_options[] =
    {
      {"fluence",      required_argument, 0, 'f'},
      {"start",        required_argument, 0, 's'},
      {"stop",         required_argument, 0, 'e'},
      {"step",         required_argument, 0, 'i'},
      {"kappa",        required_argument, 0, 'k'},
      {"model",        required_argument, 0, 'm'},
      {"reflectivity", required_argument, 0, 'R'},
      {"quiet",        no_argument,       0, 'q'},
      {"threads",      required_argument, 0, 't'},
      {"n",            required_argument, 0, 'n'},
      {"p12",          required_argument, 0, 'p'},
      {0, 0, 0, 0}
    };
  int option_index = 0;

  while (1)
    {
      c = getopt_long(argc, argv, "f:s:e:i:k:m:R:qt:n:p:", long_options, &option_index);
      
      if (c == -1)
	break;

      if (c != 'q')
	{
	  ss.clear();
	  ss.str(optarg);
	}

      switch (c)
	{
	case 'f':
	  ss >> fluence;
	  break;
	case 's':
	  ss >> start_time;
	  break;
	case 'e':
	  ss >> stop_time;
	  break;
	case 'i':
	  ss >> time_step;
	  break;
	case 'k':
	  ss >> kappa;
	  break;
	case 'm':
	  model_name = ss.str();
	  model_name = to_upper(model_name);
	  break;
	case 'R':
	  ss >> reflectivity;
	  break;
	case 'q':
	  quiet = true;
	  break;
	case 't':
	  ss >> num_threads;
	  break;
	case 'n':
	  ss >> n;
	  break;
	case 'p':
	  ss >> p12;
	  break;
       	}
    }

  DamageModelInterface * model;
  if (model_name == "UNDAMAGED")
    model = new UndamagedDiamondModel(n, kappa, p12);
  else if (model_name == "LAGOMARSINO")
    model = new LagomarsinoDamageModel();
  else
    {
      std::cerr << "Error: Unknown damage model: " << model_name << std::endl;
      exit(1);
    }

  TransducingLayer transducing_layer(reflectivity, 7.6e-9, 0.91, 2.70, 0.334, 23e-6);
  ImplantedDiamond material(model, fluence);
  material.set_transducing_layer(transducing_layer);
  CapSimulation simulation;
  simulation.set_material(&material);
  ThreadedCapSimulationRunner runner(&simulation);
  runner.set_time_delays(start_time, stop_time, time_step);
  runner.set_number_of_threads(num_threads);

  runner.PrintParameters(std::cout, "# ");
  if (!quiet) runner.PrintParameters(std::cerr, "");

  print_data(runner.Run());

  return 0;
}

void print_data(const std::vector <CapPoint> & data, std::ostream & out)
{
  out << "# Column 1: Time Delay (s)" << std::endl;
  out << "# Column 2: Reflectivity [(R - R0) / R0]" << std::endl;
  for (unsigned int i = 0; i < data.size(); i++)
    {
      out << data[i].time_delay << '\t' << data[i].reflectivity << std::endl;
    }
}

std::string to_upper(const std::string & s)
{
  std::string out = s;
  for (unsigned int i = 0; i < out.length(); i++)
    {
      if (out[i] >= 'a' && out[i] <= 'z') out[i] = out[i] + ('A' - 'a');
    }
  return out;
}
