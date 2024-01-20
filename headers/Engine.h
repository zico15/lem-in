#ifndef ENGINE_H
#define ENGINE_H

#include "SDL2D.h"
#include <Vector.h>
#include "ft_util.h"
#include "Objects.h"
#include <limits.h>
#include <lemin.h>

typedef struct s_engine t_engine;

struct s_engine
{
    t_sdl *sdl;
    t_scene *scene;
    float delta_time;
    int width;
    int height;
    void (*init)(int argc, char **argv, int width, int height);
    void (*run)();
    void (*update)();
    void (*render)(SDL_Renderer *renderer);
    void (*destroy)(char *msg);
    t_scene *(*add)(t_scene *scene);
    void *scenes;
};

t_engine *engine();

#endif