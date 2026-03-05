#include "parsing.h"

void init_config(t_config *config)
{
    config->no_path = NULL;
    config->so_path = NULL;
    config->we_path = NULL;
    config->ea_path = NULL;
    config->floor = (t_rgb){0,0,0};
    config->ceiling = (t_rgb){0,0,0};
}

char *skip_spaces(char *s)
{
    if(!s)
        return (NULL);
    while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\v' || *s == '\f')
    s++;
    return(s);
}
int is_right_char(char c)
{
    if(c == '0' || c == '1')
        return(1);
    if(c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    if(c == ' ')
        return (1);
    return (0);
}

int parse_before_map(char *line)
{
    int i;
    int is_map_char;

    if(!line || !*line)
        return(0);
    i = 0;
    is_map_char = 0;
    while(line[i] && line[i] != '\n')
    {
        if(!is_right_char(line[i]))
            return(0);
        if(line[i] == '0' || line[i] == '1' || line[i] == 'N' 
            || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
            is_map_char = 1;
        i++;
    }
    return(is_map_char);
}

int recognize_direction_config(char *line, char a, char b)
{
    if(!line)
        return (0);
    if(line[0] != a)
        return(0);
    if(line[1] != b)
        return (0);
    if(!ft_isspace((unsigned char)line[2]))
        return (0);
    return (1);
}

int parse_config_section(char *line, t_game *game)
{
    char *trim;

    trim = skip_spaces(line);
    if(!trim || *trim == '\0' || *trim == '\n')
        return(0);
    
    if(recognize_config(trim, 'N', '0'))
        return(parse_no(trim + 2, game));
}