# Qapture

A CLI tool to recover JPEGs from a forensic image.

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

3. Run the application by passing the RAW image as the argument:

   ```
   ./qapture IMAGE.raw
   ```

4.  Enter the block size of the RAW image in bytes (Usually 512 for FAT filesystems):

      ```
      Enter the block size of the RAW image in bytes: 512
      ```