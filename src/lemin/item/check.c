#include <lemin.h>

bool is_comment(char *line)
{
    if (!line)
        return false;
    if (line[0] == '#' && line[1] != '#')
        return true;
    return false;
}

bool is_link(char *line)
{
    if (!line)
        return false;
    return string().contains(line, "-");
}

bool is_room(char *line)
{
    int spaces;
    bool is_space;

    if (!line || string().contains(line, "-") || string().contains(line, "#"))
        return false;
    spaces = 0;
    is_space = false;
    while (*line)
    {
        if (!is_space && string().is_space(*line))
        {
            is_space = true;
            spaces++;
        }
        else if (is_space && !string().is_space(*line))
            is_space = false;
        line++;
    }
    if (string().contains(line, "start"))
        printf("spaces: %d line: %s\n", spaces, line);
    return spaces >= 2;
}

bool is_command(char *line)
{
    if (!line)
        return false;
    return (string().equals_n(line, "##", 2));
}

void *check_line(t_data *data, char *line, int count)
{
    (void)data;
    (void)count;
    if (line && string().is_number(line))
        data->number_ants = string().atoi(line);
    else
        data->is_error = true;
    return NULL;
}