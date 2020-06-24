template<typename I, typename R>
void ResourceHolder<I, R>::load(const I & id, const std::string & filename)
{
  auto resource = std::make_unique<R>();
  if (!resource->loadFromFile(filename)) {
    throw std::runtime_error{ "ResourceHolder::load : Failed to load resource " + filename };
  }

  resources_.insert(std::make_pair(id, std::move(resource)));
}

template<typename I, typename R>
R & ResourceHolder<I, R>::get(const I & id)
{
  auto found = resources_.find(id);
  if (found == resources_.end()) {
    throw std::invalid_argument{ "ResourceHolder::get : Failed to find resource" };
  }

  return *found->second;
}

template<typename I, typename R>
const R & ResourceHolder<I, R>::get(const I & id) const
{
  auto found = resources_.find(id);
  if (found == resources_.end()) {
    throw std::invalid_argument{ "ResourceHolder::get : Failed to find resource" };
  }

  return *found->second;
}

template<typename I, typename R>
R & ResourceHolder<I, R>::getOrLoad(const I & id, const std::string & filename)
{
  auto found = resources_.find(id);
  if (found != resources_.end()) {
    return *found->second;
  }

  auto resource = std::make_unique<R>();
  if (!resource->loadFromFile(filename)) {
    throw std::runtime_error{ "ResourceHolder::getOrLoad : Failed to load resource " + filename };
  }

  resources_.insert(std::make_pair(id, std::move(resource)));
}
