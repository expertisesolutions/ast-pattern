#ifndef PATTERNS_MATCHER_CHILDREN_MATCHER_TERMINAL_HPP
#define PATTERNS_MATCHER_CHILDREN_MATCHER_TERMINAL_HPP

#include <patterns/matcher/concept.hpp>

namespace patterns { namespace matcher {

template <typename M>
struct children_matcher
{
  template <AST_Node N, typename Context>
  bool match(N&& n, Context const& context) const
  {
    return false;
  }

  M children_matches;
};

struct children_matcher_terminal {
  template <typename M>
  children_matcher<M> operator[](M&& children_matches) const
  {
    return {std::forward<M>(children_matches)};
  }
};

}

template <typename T>
constexpr bool is_matcher<matcher::children_matcher<T>> = true;
template <typename T>
constexpr bool is_matcher<matcher::children_matcher<T>&> = true;

}

#endif
