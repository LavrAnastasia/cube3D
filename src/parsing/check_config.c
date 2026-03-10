#include "parsing.h"
#include "map_utils.h"


bool is_next_line_map(char *line)
{
    size_t i;

    if(!line || !*line)
        return(false);
    i = 0;
    while(line[i] && line[i] != '\n')
    {
        if(!is_valid_char(line[i]) && (line[i] != SKIP_SIGN))
            return(false);
        i++;
    }
    return (true);
}

char *map_key(t_direction_key key)
{
    if (key == NO)
        return "NO";
    if (key == SO)
        return "SO";
    if (key == WE)
        return "WE";
    return "EA";  
}

bool is_direction_key(char *line, t_direction_key key)
{
    const char *direction_key = map_key(key);

    if(line[0] != direction_key[0])
        return(false);
    if(line[1] != direction_key[1])
        return (false);
    if(!ft_isspace((unsigned char)line[2]))
        return (false);
    return (true);
}
int is_config(char *line, char a)
{
    if(!line)
        return(0);
    if(line[0] != a)
        return(0);
    if(!ft_isspace((unsigned char)line[1]))
        return(0);
    return(1);    
}

