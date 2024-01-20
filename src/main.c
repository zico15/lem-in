#include <Engine.h>

void load_data(t_data *data, int count)
{
    char *line;
    char *tmp;

    line = get_next_line(0);
    if (line && ++data->size)
        load_data(data, count + 1);
    else if (count > 0)
        data->items = ft_calloc(sizeof(t_item *) * count + 1);
    if (line && data->items)
    {
        tmp = string().trim(line);
        if (is_room(tmp))
            data->items[count] = (t_item *)new_room(data, tmp);
        else if (is_link(tmp))
            data->items[count] = (t_item *)new_link(data, tmp);
        else if (is_comment(tmp))
            data->items[count] = (t_item *)new_comment(data, tmp);
        else if (is_command(tmp))
            data->items[count] = (t_item *)new_command(data, tmp);
        if (data->items[count] == NULL)
            data->items[count] = check_line(data, tmp, count);
        data->item_end[0] = data->items[count];
        free(tmp);
    }
    free(line);
}

void created_ant(t_data *data, t_scene *scene)
{
    size_t i;

    i = 0;
    while (i < data->number_ants)
    {
        scene->add(scene, new_ant(i, data->start->x, data->start->y));
        i++;
    }
}

int main(int argc, char *argv[])
{
    static t_data data;

    load_data(&data, 0);
    if (link_rooms(&data, (t_link *)data.item_begin[LINK]) == false)
        data.is_error = true;
    printf("start: %s | %zu | %i\n", data.start->name, data.start->number_links, data.is_error);
    if (data.is_error || data.number_ants < 1 || data.start == NULL || data.end == NULL ||
        data.start->number_links == 0)
    {
        printf("ERROR\n");
        free_list((void *)data.items);
        return (0);
    }
    algorithm(&data);
    engine()->init(argc, argv, 800, 600);

    t_scene *scene = new_scene(&data);

    scene->add(scene, new_map(&data));
    created_ant(&data, scene);
    engine()->add(scene);
    engine()->run();
    engine()->destroy(NULL);
    return (0);
}