#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Supply -c and filename");
    exit(EXIT_FAILURE);
  }

  char *filename = argv[2];

  struct stat st;
  if (stat(filename, &st) != 0) {
    perror(filename);
    exit(1);
  }

  printf("%lld %s\n", (long long)st.st_size, filename);
}
