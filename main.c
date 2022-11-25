#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{   
    if (argc > 3) 
    {
        char **paths = argv;

        for (size_t i = 1; i < argc; i++)
            printf("%s\n", paths[i]);
        
        return 0;
    }
}


