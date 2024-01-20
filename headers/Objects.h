#ifndef OBJECTS_H
#define OBJECTS_H

#include "Engine.h"

typedef struct s_object t_object;
typedef struct s_scene t_scene;
typedef struct s_plane t_plane;
typedef struct s_map t_map;
typedef struct s_data t_data;
typedef struct s_ant t_ant;

#define res 1
#define SW 160 * res
#define SH 120 * res
#define SW2 (SW / 2)
#define SH2 (SH / 2)
#define pixelScale 4 / res
#define GLSW (SW * pixelScale)
#define GLSH (SH * pixelScale)

typedef struct s_math
{
    float cos[360];
    float sin[360];
} t_math;

typedef enum e_type
{
    NONE,
    ANT,
    MAP,
} t_type;

struct s_object
{
    t_type type;
    SDL_Rect rect;
    t_vector2 direction;
    t_image *image;
    void (*move)(t_object *this, float x, float y);
    void (*render)(t_object *this, SDL_Renderer *renderer);
    void (*destroy)(t_object *this);
    void (*update)(t_object *this, t_sdl *sdl);
    void (*key)(t_object *this, bool *key, SDL_Event *event);
    void (*mouse)(t_object *this, t_sdl *sdl, SDL_Event *event);
};

struct s_scene
{
    t_type type;
    SDL_Rect rect;
    t_vector2 direction;
    t_image *image;
    void (*move)(t_scene *this, float x, float y);
    void (*render)(t_scene *this, SDL_Renderer *renderer);
    void (*destroy)(t_scene *this);
    void (*update)(t_scene *this, t_sdl *sdl);
    void (*key)(t_scene *this, bool *key, SDL_Event *event);
    void (*mouse)(t_scene *this, t_sdl *sdl, SDL_Event *event);
    t_object *(*add)(t_scene *this, void *object);
    void *objects;
    void *event_render;
    void *event_update;
    void *event_key;
    t_data *data;
};

struct s_map
{
    t_type type;
    SDL_Rect rect;
    t_vector2 direction;
    t_image *background;
    void (*move)(t_map *this, float x, float y);
    void (*render)(t_map *this, SDL_Renderer *renderer);
    void (*destroy)(t_map *this);
    void (*update)(t_map *this, t_sdl *sdl);
    void (*key)(t_map *this, bool *key, SDL_Event *event);
    void (*mouse)(t_map *this, t_sdl *sdl, SDL_Event *event);
    t_data *data;
};

struct s_ant
{
    t_type type;
    SDL_Rect rect;
    t_vector2 direction;
    t_image *image;
    void (*move)(t_ant *this, float x, float y);
    void (*render)(t_ant *this, SDL_Renderer *renderer);
    void (*destroy)(t_ant *this);
    void (*update)(t_ant *this, t_sdl *sdl);
    void (*key)(t_ant *this, bool *key, SDL_Event *event);
    void (*mouse)(t_ant *this, t_sdl *sdl, SDL_Event *event);
    int id;
};

t_object *new_object(size_t size);
t_scene *new_scene(t_data *data);
t_map *new_map(t_data *data);
t_ant *new_ant(int id, int x, int y);

#endif