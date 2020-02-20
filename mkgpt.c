#include <stdio.h>
#include <string.h>

#include "device.h"

void usage()
{
    printf("mkgpt [--force] [device]\n");
}

int main(int argc, char *argv[])
{
    int force = 0;
    char *devname = NULL;
    struct device dev;

    if (argc > 3)
    {
        printf("Too many arguments.\n");
        usage();
        return -1;
    }
    else if(argc == 1)
    {
        printf("Missing parameters.\n");
        usage();
        return -1;
    }
    else
    {
        for(int i = 1; i < argc; i++)
        {
            if(argv[i][0] == '-')
            {
                if(strcmp("--force", argv[i]) == 0)
                {
                    if(argc == 2)
                    {
                        printf("You must specify a device.\n");
                        usage();
                        return -1;
                    }
                    force = 1;
                }
                else
                {
                    printf("Unknown parameter %s\n", argv[i]);
                    usage();
                    return -1;
                }
            }
            else
            {
                devname = argv[i];
            }
        }
    }
    if(open_device(devname, &dev) < 0)
    {
        printf("Unable to open device.\n");
        return -1;
    }
    close_device(&dev);
    return 0;
}
