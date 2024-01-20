#include <lemin.h>

void check_path(t_room *room)
{
    size_t i;
    t_room *tmp;

    i = 0;
    while (i < room->number_links)
    {
        tmp = room->links[i];
        if (tmp)
            printf("room: %s x: %i, y: %i\n", tmp->name, tmp->x, tmp->y);
        i++;
    }
}

void algorithm(t_data *data)
{
    printf("start: %s x: %i, y: %i links: %zu\n", data->start->name, data->start->x, data->start->y, data->start->number_links);
    check_path(data->start);
}