#ifndef PATTERNS_MATCHER_MATCHER_LIST_HPP
#define PATTERNS_MATCHER_MATCHER_LIST_HPP

#include <patterns/concept.hpp>
#include <patterns/matcher/concept.hpp>

#include <tuple>

namespace patterns { namespace matcher {

template <MatcherExpression... Ms>
struct matcher_list
{
  template <AST_Node T, typename Context>
  bool match (T&& object, Context const& context) const
  {
    return false;
  }

  std::tuple<Ms...> ms;
};

}

template <MatcherExpression...Ms>
constexpr bool is_matcher<matcher::matcher_list<Ms...>> = true;
template <MatcherExpression...Ms>
constexpr bool is_matcher<matcher::matcher_list<Ms...>&> = true;

}

#endif
