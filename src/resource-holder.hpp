#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

template <typename I, typename R>
class ResourceHolder
{
public:
  void load(const I & id, const std::string & filename);
  R & get(const I & id);
  const R & get(const I & id) const;
  R & getOrLoad(const I & id, const std::string & filename);
private:
  std::map<I, std::unique_ptr<R>> resources_;
};

#include "resource-holder.inl"

#endif 
