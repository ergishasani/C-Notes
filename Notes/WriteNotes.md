# The `write` Function in C

The `write` function is a **low-level system call** used to send raw bytes directly to an output destination (such as the terminal, a file, or even a network socket).  
It’s part of the **POSIX** standard and is declared in the `<unistd.h>` header.

Unlike `printf`, which is a high-level function from the C Standard Library, `write` bypasses formatting and buffering and communicates directly with the operating system.

---

## Syntax

```c
ssize_t write(int file_descriptor, const void *buffer, size_t count);
```

- **Return value**:
  On success, it returns the number of bytes actually written.
  On error, it returns `-1` and sets `errno` to indicate the error.

---

## Parameters Explained

1. **`file_descriptor`** – Identifies the output destination.

   - `0` → **Standard Input** (stdin) _(normally used for reading, rarely for writing)_
   - `1` → **Standard Output** (stdout) _(default terminal output)_
   - `2` → **Standard Error** (stderr) _(error messages)_
   - Other positive integers → File descriptors obtained from `open()`, `socket()`, etc.

2. **`buffer`** – Pointer to the data you want to send.

   - This can be:

     - The address of a single variable (e.g., `&c` where `c` is a `char`)
     - A string literal (e.g., `"Hello"`)
     - A memory block containing binary data

3. **`count`** – Number of bytes to write.

   - For a string, this is **the number of characters** (excluding the null terminator `'\0'`).
   - Example: `"Ergis"` → 5 characters → `count = 5`
   - For binary data, it’s the exact byte size you want to send.

---

## Example

```c
#include <unistd.h>

void test(void) {
    write(1, "Ergis", 5); // Output: Ergis
}
```

**Explanation:**

- `1` → Write to standard output (terminal)
- `"Ergis"` → The data being written
- `5` → Number of characters to send

---

## How It Differs from `printf`

| Feature         | `write`                           | `printf`                                |
| --------------- | --------------------------------- | --------------------------------------- |
| **Level**       | Low-level system call             | High-level C Standard Library function  |
| **Formatting**  | No formatting, raw output only    | Supports format specifiers (`%d`, `%s`) |
| **Header**      | `<unistd.h>`                      | `<stdio.h>`                             |
| **Buffering**   | No buffering (writes immediately) | Uses buffered output                    |
| **Performance** | Faster for small, raw writes      | Slower due to formatting and buffering  |
| **Portability** | POSIX-specific                    | Portable across all C environments      |

---

## When to Use `write`

- **Fast, unformatted output** (e.g., debugging, logging to stderr)
- **Writing binary data** (not just text)
- **Working with file descriptors** from `open()` or `socket()`
- **System programming** where low-level control is needed

---

## Common Mistakes to Avoid

- **Including the null terminator in `count`** for strings (unless you explicitly want it).
- **Not checking the return value** — `write` might write fewer bytes than requested.
- **Using `write` for formatted output** — use `printf` or `sprintf` instead.

---

## Quick Tips

- For a single character:

  ```c
  char c = 'A';
  write(1, &c, 1);
  ```

- For a string:

  ```c
  write(1, "Hello", 5); // '5' is the number of characters
  ```

- For error messages (stderr):

  ```c
  write(2, "Error occurred\n", 15);
  ```

---

**Summary:**
`write` is fast, direct, and unformatted. It’s perfect for low-level output where performance and control are more important than convenience or formatting.

## Practical Examples

### Writing a Single Character

```c
char c = 'X';
write(1, &c, 1);
```

### Writing a String

```c
write(1, "Hello, World!", 13);
```

### Writing an Error Message to Standard Error

```c
write(2, "Fatal error\n", 12);
```

### Handling Partial Writes Safely

```c
ssize_t total_written = 0;
ssize_t bytes_written;
size_t len = /* length of buffer */;
char *buf = /* pointer to data */;

while (total_written < len)
{
    bytes_written = write(fd, buf + total_written, len - total_written);
    if (bytes_written < 0)
    {
        // handle error
        break;
    }
    total_written += bytes_written;
}
```

---

## Final Tip

Always check the return value of `write` to ensure your data was fully written, especially when working with files, sockets, or pipes, where partial writes can occur.
