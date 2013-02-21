#ifndef JMG_DAMAGE_MODEL_FACTORY_H
#define JMG_DAMAGE_MODEL_FACTORY_H

#include "DamageModelInterface.h"

class DamageModelFactory
{
 private:
  static std::string to_upper(const std::string & s);
  
 public:
  static DamageModelInterface * GetModelFromString(const std::string & name);
  static std::vector<DamageModelInterface *> GetAllModels();
  static DamageModelInterface * ParseCommandLine(const std::string & model_string);
};

#endif
