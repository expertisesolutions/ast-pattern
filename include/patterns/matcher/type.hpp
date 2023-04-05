#ifndef PATTERNS_MATCHER_TYPE_HPP
#define PATTERNS_MATCHER_TYPE_HPP

#include <patterns/matcher/concept.hpp>
#include <patterns/matcher/children_matcher_terminal.hpp>
#include <patterns/concept.hpp>

#include <type_traits>

namespace patterns { namespace matcher {

template <typename T>
struct type_matcher : children_matcher_terminal {
  template <AST_Node U, typename Context>
  bool match(U&& u, Context const& context) const
  {
    return is_type(u, std::type_identity<U>{});
  }
};

template <typename T>
type_matcher<T> type;

}

template <typename T>
constexpr bool is_matcher<matcher::type_matcher<T>> = true;
template <typename T>
constexpr bool is_matcher<matcher::type_matcher<T>&> = true;

}

#endif
