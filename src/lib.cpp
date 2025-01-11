export module sampleapp;

export import :basic_ops;
export import :stats;

import std;

export auto greet(std::string name) -> void {
    std::println("Hello, {}", name);
}
