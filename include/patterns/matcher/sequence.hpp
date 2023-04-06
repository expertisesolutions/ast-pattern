#ifndef PATTERNS_MATCHER_SEQUENCE_HPP
#define PATTERNS_MATCHER_SEQUENCE_HPP

#include <patterns/concept.hpp>
#include <patterns/matcher/concept.hpp>

namespace patterns { namespace matcher {

template <MatcherExpression L, MatcherExpression R>
struct sequence
{
  template <Node T, typename Context>
  bool match (T&& object, Context const& context) const
  {
    if (l.match(object, context))
    {
      if (r.match(next(object), context))
        return true;
    }
    return false;
  }

  L l;
  R r;
};

}

template <MatcherExpression L, MatcherExpression R>
constexpr bool is_matcher<matcher::sequence<L, R>> = true;
template <MatcherExpression L, MatcherExpression R>
constexpr bool is_matcher<matcher::sequence<L, R>&> = true;

}

#endif
