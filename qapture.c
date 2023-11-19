#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef uint8_t BYTE;

char *fileout_name;
int fileout_count = 0;
int blocksize;

void argCheck(int argc, char *rawfile)
{
  if (argc != 2)
  {
    printf("Usage: ./qapture IMAGE.raw\n");
    exit(1);
  }
  FILE *rawdata = fopen(rawfile, "r");
  fclose(rawdata);
  if (rawdata == NULL)
  {
    printf("Unable to open the file\n");
    exit(1);
  }
}

void createDirectory()
{
  struct stat dir = {0};
  int dircheck = 0;
  if (stat("./images", &dir) == -1)
  {
    dircheck = mkdir("./images", 0777);
  }
  if (dircheck)
  {
    printf("Unable to create a folder to store images./n");
    exit(1);
  }
}

FILE *writeJPEG(FILE *jpeg, BYTE buffer[], int new_file)
{
  if (new_file == 1)
  {
    if (jpeg != NULL)
    {
      fclose(jpeg);
    }
    sprintf(fileout_name, "./images/%.3d.jpg", fileout_count++);
    jpeg = fopen(fileout_name, "wb");
    if (jpeg == NULL)
    {
      printf("Unable to create JPEG files\n");
      exit(0);
    }
  }
  for (int i = 0; i < blocksize; i++)
  {
    if (buffer[i] == 255 && buffer[i + 1] == 217)
    {
      BYTE eoi[2] = {buffer[i], buffer[i + 1]};
      fwrite(eoi, 1, 2, jpeg);
      break;
    }
    fwrite(&buffer[i], 1, 1, jpeg);
  }
  return jpeg;
}

void readRawData(char *rawfile)
{
  FILE *rawdata = fopen(rawfile, "r");
  BYTE buffer[blocksize];
  int writeStatus = 0;
  int fileCount = 0;

  fileout_name = malloc(8);
  if (fileout_name == NULL)
  {
    printf("Error allocating memory\n");
    exit(1);
  }
  fileout_count = 0;
  FILE *file = NULL;

  while (fread(buffer, 1, blocksize, rawdata) == blocksize)
  {
    if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 &&
        buffer[3] >= 224 && buffer[3] <= 240)
    {
      file = writeJPEG(file, buffer, 1);
      writeStatus = 1;
      fileCount++;
    }
    else
    {
      if (writeStatus == 1)
      {
        file = writeJPEG(file, buffer, 0);
      }
    }
  }
  fclose(file);
  fclose(rawdata);
  free(fileout_name);
  printf("Number of files recovered: %i\n", fileCount);
}

int main(int argc, char *argv[])
{
  argCheck(argc, argv[1]);
  printf("Enter the block size of the RAW image in bytes: ");
  if (scanf("%d", &blocksize) != 1)
  {
    printf("Invalid arguments\n");
    exit(1);
  }
  createDirectory();
  readRawData(argv[1]);
}
