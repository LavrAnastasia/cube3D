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

int is_direction_config(char *line, char a, char b)
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

