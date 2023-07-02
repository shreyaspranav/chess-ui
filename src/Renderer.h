#pragma once
#include "glm/glm.hpp"

class Renderer
{
public:
    static void Init();

    static void Begin(uint32_t window_width, uint32_t window_height);
    static void End();

    static void RenderFrame();

    static void DrawQuad(const glm::vec3& pos, float rotation, const glm::vec2& scale, const glm::vec4& color);
};