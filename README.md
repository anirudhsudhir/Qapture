# Qapture

A WIP CLI tool to recover JPEGs from a forensic image.

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

Currently, the tool assumes that the data was stored in a FAT filesystem with a block size of 512 bytes.

### Todo:
- [ ] Write files to a separate folder
- [ ] Print number of files found
- [ ] Stop reading when EOF character encountered
- [ ] Implement custom block sizes
