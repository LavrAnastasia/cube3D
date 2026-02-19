#include "parsing.h"
#include "get_next_line.h"

int read_cube(const char *path)
{
    int fd;
    char *line;
    int line_num;
    
    line_num = 0;
    fd = open(path, O_RDONLY);
    if(fd < 0)
        return(perror("open"), 1);
    line = get_next_line(fd);
    while(line)
    {
        line_num++;
        printf("line %d: %s", line_num, line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return(0);
}