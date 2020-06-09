#include <stdlib.h>
#include <unistd.h>

main(int argc, char *argv[ ])
{
   if (unlink(argv[1]) == -1) {
      perror(argv[1]);
      exit(1);
   }
   exit(0);
 }
