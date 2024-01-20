#include "Engine.h"

static void __render(t_ant *this, SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->image->textura,
                   NULL, &this->rect);
}

static void __key(t_ant *this, bool *key, SDL_Event *event)
{
}

static void __update(t_ant *this, t_sdl *sdl)
{
}

t_ant *new_ant(int id, int x, int y)
{
    t_ant *ant;

    ant = (t_ant *)new_object(sizeof(t_ant));
    ant->type = ANT;
    ant->rect.x = x;
    ant->rect.y = y;
    ant->rect.w = 32;
    ant->rect.h = 32;
    ant->render = __render;
    ant->key = __key;
    ant->update = __update;
    ant->id = id;
    ant->image = new_image_file("resources/textures/ant.png");
    return (ant);
}