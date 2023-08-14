#ifndef PATTERNS_ARCHETYPE_NODE_HPP
#define PATTERNS_ARCHETYPE_NODE_HPP

#include <patterns/concept.hpp>

namespace patterns { namespace archetype {

struct tree_node
{
};

inline tree_node next(tree_node x) { return x; }
template <typename T>
bool is_type(tree_node x, std::type_identity<T>) { return false; }

}
  
template <>
constexpr bool is_node<archetype::tree_node> = true;
template <>
constexpr bool is_node<archetype::tree_node&> = true;

static_assert( Node<archetype::tree_node>);
static_assert( Node<archetype::tree_node&>);

}

#endif
