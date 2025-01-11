export module sampleapp:add;

export namespace sampleapp {
export namespace add {

template <typename T>
auto add(T a, T b) -> T {
  return a + b;
}

};
};
