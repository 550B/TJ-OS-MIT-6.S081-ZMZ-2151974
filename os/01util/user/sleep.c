#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int
main(int argc, char *argv[])
{
if(argc == 1)
{
write(1, "Please pass an argument!\n", strlen("Please pass an argument!\n"));
exit(1);
}
else if(argc >= 2)
{
int sec = atoi(argv[1]);
sleep(sec);
}
exit(0);
}

