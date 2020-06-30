template <typename T>
util::RandomGenerator<T>::RandomGenerator() :
  gen_{ std::random_device{ }() }
{ }
