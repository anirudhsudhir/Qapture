#include <stdio.h>
#include <stdlib.h>

int argCheck(int argc, FILE *file) {
  if (argc != 2) {
    printf("Usage: ./recover IMAGE");
    return 1;
  }
  if (file == NULL) {
    printf("Unable to open the file");
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  FILE *rawdata = fopen(argv[1], "r");
  if (argCheck(argc, rawdata) == 1) {
    return 1;
  }
  // TODO: Add custom block size
}
