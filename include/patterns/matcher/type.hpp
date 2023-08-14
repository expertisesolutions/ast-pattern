#ifndef PATTERNS_MATCHER_TYPE_HPP
#define PATTERNS_MATCHER_TYPE_HPP

#include <patterns/matcher/concept.hpp>
#include <patterns/matcher/children_matcher_terminal.hpp>
#include <patterns/concept.hpp>

#include <type_traits>

namespace patterns { namespace matcher {

template <typename T, typename A>
struct actioned_type_matcher : children_matcher_terminal {
  A action;

  template <Node U, typename Context>
  bool match(U&& u, Context const& context) const
  {
    if (is_type(u, std::type_identity<T>{}))
    {
      action(u, context);
      return true;
    }
    else
      return false;
  }
};

template <typename T>
struct type_matcher : children_matcher_terminal {
  template <Node U, typename Context>
  bool match(U&& u, Context const& context) const
  {
    return is_type(u, std::type_identity<T>{});
  }

  template <typename A>
  actioned_type_matcher<T, A> operator()(A&& a) const
  {
    return actioned_type_matcher<T, A>{{}, std::forward<A>(a)};
  }
};

template <typename T>
type_matcher<T> type;

}

template <typename T>
constexpr bool is_matcher<matcher::type_matcher<T>> = true;
template <typename T>
constexpr bool is_matcher<matcher::type_matcher<T>&> = true;

template <typename T, typename A>
constexpr bool is_matcher<matcher::actioned_type_matcher<T, A>> = true;
template <typename T, typename A>
constexpr bool is_matcher<matcher::actioned_type_matcher<T, A>&> = true;

}

#endif
