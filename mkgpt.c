#include <stdio.h>

void usage()
{
    printf("mkgpt [--force] [device]\n");
}

int main(int argc, char *argv[])
{
    int force = 0;
    char *devname = NULL;

    if (argc > 3)
    {
        printf("Too many arguments.\n");
        usage();
        return -1;
    }
    return 0;
}
