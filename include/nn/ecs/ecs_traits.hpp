#pragma once

#include "nn/ecs/entity_manager.hpp"

namespace nn {
template<typename C, typename EntityManager>
struct entity_manager_has_component;

template<typename C, typename... Cs>
struct entity_manager_has_component<C, nn::entity_manager<Cs...>>
    : std::disjunction<std::is_same<C, Cs>...> {};
} // namespace nn