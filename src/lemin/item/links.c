#include <lemin.h>

static t_room *find_room(t_data *data, char *name)
{
    t_room *room;

    room = (t_room *)data->item_begin[ROOM];
    while (room)
    {
        if (string().equals(room->name, name))
            return (room);
        room = room->next;
    }
    return (NULL);
}

static void ft_realloc_link_rooms(t_room *room, t_room *link)
{
    t_room **links;
    size_t i;

    links = ft_calloc(sizeof(t_room *) * room->number_links + 2);
    if (links)
    {
        i = -1;
        while (++i < room->number_links)
            links[i] = room->links[i];
        links[i] = link;
        free(room->links);
        room->links = links;
        if (DEBUG_LINK_ROOMS)
            printf("link_rooms: %s | %zu | %s\n", room->name, room->number_links, room->links[room->number_links]->name);
        room->number_links++;
    }
}

bool link_rooms(t_data *data, t_link *link)
{
    t_room *to;
    t_room *from;

    if (!link || data->is_error)
        return (true);
    to = find_room(data, link->to);
    from = find_room(data, link->from);
    if (!to || !from)
        return (false);
    ft_realloc_link_rooms(to, from);
    return link_rooms(data, link->next);
}