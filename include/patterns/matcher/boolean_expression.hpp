#ifndef PATTERNS_MATCHER_BOOLEAN_EXPRESSION_HPP
#define PATTERNS_MATCHER_BOOLEAN_EXPRESSION_HPP

#include <patterns/matcher/concept.hpp>
#include <patterns/matcher/children_matcher_terminal.hpp>
#include <patterns/concept.hpp>
#include <patterns/archetype/context.hpp>

#include <type_traits>

namespace patterns { namespace matcher {

namespace detail {

struct and_ {
  template <typename Context>
  static bool match(bool l, bool r, Context const&) {
    return l && r;
  }
};

struct or_ {
  template <typename Context>
  static bool match(bool l, bool r, Context const&) {
    return l || r;
  }
};

}

template <typename L, typename R, typename Op>
struct boolean_expression_matcher : children_matcher_terminal {
  L l;
  R r;

  template <Node U, typename Context = archetype::empty_context>
  bool match(U&& u, Context const& context = archetype::empty_context{}) const
  {
    return Op::match(l.match(u, context), r.match(u, context), context);
  }
};

template <typename L, typename R> requires MatcherExpression<L>
auto operator&&(L&& l, R&& r) {
  return boolean_expression_matcher<L, R, detail::and_>{{}, l, r};
}

}

template <typename L, typename R, typename Op>
constexpr bool is_matcher<matcher::boolean_expression_matcher<L, R, Op>> = true;
template <typename L, typename R, typename Op>
constexpr bool is_matcher<matcher::boolean_expression_matcher<L, R, Op>&> = true;

}

#endif
