#ifndef JMG_CAP_SIMULATION_H
#define JMG_CAP_SIMULATION_H

#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include "CapMaterialInterface.h"
#include "LaserBeam.h"
#include "TransducingLayer.h"
#include "CharacteristicMatrix.h"

#define DEFAULT_SAMPLING_RESOLUTION 1e-10

using std::complex;

struct CapPoint
{
  double time_delay; // s

  // (R - R0) / R0
  double reflectivity;

  CapPoint()
    : time_delay(0.0), reflectivity(0.0) {}

  CapPoint(double Time_Delay, double Reflectivity)
    : time_delay(Time_Delay), reflectivity(Reflectivity) {}
};

class CapSimulation
{
public:
  explicit CapSimulation(double depth_sampling_resolution = DEFAULT_SAMPLING_RESOLUTION);
  CapSimulation(CapMaterialInterface *material, double depth_sampling_resolution = DEFAULT_SAMPLING_RESOLUTION);
  CapSimulation(CapMaterialInterface *material, LaserBeam *laser, double depth_sampling_resolution = DEFAULT_SAMPLING_RESOLUTION);
  ~CapSimulation();

  std::vector <CapPoint> Run(double stop_time_delay, double time_delay_step);
  std::vector <CapPoint> Run(double start_time_delay, double stop_time_delay, double time_delay_step);

  void PrintParameters(std::ostream & out = std::cout, std::string tag = "") const;
  void set_material(CapMaterialInterface *material);

private:
  bool _material_needs_destroyed;
  CapMaterialInterface *_material;
  LaserBeam _laser;
  double _depth_sampling_resolution;

  void DestroyMaterialIfNecessary();
  double CalculateReflectivityForTimeDelay(double time_delay) const;
  double CalculateDifferentialReflectivity(double modulated_reflectivity, double baseline_reflectivity) const;
  double CalculateStrain(double td, double z) const;
  double CalculateUnstrainedReflectivity() const;
  std::vector <CharacteristicMatrix> BuildLayerMatricesList(double time_delay) const;
  complex <double> UnstrainedIndex(double depth) const;
  complex <double> IndexBeforeSpecimen() const;
  complex <double> IndexAfterSpecimen() const;
  complex <double> CalculateIndexWithStrain(double time_delay, double depth) const;
};

#endif
