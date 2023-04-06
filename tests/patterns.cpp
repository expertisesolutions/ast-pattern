#define BOOST_TEST_MODULE patterns
#include <boost/test/included/unit_test.hpp>

#include <patterns/matcher/operators.hpp>

#include <iostream>

struct base {};

struct type1 : base {};
struct type2 : base {};
struct type3 : base {};
struct type4 : base {};

type2 next (type1) { return {}; }
type4 next (type2) { return {}; }
template <typename T>
bool is_type (T t, std::type_identity<typename std::remove_reference_t<T>>) { return true; }
template <typename T, typename U>
bool is_type (T t, std::type_identity<U>) { return false; }

struct this_tree_tag {};

template <typename T>
constexpr bool patterns::is_node<T, typename std::enable_if_t<std::is_base_of_v< ::base, typename std::remove_reference_t<T>>>> = true;

namespace pt = patterns;

BOOST_AUTO_TEST_SUITE(test_pattern_suite)

BOOST_AUTO_TEST_CASE( test_pattern1 )
{
  bool action_called = false;
  
  // static_assert(pt::is_pattern_v<decltype(pt::a<type1>)>, "");
  // static_assert(pt::is_pattern_v<decltype(pt::a<type2>)>, "");
  using pt::matcher::type;
  using pt::matcher::case_;
  static_assert(pt::Node<pt::node_archetype>);
  static_assert(pt::Node<type1>);
  type<type1>.match(pt::node_archetype{}, 0);
  type<type2>.match(pt::node_archetype{}, 0);
  (type<type1> >> type<type2>).match(pt::node_archetype{}, 0);
  (type<type1> >> type<type2>, type<type4>).match(pt::node_archetype{}, 0);
  (type<type1>[type<type2>, type<type4>]).match(pt::node_archetype{}, 0);
  (type<type1>([&action_called] (auto&&, auto&&) {std::cout << "this was called" << std::endl; action_called = true;})
   >> type<type2>[type<type2>, type<type4>]).match(pt::node_archetype{}, 0);
  auto x =
    case_[type<type1> >> type<type2>[type<type3> >> type<type1>, type<type4>]]
    (
     [] (auto&& t1, auto&& t2)
     {
       std::cout << "lambda called" << std::endl;
     }
    )
    ;
  type1 t;
  x.match(t, 0);

  BOOST_TEST(action_called == true);
}

BOOST_AUTO_TEST_SUITE_END()

