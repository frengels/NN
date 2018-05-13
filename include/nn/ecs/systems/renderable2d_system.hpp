#pragma once

#include "nn/ecs/system.hpp"
#include "nn/ecs/systems/transform2d_system.hpp"
#include "nn/render/2d/renderable2d.hpp"
#include "nn/render/2d/renderer2d.hpp"
#include "nn/render/2d/sprite.hpp"

namespace nn {
struct renderable2d_component {
  bool visible;
  nn::renderable2d renderable;

  template<typename... Args>
  renderable2d_component(bool visible, Args&&... args)
      : visible{visible}
      , renderable(std::forward<Args>(args)...) {
  }
};

struct sprite_component {
  bool visible;
  nn::sprite sprite;

  template<typename... Args>
  sprite_component(bool visible, Args&&... args)
      : visible{visible}
      , sprite(std::forward<Args>(args)...) {
  }

  friend void swap(sprite_component& lhs, sprite_component& rhs) {
    using std::swap;
    swap(lhs.visible, rhs.visible);
    swap(lhs.sprite, rhs.sprite);
  }
};

template<typename EntityManager>
auto make_renderable2d_system(const EntityManager& m,
                              nn::renderer2d& renderer) {
  return nn::make_iterating_constexpr_system<renderable2d_component,
                                             transform2d_component>(
      m, [&](auto& view, [[maybe_unused]] float) {
        auto t = view.template get<transform2d_component>();
        auto r = view.template get<renderable2d_component>();

        if (r->value.visible) {
          renderer.push(
              r->value.renderable, t->value.transform.transformation(),
              t->value.transform.z_layer, t->value.transform.z_offset);
        }
      });
}

template<typename EntityManager>
auto make_sprite_system(const EntityManager& m, nn::renderer2d& renderer) {
  return nn::make_iterating_constexpr_system<sprite_component,
                                             transform2d_component>(
      m, [&](auto& view, [[maybe_unused]] float) {
        auto t = view.template get<transform2d_component>();
        auto s = view.template get<sprite_component>();

        if (s->value.visible) {
          renderer.push(s->value.sprite, t->value.transform.transformation(),
                        t->value.transform.z_layer,
                        t->value.transform.z_offset);
        }
      });
}

template<class EntityManager>
class renderer_system {
public:
  using entity_manager_type = EntityManager;

private:
  nn::renderer2d m_renderer;

  decltype(nn::make_renderable2d_system(std::declval<entity_manager_type>(),
                                        m_renderer)) m_renderable_system;

  decltype(nn::make_sprite_system(std::declval<entity_manager_type>(),
                                  m_renderer)) m_sprite_system;

public:
  renderer_system(const entity_manager_type& m)
      : m_renderer{}
      , m_renderable_system(nn::make_renderable2d_system(m, m_renderer))
      , m_sprite_system(nn::make_sprite_system(m, m_renderer)) {
  }

  void operator()(entity_manager_type& manager, [[maybe_unused]] float dt) {
    m_renderable_system(manager, dt);
    m_sprite_system(manager, dt);

    m_renderer.flush();
  }
};

} // namespace nn