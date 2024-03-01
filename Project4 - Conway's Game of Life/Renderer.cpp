#include "Renderer.h"

Renderer* Renderer::GetInstance(SDL_Window* window, int index, int flags)
{
    if (renderer_ == nullptr) {
        renderer_ = new Renderer(window, index, flags);
    }
    return renderer_;
}

Renderer* Renderer::GetInstance()
{
    return renderer_;
}

SDL_Renderer* Renderer::GetRenderer()
{
    return sdl_renderer;
}

Renderer::Renderer(SDL_Window* window, int index, int flags)
{
    sdl_renderer = SDL_CreateRenderer(window, index, flags);
}

Renderer* Renderer::renderer_ = nullptr;