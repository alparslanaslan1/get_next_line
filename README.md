# get\_next\_line

`get_next_line` is a function that reads and returns the next line from a file descriptor. It reads from the given file descriptor until it encounters a newline (`\n`) or reaches end-of-file, and returns the line as a dynamically allocated string.

## File Structure

```
get_next_line/
├── get_next_line.c        # Core function implementation
├── get_next_line_utils.c  # Helper functions for string operations and buffering
└── get_next_line.h        # Function prototype and necessary includes
```

* **`get_next_line.c`**: Contains the `get_next_line` function, which manages reading from the file descriptor, buffering, and returning each line.
* **`get_next_line_utils.c`**: Implements utility functions such as string concatenation (`ft_strjoin`), searching for newline characters (`ft_strchr`), and calculating string lengths (`ft_strlen`).
* **`get_next_line.h`**: Declares `get_next_line`, the helper function prototypes, and any required macros (e.g., `BUFFER_SIZE`).

## Usage

1. **Include the header** in your source file:

   ```c
   #include "get_next_line.h"
   ```

2. \*\*Define \*\***`BUFFER_SIZE`** before including or during compilation (must be greater than 0):

   ```c
   #define BUFFER_SIZE 32
   ```

3. \*\*Call \*\***`get_next_line`** in your code:

   ```c
   int fd = open("file.txt", O_RDONLY);
   char *line;

   while ((line = get_next_line(fd)) != NULL) {
       printf("%s", line);
       free(line);
   }
   close(fd);
   ```

## Compilation

Compile the function and your program together. For example:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 \
    get_next_line/get_next_line.c \
    get_next_line/get_next_line_utils.c \
    your_program.c -o your_program
```

## Examples

| Usage Call           | Behavior                                            |
| -------------------- | --------------------------------------------------- |
| `get_next_line(fd)`  | Returns next line (including `\n`) or `NULL` at EOF |
| Looping until `NULL` | Reads and processes the entire file line by line    |

## Limitations

* **`BUFFER_SIZE`** must be a positive integer; behavior is undefined if `BUFFER_SIZE <= 0`.
* The returned line **must** be freed by the caller to avoid memory leaks.
* Does not handle multiple file descriptors simultaneously (no static storage per FD).

## Author

* **Alparslan Aslan** ([alaslan@student.42kocaeli.tr](mailto:alaslan@student.42kocaeli.tr))

## License

No explicit license is provided. Use, modify, and distribute at your owisk.
