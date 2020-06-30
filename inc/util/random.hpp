#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

namespace util
{

  template <typename T>
  class RandomGenerator
  {
  public:
    RandomGenerator();
    virtual T get(T min, T max) = 0;
  protected:
    std::mt19937 gen_;
  };

  class FloatGenerator : public RandomGenerator<float>
  {
  public:
    float get(float min, float max) override;
  };

}

#include "random.inl"

#endif
