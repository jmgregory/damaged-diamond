#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <gsl/gsl_multimin.h>
#include "DamageModelInterface.h"
#include "DamageModelFactory.h"
#include "ImplantedDiamond.h"
#include "ThreadedCapSimulationRunner.h"
#include "CapSimulation.h"

struct fit_run
{
  std::string experimental_file;
  std::string simulation_file;
  double fluence;
  double reflectivity;
  double kappa_0;
  double start_time;
  double stop_time;
  double time_step;
  double early_cutoff;
  double correction_shift;
};

struct cap_point
{
  double time;
  double R;
};

struct fit_context
{
  fit_context(DamageModelInterface * _model,
	      const std::vector <fit_run> & _fit_run_parameters,
	      const std::vector <Parameter> & _seed,
	      const std::vector <bool> & _locked_parameters)
    : model(_model),
      fit_run_parameters(_fit_run_parameters),
      seed(_seed),
      locked_parameters(_locked_parameters)
  { }

  DamageModelInterface * model;
  std::vector <fit_run> fit_run_parameters;
  std::vector <Parameter> seed;
  std::vector <bool> locked_parameters;
};

std::vector <CapPoint> LoadCapDataFromFile(std::string filename);
std::vector <fit_run> load_params_file(std::string filename);
gsl_vector * stl_vector_to_gsl(const std::vector <double> & stl);
gsl_vector * stl_vector_to_gsl(const std::vector <Parameter> & stl);
std::vector <double> gsl_vector_to_stl(const gsl_vector * gsl);
double fit_helper(const gsl_vector *params, void *con);
std::vector <bool> process_locked_parameters(std::string * model_string);
void scale_horizontal(std::vector <CapPoint> * points, double scale);
void shift_horizontal(std::vector <CapPoint> * points, double shift);
void remove_offset(std::vector <CapPoint> * points);
void WriteData(const std::vector <CapPoint> & exp_points, const std::vector <CapPoint> & sim_points, std::string filename, std::string header = "");

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      std::cerr << "Usage: " << argv[0] << " \"model parameter1 parameter2 ...\"" << std::endl;
      std::cerr << "Place an L before a parameter to lock its value" << std::endl;
      exit(1);
    }

  std::string model_string = argv[1];
  std::vector <bool> locked_parameters = process_locked_parameters(&model_string);
  DamageModelInterface * model = DamageModelFactory::ParseCommandLine(model_string);
  std::vector <fit_run> fit_run_parameters = load_params_file("fitting-params.dat");
  gsl_multimin_function fit_func;

  unsigned int free_parameter_count = 0;
  for (unsigned int i = 0; i < model->parameters().size(); i++)
    {
      if (!locked_parameters[i])
	{
	  free_parameter_count++;
	}
    }

  fit_func.n = free_parameter_count;
  fit_func.f = fit_helper;
  fit_func.params = new fit_context(model, fit_run_parameters, model->parameters(), locked_parameters);
  gsl_vector * seed = gsl_vector_alloc(free_parameter_count);
  gsl_vector * step_sizes = gsl_vector_alloc(free_parameter_count);
  unsigned int j = 0;
  double stop_size = 0.0;
  for (unsigned int i = 0; i < free_parameter_count; i++)
    {
      while (j < locked_parameters.size() && locked_parameters[j])
	{
	  j++;
	}
      gsl_vector_set(seed, i, model->parameters()[j].value);
      gsl_vector_set(step_sizes, i, model->parameters()[j].value / 10.0);
      j++;
      stop_size += gsl_vector_get(step_sizes, i) * gsl_vector_get(step_sizes, i);
    }  
  model->print_parameters();
  stop_size /= free_parameter_count;
  stop_size /= 10000.0;
  stop_size = sqrt(stop_size);
  std::cerr << "Stopping size = " << stop_size << std::endl;
  const gsl_multimin_fminimizer_type *min_type = gsl_multimin_fminimizer_nmsimplex2;
  gsl_multimin_fminimizer * minimizer = gsl_multimin_fminimizer_alloc(min_type, free_parameter_count);
  gsl_multimin_fminimizer_set(minimizer, &fit_func, seed, step_sizes);
  
  size_t iter = 0;
  int status;
  double size = 0.0;
  do
    {
      iter++;
      status = gsl_multimin_fminimizer_iterate(minimizer);
      
      if (status) 
	break;
     
      size = gsl_multimin_fminimizer_size(minimizer);
      status = gsl_multimin_test_size(size, stop_size);
      
      std::cerr << "Iteration: " << iter << std::endl;
      model->print_parameters(std::cerr);
      std::cerr << " f() = " << minimizer->fval << std::endl;
      std::cerr << " size = " << size << std::endl;
      std::cerr << std::endl;
      std::cerr << model->name();
      for (unsigned int i = 0; i < model->ParameterCount(); i++)
	{
	  std::cerr << " " << model->parameters()[i].value;
	}
      std::cerr << std::endl;
      system("gnuplot ./plot-sim-output.gp");

      if (status == GSL_SUCCESS)
	{
	  std::cerr << "Converged to minimum at:" << std::endl;
	}
      
    }
  while (status == GSL_CONTINUE && iter < 1000);

  std::cerr << "Iteration: " << iter << std::endl;
  model->print_parameters(std::cerr);
  std::cerr << " f() = " << minimizer->fval << std::endl;
  std::cerr << " size = " << size << std::endl;
  std::cerr << std::endl;
  std::cerr << model->name();
  for (unsigned int i = 0; i < model->ParameterCount(); i++)
    {
      std::cerr << " " << model->parameters()[i].value;
    }
  std::cerr << std::endl;
  
  gsl_vector_free(seed);
  gsl_vector_free(step_sizes);
  gsl_multimin_fminimizer_free(minimizer);
  
  return status;
}

double fit_helper(const gsl_vector *params, void *con)
{
  fit_context * context = (fit_context *)con;
  std::vector <bool> locked_parameters = context->locked_parameters;
  std::vector <fit_run> fit_run_parameters = context->fit_run_parameters;
  std::vector <double> these_params;
  unsigned int j = 0;
  for (unsigned int i = 0; i < locked_parameters.size(); i++)
    {
      if (locked_parameters[i])
	{
	  these_params.push_back(context->seed[i].value);
	}
      else
	{ 
	  these_params.push_back(gsl_vector_get(params, j));
	  j++;
	}
    }
  context->model->set_parameters(these_params);

  ImplantedDiamond * material;
  CapSimulation * simulation;
  ThreadedCapSimulationRunner * runner;
  std::vector <CapPoint> sim_points;
  std::vector <CapPoint> exp_points;
  double sum = 0.0;
  double diff;
  std::stringstream ss;
  for (unsigned int run = 0; run < fit_run_parameters.size(); run++)
    {
      exp_points = LoadCapDataFromFile(fit_run_parameters[run].experimental_file);

      material = new ImplantedDiamond(context->model, fit_run_parameters[run].fluence);
      material->set_transducing_layer(TransducingLayer(fit_run_parameters[run].reflectivity, 7.6e-9, 0.91, 2.70, 0.334, 23e-6));
      simulation = new CapSimulation();
      simulation->set_material(material);
      runner = new ThreadedCapSimulationRunner(simulation);
      runner->set_number_of_threads(2);
      runner->set_time_delays((fit_run_parameters[run].start_time - fit_run_parameters[run].correction_shift) * 1e-12,
			     (fit_run_parameters[run].stop_time - fit_run_parameters[run].correction_shift) * 1e-12,
			     fit_run_parameters[run].time_step * 1e-12);
      sim_points = runner->Run();      
      ss.str("");
      ss.clear();
      runner->PrintParameters(ss, "# ");
      delete runner;
      delete simulation;
      delete material;

      scale_horizontal(&sim_points, 1e12);
      shift_horizontal(&sim_points, fit_run_parameters[run].correction_shift);
      remove_offset(&sim_points);
        
      WriteData(exp_points, sim_points, fit_run_parameters[run].simulation_file, ss.str());

      if (sim_points.size() != exp_points.size())
	{
	  std::cerr << "Error: different numbers of points between " 
		    << fit_run_parameters[run].experimental_file << " and simulation output (see " 
		    << fit_run_parameters[run].simulation_file << ")" << std::endl;
	  exit(1);
	}
      for (unsigned int i = 0; i < sim_points.size(); i++)
	{
       	  if ((abs(sim_points[i].time_delay - exp_points[i].time_delay) / sim_points[i].time_delay) > 0.0001)
	    {
	      std::cerr << "Warning: time delays " << sim_points[i].time_delay << " and " 
			<< exp_points[i].time_delay << " don't match up for " 
			<< fit_run_parameters[run].experimental_file << std::endl;
	    }
	  if (sim_points[i].time_delay >= fit_run_parameters[run].early_cutoff)
	    {
	      diff = sim_points[i].reflectivity - exp_points[i].reflectivity;
	      sum += diff * diff;
	    }
	}
    }
  return sum;
}

std::vector <bool> process_locked_parameters(std::string * model_string)
{
  std::vector <std::string> words;
  std::string this_word;
  std::vector <bool> locked_parameters;
  std::stringstream ss;
  ss.str(*model_string);
  while (!ss.eof())
    {
      ss >> this_word;
      words.push_back(this_word);
    }
  ss.clear();
  ss.str("");
  ss << words[0];
  for (unsigned int i = 1; i < words.size(); i++)
    {
      if (words[i][0] == 'L')
	{
	  locked_parameters.push_back(true);
	  words[i] = words[i].substr(1);
	}
      else
	{
	  locked_parameters.push_back(false);
	}
      ss << " " << words[i];
    }
  (*model_string) = ss.str();
  return locked_parameters;
}

std::vector <CapPoint> LoadCapDataFromFile(std::string filename)
{
  std::ifstream infile;
  infile.open(filename.c_str());
  if (!infile)
    {
      std::cerr << "Error: could not open " << filename << std::endl;
      exit(1);
    }
  std::vector <CapPoint> output;
  std::string this_line;
  std::stringstream ss;
  CapPoint temp;
  while (infile)
    {
      getline(infile, this_line);
      if (!(this_line.length() == 0 || this_line[0] == '#'))
	{
	  ss.clear();
	  ss.str(this_line);
	  ss >> temp.time_delay >> temp.reflectivity;
	  output.push_back(temp);
	}
    }
  infile.close();
  return output;
}

std::vector <fit_run> load_params_file(std::string filename)
{
  std::ifstream infile;
  infile.open(filename.c_str());
  if (!infile)
    {
      std::cerr << "Error: could not open " << filename << std::endl;
      exit(1);
    }
  std::stringstream ss;
  fit_run temp;
  std::string this_line;
  std::vector <fit_run> output;
  while (infile)
    {
      getline(infile, this_line);
      if (!(this_line.length() == 0 || this_line[0] == '#'))
	{
	  ss.clear();
	  ss.str(this_line);
	  ss >> temp.experimental_file 
	     >> temp.fluence 
	     >> temp.reflectivity 
	     >> temp.kappa_0
	     >> temp.start_time 
	     >> temp.stop_time 
	     >> temp.time_step 
	     >> temp.early_cutoff
	     >> temp.correction_shift;
	  
	  temp.simulation_file = std::string("sim-output/") + temp.experimental_file;
	  temp.experimental_file = std::string("experimental-data/") + temp.experimental_file;
	  output.push_back(temp);
	}
    }
  infile.close();

  return output;
}

gsl_vector * stl_vector_to_gsl(const std::vector <double> & stl)
{
  gsl_vector * out = gsl_vector_alloc(stl.size());
  for (unsigned int i = 0; i < stl.size(); i++)
    {
      gsl_vector_set(out, i, stl[i]);
    }
  return out;
}

gsl_vector * stl_vector_to_gsl(const std::vector <Parameter> & stl)
{
  gsl_vector * out = gsl_vector_alloc(stl.size());
  for (unsigned int i = 0; i < stl.size(); i++)
    {
      gsl_vector_set(out, i, stl[i].value);
    }
  return out;
}

std::vector <double> gsl_vector_to_stl(const gsl_vector * gsl)
{
  std::vector <double> out;
  for (unsigned int i = 0; i < gsl->size; i++)
    {
      out.push_back(gsl_vector_get(gsl, i));
    }
  return out;
}

void scale_horizontal(std::vector <CapPoint> * points, double scale)
{
  for (unsigned int i = 0; i < points->size(); i++)
    {
      (*points)[i].time_delay *= scale;
    }
}

void shift_horizontal(std::vector <CapPoint> * points, double shift)
{
  for (unsigned int i = 0; i < points->size(); i++)
    {
      (*points)[i].time_delay += shift;
    }  
}

void remove_offset(std::vector <CapPoint> * points)
{
  double sum = 0.0;
  for (unsigned int i = 0; i < points->size(); i++)
    {
      sum += (*points)[i].reflectivity;
    }  
  double average = sum / double(points->size());
  for (unsigned int i = 0; i < points->size(); i++)
    {
      (*points)[i].reflectivity -= average;
    }
}

void WriteData(const std::vector <CapPoint> & exp_points, const std::vector <CapPoint> & sim_points, std::string filename, std::string header)
{
  std::ofstream outfile;
  outfile.open(filename.c_str());
  if (!outfile)
    {
      std::cerr << "Error: could not open " << filename << " for output." << std::endl;
    }
  outfile << header;
  for (unsigned int i = 0; i < sim_points.size(); i++)
    {
      outfile << exp_points[i].time_delay << '\t' << exp_points[i].reflectivity << '\t' << sim_points[i].reflectivity << std::endl;
    }
  outfile.close();
}
