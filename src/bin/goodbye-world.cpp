import std;
import sampleapp;

int main() {
  std::println("Goodbye, World!");
  std::println("average() of 1, 2, 3 is {}", sampleapp::stats::one_var::average(std::vector<int>{1, 2, 3}));
}
