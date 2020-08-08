#pragma once

#include <Trundle/trundle.hpp>

// Debug info
#define LOC " (" << __FILE__ << ": " << __LINE__ << ")\n"
#define CHECK(condition) { if(!(condition)){ std::cerr << "ASSERT FAILED: " << #condition << LOC; exit(1) } }
#define DIE(msg) { std::cerr << "Error: " << #msg << LOC; exit(1); }


namespace common {

// Helper templates for combining a list of lambdas into an anonymous
// struct for use with std::visit() on a std::variant<> sum type.
// E.g.: std::visit(visitors{
//         [&](const firstType &x) { ... },
//         [&](const secondType &x) { ... },
//         ...
//         [&](const auto &catchAll) { ... }}, variantObject);
template <typename... LAMBDAS> struct visitors : LAMBDAS... {
  using LAMBDAS::operator()...;
};

template <typename... LAMBDAS> visitors(LAMBDAS... x) -> visitors<LAMBDAS...>;


// Copy a value from one variant type to another.  The types allowed in the
// source variant must all be allowed in the destination variant type.
template <typename TOV, typename FROMV> TOV CopyVariant(const FROMV &u) {
  return std::visit([](const auto &x) -> TOV { return {x}; }, u);
}

}; // namespace common
