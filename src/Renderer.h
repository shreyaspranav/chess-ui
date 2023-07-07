#pragma once
#include "glm/glm.hpp"
#include <string>

class Renderer
{
public:
    static void Init();

    static void Begin(uint32_t window_width, uint32_t window_height);
    static void End();

    static void RenderFrame();

    static void PushTexture(const std::string& textureFilePath, bool flipVertically = true);
    static void DrawQuad(const glm::vec3& pos, float rotation, const glm::vec2& scale, const glm::vec4& color);
    static void DrawTexturedQuad(const glm::vec3& pos, float rotation, const glm::vec2& scale, const glm::vec4& color, uint8_t id, glm::vec2 tex_coords[4] = nullptr);
};