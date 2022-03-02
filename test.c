# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>



int main()
{

    manage_pipes((char *[]){"/bin/cat","/dev/random", "/usr/bin/head", "-c10",NULL});
}


// int main()
// {
//     int fds[2];

//     pipe(fds);
//     close(fds[0]);
//     write(fds[1], "hello world", 11);
//     printf("DOne\n");
// }