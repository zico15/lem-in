#ifndef LEMIN_H
#define LEMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <ft_util.h>
#include <ft_string.h>

#define DEBUG_ROOM 0
#define DEBUG_LINK 1
#define DEBUG_COMMENT 0
#define DEBUG_COMMAND 0
#define DEBUG_LINK_ROOMS 0

typedef struct s_item t_item;
typedef struct s_room t_room;
typedef struct s_link t_link;
typedef struct s_comment t_comment;
typedef struct s_command t_command;
typedef struct s_data t_data;
typedef struct s_item t_item;

typedef enum e_lemin
{
    INVALID_TYPE,
    ROOM,
    LINK,
    COMMENT,
    COMMAND
} t_lemin;

typedef enum e_cmd
{
    INVALID_CMD,
    START,
    END
} t_cmd;

struct s_item
{
    t_lemin type;
};

struct s_room
{
    t_lemin type;
    char *name;
    int x;
    int y;
    size_t number_links;
    t_room **links;
    t_room *next;
};

struct s_link
{
    t_lemin type;
    char *to;
    char *from;
    t_link *next;
};

struct s_comment
{
    t_lemin type;
    char *comment;
};

struct s_command
{
    t_lemin type;
    t_cmd cmd;
};

struct s_data
{
    bool is_error;
    size_t size;
    t_item **items;
    t_item *item_begin[5];
    t_item *item_end[5];
    t_room *start;
    t_room *end;
    size_t number_ants;
};

bool is_comment(char *line);
bool is_link(char *line);
bool is_room(char *line);
bool is_command(char *line);
void *check_line(t_data *data, char *line, int count);

// items
t_room *new_room(t_data *data, char *line);
t_link *new_link(t_data *data, char *line);
t_comment *new_comment(t_data *data, char *line);
t_command *new_command(t_data *data, char *line);

bool link_rooms(t_data *data, t_link *link);
void algorithm(t_data *data);

#endif