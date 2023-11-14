#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

char *fileout_name;
int fileout_count = 0;

int argCheck(int argc, char *rawfile) {
  if (argc != 2) {
    // TODO: Change ./recover to ./quapture
    printf("Usage: ./recover IMAGE\n");
    return 1;
  }
  FILE *rawdata = fopen(rawfile, "r");
  if (rawdata == NULL) {
    printf("Unable to open the file\n");
    return 1;
  }
  return 0;
}

FILE *writeJPEG(FILE *jpeg, BYTE buffer[], int new_file) {
  if (new_file == 1) {
    if (jpeg != NULL) {
      fwrite("\n", 1, 1, jpeg);
      fclose(jpeg);
    }
    sprintf(fileout_name, "%.3d.jpg", fileout_count++);
    jpeg = fopen(fileout_name, "wb");
    if (jpeg == NULL) {
      printf("Unable to create JPEG files");
      return NULL;
    }
  }
  fwrite(buffer, 1, 512, jpeg);
  return jpeg;
}

int readRawData(char *rawfile) {
  FILE *rawdata = fopen(rawfile, "r");
  const int blocksize = 512;
  BYTE buffer[blocksize];

  fileout_name = malloc(4);
  if (fileout_name == NULL) {
    printf("Error allocating memory");
    return 1;
  }
  fileout_count = 0;
  FILE *file = NULL;

  // TODO: Add custom block size
  while (fread(buffer, 1, blocksize, rawdata) == blocksize) {
    if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 &&
        buffer[3] >= 224 && buffer[3] <= 240) {
      file = writeJPEG(file, buffer, 1);
      if (file == NULL) {
        return 1;
      }
    } else {
      if (file != NULL) {
        file = writeJPEG(file, buffer, 0);
        if (file == NULL) {
          return 1;
        }
      }
    }
  }
  fclose(rawdata);
  free(fileout_name);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argCheck(argc, argv[1]) == 1) {
    return 1;
  }
  return readRawData(argv[1]);
}
