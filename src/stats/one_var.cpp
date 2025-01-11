export module sampleapp:stats_one_var;

import std;

export namespace sampleapp {
namespace stats {
namespace one_var {

auto average(std::vector<int> list) -> int {
  int sum = 0;
  for (auto v : list) {
    sum += v;
  }
  return sum / list.size();
};

};
};
};
