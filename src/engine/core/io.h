#ifndef IO_H
#define IO_H

#include <errno.h>
#include "utils.h"

typedef struct file {
  char *data;
  usize len;
  bool is_valid;
} ast_file;

#define IO_READ_CHUNK_SIZE MB(20)
#define IO_READ_ERROR_GENERAL "Error reading file: %s. errno: %d\n"
#define IO_READ_ERROR_MEMORY "Not enough free memory to read file: %s\n"
#define IO_READ_ERROR_TOO_LARGE "Input file too large: %s\n"

static inline ast_file ast_io_file_read(const char *path) {
  ast_file file = {.is_valid = false};

  // Open the file in binary read mode
  FILE *file_ptr = fopen(path, "rb");
  if (!file_ptr || ferror(file_ptr)) {
    LOG_ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
  }

  // file data variables
  char *data = NULL;
  char *temp_data;
  usize used_size = 0;
  usize total_size = 0;
  usize read_size;

  // Loop to read file data in chunks
  while (true) {
    if (used_size + IO_READ_CHUNK_SIZE + 1 > total_size) {
      total_size = used_size + IO_READ_CHUNK_SIZE + 1;

      // Log error and return if file is too large
      if (total_size <= used_size) {
        free(data);
        LOG_ERROR_RETURN(file, IO_READ_ERROR_TOO_LARGE, path);
      }

      // Log error and return if memory allocation fails
      temp_data = (char*) realloc(data, total_size);
      if (!temp_data) {
        free(data);
        LOG_ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
      }
      data = temp_data;
    }

    // Read a chunk of data
    read_size = fread(data + used_size, 1, IO_READ_CHUNK_SIZE, file_ptr);
    if (read_size == 0) break;
    used_size += read_size;
  }

  if (ferror(file_ptr)) {
    free(data);
    LOG_ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
  }

  // Log error and return if a read error occurred
  temp_data = (char*) realloc(data, used_size + 1);
  if (!temp_data) {
    free(data);
    LOG_ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
  }
  data = temp_data;
  data[used_size] = '\0';

  file.data     = data;
  file.len      = used_size;
  file.is_valid = true;

  fclose(file_ptr);
  return file;
}

// Function to write data to a file
static inline bool ast_io_file_write(void *buffer, usize size, const char *path) {
  // Open te file in binary write mode
  FILE *file_ptr = fopen(path, "wb");
  
  // Log error and return if file can't be opened
  if(!file_ptr || ferror(file_ptr)) {
    LOG_ERROR_RETURN(false, "Cannot write file: %s. errno: %d\n", path, errno); 
  }

  // Write the buffer to the file
  usize chunks_written = fwrite(buffer, size, 1, file_ptr);
  fclose(file_ptr);  // Close the file

  // Check if the write was successful
  if (chunks_written != 1) {
    LOG_ERROR_RETURN(false, "Write error. Expected 1 chunk, got %zu.\n", chunks_written);
  }

  return true; 
}

#endif // !IO_H
