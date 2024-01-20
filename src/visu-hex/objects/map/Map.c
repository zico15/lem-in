#include "Engine.h"

static void __render_link(t_room *to, SDL_Renderer *renderer)
{
    size_t i;
    t_room *from;

    i = 0;
    while (i < to->number_links)
    {
        from = to->links[i];
        if (!from)
            continue;
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(renderer, to->x, to->y, from->x, from->y);
        i++;
    }
}

// static void __render_text(char *text, int x, int y, int size, SDL_Renderer *renderer)
// {
//     // SDL_Color color = {0, 0, 0, 255};
//     // // font = TTF_OpenFont("resources/fonts/arial.ttf", 24);
//     // SDL_Surface *surface = TTF_RenderText_Solid(engine()->font, text, color);
//     // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
//     // SDL_Rect rect = {x, y, size, size};
//     // SDL_RenderCopy(renderer, texture, NULL, &rect);
//     // SDL_FreeSurface(surface);
//     // SDL_DestroyTexture(texture);
// }

static void __render(t_map *this, SDL_Renderer *renderer)
{
    t_room *room;

    SDL_RenderCopy(renderer, this->background->textura, NULL, NULL);
    room = this->data->item_begin[ROOM];
    while (room)
    {
        __render_link(room, renderer);
        if (room == this->data->start)
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        else if (room == this->data->end)
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
        else
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        this->rect.x = room->x;
        this->rect.y = room->y;
        SDL_RenderDrawRect(renderer, &this->rect);
        room = room->next;
    }
}

static void __key(t_map *this, bool *key, SDL_Event *event)
{
}

t_map *new_map(t_data *data)
{
    t_map *map;

    map = (t_map *)new_object(sizeof(t_map));
    map->type = MAP;
    map->rect.w = 32;
    map->rect.h = 32;
    map->render = __render;
    map->key = __key;
    map->data = data;
    map->background = new_image_file("resources/textures/background.png");
    return (map);
}