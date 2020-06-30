#include <util/random.hpp>

#include <random>

float util::FloatGenerator::get(float min, float max)
{
  std::uniform_real_distribution<float> dist(min, max);
  return dist(gen_);
}
