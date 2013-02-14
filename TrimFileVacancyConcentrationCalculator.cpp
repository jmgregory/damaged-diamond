#include <fstream>
#include <sstream>
#include <assert.h>
#include "TrimFileVacancyConcentrationCalculator.h"
#include "Exception.h"

TrimFileVacancyConcentrationCalculator::TrimFileVacancyConcentrationCalculator(std::string filename, double fluence)
  : _fluence(fluence), _filename(filename)
{
  LoadFromFile();
}

std::string TrimFileVacancyConcentrationCalculator::description() const
{
  return std::string("TRIM Vacancy Concentration loaded from ") + _filename;
}

double TrimFileVacancyConcentrationCalculator::Interpolate(double x, double x1, double y1, double x2, double y2)
{
  double slope = (y2 - y1) / (x2 - x1);
  double offset = y1 - (slope * x1);
  return slope * x + offset;
}

double TrimFileVacancyConcentrationCalculator::vacancy_concentration(double depth) const
{
  assert(!trim_points.empty());
  if (depth < 0.0) return 0.0;
  if (depth < trim_points[0].depth) return trim_points[0].vacancy_density * _fluence;
  if (_fluence == 0.0) return 0.0;
  if (depth > trim_points[trim_points.size()-1].depth) return 0.0;
  for (unsigned int i = 0; i < trim_points.size() - 1; i++)
    {
      if ((depth >= trim_points[i].depth) && (depth < trim_points[i+1].depth))
	{
	  return _fluence * Interpolate(depth, trim_points[i].depth,   trim_points[i].vacancy_density, 
					       trim_points[i+1].depth, trim_points[i+1].vacancy_density);
	}
    }
  return 0.0;
}

void TrimFileVacancyConcentrationCalculator::LoadFromFile()
{
  std::stringstream string_stream;
  std::string temp;
  trim_point temp_point;
  double throw_away;

  std::ifstream infile;
  infile.open(_filename.c_str());
  if (!infile)
    {
      throw Exception(std::string("Could not open file ") + _filename);
    }

  trim_points.resize(0);
  while (infile)
    {
      getline(infile, temp);
      if(temp.length() > 0 && temp[0] != '#')
	{
	  string_stream.str("");
	  string_stream.clear();
	  string_stream.str(temp);
	  string_stream >> temp_point.depth >> throw_away >> temp_point.vacancy_density;
	  temp_point.depth *= 1e-10;
	  temp_point.vacancy_density *= 1e8;
	  trim_points.push_back(temp_point);
	}
    }
}
