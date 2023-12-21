// part 1 is a working REPL (read–eval–print loop)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// small wrapper around the state we need to store to interact with getline()
typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));

  if (input_buffer == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }

  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

// print_prompt() prints a prompt to the user
void print_prompt() { printf("db > "); }

// We tell getline to store the read line in input_buffer->buffer 
// and the size of the allocated buffer in input_buffer->buffer_length
// We store the return value in input_buffer->input_length
void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    fprintf(stderr, "Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

// Now it is proper to define a function that frees the memory allocated for 
// an instance of InputBuffer * and the buffer element of the respective structure 
void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

// main function will have an infinite loop that prints the prompt, gets a line of input, then processes that line of input
int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);

// we parse and execute the command, right now only .exit works
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }
}
