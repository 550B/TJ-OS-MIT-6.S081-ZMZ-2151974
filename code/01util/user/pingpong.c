#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int
main(int argc, char* argv[])
{
char ball = 'A'; //ping-pong ball
int fd_c2p[2]; //child->parent
int fd_p2c[2]; //parent->child
pipe(fd_c2p); //pipe for child->parent
pipe(fd_p2c); //pipe for parent->child
int pid = fork(); //process id
int status = 0; //exit status
if (pid < 0)
{
fprintf(2, "There is an error when fork()!\n");
close(fd_c2p[0]);
close(fd_c2p[1]);
close(fd_p2c[0]);
close(fd_p2c[1]);
exit(1);
}
else if (pid == 0) //child process
{
close(fd_p2c[1]);
close(fd_c2p[0]);
if (read(fd_p2c[0], &ball, sizeof(char)) != sizeof(char))
{
fprintf(2, "There is an error when child read()!\n");
status = 1;
}
else
{
fprintf(1, "%d: received ping\n", getpid());
}
if (write(fd_c2p[1], &ball, sizeof(char)) != sizeof(char))
{
fprintf(2, "There is an error when child write()!\n");
status = 1;
}
close(fd_p2c[0]);
close(fd_c2p[1]);
exit(status);
}
else //parent process
{
close(fd_p2c[0]);
close(fd_c2p[1]);
if (write(fd_p2c[1], &ball, sizeof(char)) != sizeof(char))
{
fprintf(2, "There is an error when parent write()!\n");
status = 1;
}
if (read(fd_c2p[0], &ball, sizeof(char)) != sizeof(char))
{
fprintf(2, "There is an error when parent read()!\n");
status = 1;
}
else
{
fprintf(1, "%d: received pong\n", getpid());
}
close(fd_p2c[1]);
close(fd_c2p[0]);
exit(status);
}
}
