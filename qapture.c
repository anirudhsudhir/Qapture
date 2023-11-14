#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int argCheck(int argc, FILE *file) {
  if (argc != 2) {
    // TODO: Change ./recover to ./quapture
    printf("Usage: ./recover IMAGE\n");
    return 1;
  }
  if (file == NULL) {
    printf("Unable to open the file\n");
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  FILE *rawdata = fopen(argv[1], "r");
  if (argCheck(argc, rawdata) == 1) {
    return 1;
  }

  const int blocksize = 512;
  BYTE buffer[blocksize];

  char *fileout_name = malloc(4);
  if (fileout_name == NULL) {
    printf("Error allocating memory");
    return 1;
  }
  int fileout_count = 0;
  FILE *jpeg = NULL;

  // TODO: Add custom block size
  while (fread(buffer, 1, blocksize, rawdata) == blocksize) {
    if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 &&
        buffer[3] >= 224 && buffer[3] <= 240) {
      sprintf(fileout_name, "%.3d.jpg", fileout_count++);
      if (jpeg != NULL) {
        fprintf(jpeg, "\n");
        fclose(jpeg);
      }
      jpeg = fopen(fileout_name, "wb");
      if (jpeg == NULL) {
        printf("Unable to create JPEG files");
        return 1;
      }
      fwrite(buffer, 1, 512, jpeg);
    } else {
      if (jpeg != NULL) {
        fwrite(buffer, 1, 512, jpeg);
      }
    }
  }
  fclose(rawdata);
  free(fileout_name);
  return 0;
}
