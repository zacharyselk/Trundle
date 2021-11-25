#include <Trundle/Core/renderer.h>

namespace Trundle::Renderer {

Renderer::Renderer(RendererType type)
  : renderer(type) { }

void Renderer::setREndererType(RendererType type) {
    renderer = type;
}

RendererType Renderer::getRendererType() {
    return renderer;
}

void Renderer::waitAndRender() {
    // TODO
}

void Renderer::submitQuad(const glm::Mat4& transform) {
    drawIndexed(6, PrimitiveType::Triangle);
}

} // namespace Trundle::Renderer