# qapture

A CLI tool to recover deleted JPEGs from a forensic image, written in C.

### Usage:
1. Clone this repository and navigate to the project directory:
   
    ```
    git clone https://github.com/anirudhsudhir/qapture.git
    cd qapture
    ```

2. Compile the tool using make:

   ```
   make qapture
   ```

3. Run the application by passing the path to the RAW image as the argument:

   ```
   ./qapture PATH_TO_IMAGE.raw
   ```

   The repo contains a sample card.raw file which can be utilised to test the application.
   To use the provided image, run

   ```
   ./qapture card.raw
   ```

4.  Enter the block size of the RAW image in bytes:
   
    If using the provided image, enter 512

    ```
    Enter the block size of the RAW image in bytes: 512
    ```
