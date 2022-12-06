#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Check that the user provided the correct number of arguments
  if (argc != 2) {
    printf("Usage: jitcompile FILE.ext\n");
    return 1;
  }

  // Open the input file in binary mode
  FILE *input_file = fopen(argv[1], "rb");
  if (!input_file) {
    printf("Error: unable to open file %s\n", argv[1]);
    return 1;
  }

  // Create the output file by replacing the input file's extension
  // with ".jit"
  char output_filename[256];
  strcpy(output_filename, argv[1]);
  char *last_dot = strrchr(output_filename, '.');
  if (last_dot) {
    strcpy(last_dot, ".jit");
  } else {
    strcat(output_filename, ".jit");
  }

  // Open the output file in binary mode
  FILE *output_file = fopen(output_filename, "wb");
  if (!output_file) {
    printf("Error: unable to create file %s\n", output_filename);
    return 1;
  }

  // Read the input file one byte at a time and convert each byte
  // to a string of "JIT" and "WORLD"
  unsigned char buffer[1];
  while (fread(buffer, 1, 1, input_file) == 1) {
    // Convert each bit in the byte to "JIT" or "WORLD"
    for (int bit = 7; bit >= 0; bit--) {
      // Check if the bit at the current position is set
      if (buffer[0] & (1 << bit)) {
        fprintf(output_file, "W0RLD");
      } else {
        fprintf(output_file, "JIT");
      }
    }
  }

  // Close both files
  fclose(input_file);
  fclose(output_file);

  return 0;
}