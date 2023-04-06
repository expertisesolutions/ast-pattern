#ifndef PATTERNS_MATCHER_CASE_HPP
#define PATTERNS_MATCHER_CASE_HPP

#include <patterns/matcher/concept.hpp>

#include <utility>

namespace patterns { namespace matcher {

template <MatcherExpression M, typename H = void_type>
struct case_type
{
  template <Node N, typename Context>
  bool match(N&& node, Context const& context) const
  {
    if (m.match(node, context))
    {
      //h();
      return true;
    }
    return false;
  }
  
  M m;
  H h;
};

template <MatcherExpression M>
struct case_type<M, void_type>
{
  template <typename H2>
  case_type<M, H2> operator()(H2&& h2) const
  {
    return {std::move(m), std::forward<H2>(h2)};
  }

  template <Node N, typename Context>
  bool match(N&& node, Context const& context) const
  {
    return m.match(node, context);
  }

  M m;
  void_type h;
};
  
struct case_terminal
{
  template <MatcherExpression M>
  case_type<M, void_type> operator[](M && m) const
  {
    return {std::forward<M>(m)};
  }
};

case_terminal const& case_ = {};

} }

#endif
