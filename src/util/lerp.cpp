#include <util/lerp.hpp>

float util::lerp(float a, float b, float t) noexcept
{
  return a + t * (b - a);
}

double util::lerp(double a, double b, double t) noexcept
{
  return a + t * (b - a);
}
