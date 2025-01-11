export module sampleapp:stats_one_var;

export namespace sampleapp {
export namespace stats {
export namespace one_var {

template <typename T>
auto average(std::vector<T> list) -> T {
  T sum = 0;
  for (auto v : list) {
    sum += v;
  }
  return sum / static_cast<T>(list.size());
}

};
};
};
