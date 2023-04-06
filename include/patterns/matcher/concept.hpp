#ifndef PATTERNS_MATCHER_CONCEPT_HPP
#define PATTERNS_MATCHER_CONCEPT_HPP

#include <patterns/concept.hpp>
#include <concepts>

namespace patterns {

struct void_type {};
  
template <typename M>
constexpr bool is_matcher = false;

template <typename T>
concept MatcherExpression = requires(T a, node_archetype b)
{
  requires Node<node_archetype>;
  { a.match(b, 0) } -> std::convertible_to<bool>;
} && is_matcher<T>;

}

#endif
