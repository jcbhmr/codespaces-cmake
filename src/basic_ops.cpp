export module sampleapp:basic_ops;

export namespace sampleapp {
export namespace basic_ops {

template <typename T>
auto add(T a, T b) -> T {
  return a + b;
}

template <typename T>
auto sub(T a, T b) -> T {
  return a - b;
}

};
};
