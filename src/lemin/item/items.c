#include <lemin.h>

static void set_start_end(t_data *data, t_cmd cmd)
{
    t_room *room;

    if (data->item_end[0] && data->item_end[0]->type == ROOM)
    {
        room = (t_room *)data->item_end[0];
        if (cmd == START)
        {
            if (data->start)
                data->is_error = true;
            data->start = room;
        }
        else if (cmd == END)
        {
            if (data->end)
                data->is_error = true;
            data->end = room;
        }
        else
            data->is_error = true;
    }
}

t_room *new_room(t_data *data, char *line)
{
    t_room *room;
    char **strs;

    (void)data;
    strs = string().split(line, " ");
    if (string().size_list(strs) != 3 || !string().is_number(strs[1]) || !string().is_number(strs[2]))
        return (free_list((void *)strs));
    room = ft_calloc(sizeof(t_room));
    if (room)
    {
        room->type = ROOM;
        room->name = string().copy(strs[0]);
        room->x = string().atoi(strs[1]);
        room->y = string().atoi(strs[2]);
        if (data->item_begin[ROOM] == NULL)
            data->item_begin[ROOM] = (t_item *)room;
        else
            ((t_room *)data->item_end[ROOM])->next = room;
        data->item_end[ROOM] = (t_item *)room;
        if (DEBUG_ROOM)
            printf("room: %s %d %d\n", room->name, room->x, room->y);
    }
    free_list((void *)strs);
    return (room);
}

t_link *new_link(t_data *data, char *line)
{
    t_link *link;
    char **strs;

    (void)data;
    strs = string().split(line, "-");
    if (string().size_list(strs) != 2)
        return (free_list((void *)strs));
    link = ft_calloc(sizeof(t_link));
    if (link)
    {
        link->type = LINK;
        link->to = string().copy(strs[0]);
        link->from = string().copy(strs[1]);
        if (data->item_begin[LINK] == NULL)
            data->item_begin[LINK] = (t_item *)link;
        else
            ((t_link *)data->item_end[LINK])->next = link;
        data->item_end[LINK] = (t_item *)link;
        if (DEBUG_LINK)
            printf("link: %s %s\n", link->to, link->from);
    }
    free_list((void *)strs);
    return (link);
}

t_comment *new_comment(t_data *data, char *line)
{
    t_comment *comment;

    (void)data;
    comment = ft_calloc(sizeof(t_comment));
    if (comment)
    {
        comment->type = COMMENT;
        comment->comment = string().copy(line);
        if (DEBUG_COMMENT)
            printf("comment: %s\n", comment->comment);
    }
    return (comment);
}

t_command *new_command(t_data *data, char *line)
{
    t_command *command;

    (void)data;
    command = ft_calloc(sizeof(t_command));
    if (command)
    {
        command->type = COMMAND;
        if (string().contains(line, "##start"))
            command->cmd = START;
        else if (string().contains(line, "##end"))
            command->cmd = END;
        set_start_end(data, command->cmd);
        if (DEBUG_COMMAND)
            printf("command: %d\n", command->cmd);
    }
    return (command);
}