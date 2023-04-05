#ifndef PATTERNS_MATCHER_OPERATORS_HPP
#define PATTERNS_MATCHER_OPERATORS_HPP

#include <patterns/matcher/sequence.hpp>
#include <patterns/matcher/matcher_list.hpp>
#include <patterns/matcher/children_matcher_terminal.hpp>
#include <patterns/matcher/case.hpp>
#include <patterns/matcher/type.hpp>
#include <utility>

namespace patterns { namespace matcher {

template <MatcherExpression L, MatcherExpression R>
matcher::matcher_list<L, R>
operator,(L&& l, R&& r)
{
  return {{std::forward<L>(l), std::forward<R>(r)}};
}

template <MatcherExpression L, MatcherExpression R>
matcher::sequence<L, R>
operator>>(L&& l, R&& r)
{
  return {std::forward<L>(l), std::forward<R>(r)};
}

} }

#endif
