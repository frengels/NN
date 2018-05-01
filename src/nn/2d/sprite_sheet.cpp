#include "nn/2d/sprite_sheet.hpp"

namespace nn {
sprite_sheet::sprite_sheet(
    const std::shared_ptr<texture>& tex,
    boost::container::flat_map<std::string, sprite_description>&& descriptions)
    : m_texture(tex)
    , m_sprites(descriptions) {
}
} // namespace nn