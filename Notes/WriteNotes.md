# The `write` Function in C

The `write` function is a **low-level system call** used to send raw bytes directly to an output destination  
(such as the terminal, a file, or a network socket).  
It’s part of the **POSIX** standard and is declared in the `<unistd.h>` header.

Unlike `printf` (a high-level C Standard Library function), `write` bypasses formatting and buffering,  
communicating directly with the operating system.  
This makes it faster for small outputs but less convenient for formatted text.

---

## Syntax

```c
ssize_t write(int file_descriptor, const void *buffer, size_t count);
```

````

**Return value:**

- **On success**: Returns the number of bytes actually written.
- **On error**: Returns `-1` and sets `errno` to indicate the cause.
- **Note:** `write` may write **fewer bytes than requested** (partial write).
  Always check the return value when writing to files, sockets, or pipes.

---

## Parameters Explained

1. **`file_descriptor`** – The destination for the output.

   - `0` → **Standard Input** (stdin) _(rarely used for writing)_
   - `1` → **Standard Output** (stdout) _(default terminal output)_
   - `2` → **Standard Error** (stderr) _(error messages)_
   - Other positive integers → File descriptors from `open()`, `socket()`, etc.

2. **`buffer`** – Pointer to the data you want to send.

   - Can be:

     - Address of a single variable (`&c` where `c` is a `char`)
     - A string literal (`"Hello"`)
     - A memory block containing binary data

3. **`count`** – Number of bytes to write.

   - For text strings: The number of visible characters (excluding the null terminator `'\0'`).

     - Example: `"Ergis"` → 5 characters → `count = 5`

   - For binary data: Exact number of bytes you want to send.

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
- `"Ergis"` → The data to be written
- `5` → Number of bytes (characters) to send

---

## How It Differs from `printf`

| Feature         | `write`                         | `printf`                                |
| --------------- | ------------------------------- | --------------------------------------- |
| **Level**       | Low-level system call           | High-level C Standard Library function  |
| **Formatting**  | No formatting — raw output only | Supports format specifiers (`%d`, `%s`) |
| **Header**      | `<unistd.h>`                    | `<stdio.h>`                             |
| **Buffering**   | Unbuffered (writes immediately) | Buffered output                         |
| **Performance** | Faster for small, raw writes    | Slightly slower due to formatting logic |
| **Portability** | POSIX-specific                  | Portable across all C environments      |

---

## When to Use `write`

- **Fast, unformatted output** (e.g., debug logs, status messages)
- **Writing binary data** (images, raw bytes, serialized data)
- **Working with file descriptors** from `open()`, `socket()`, or `pipe()`
- **System-level programming** where minimal overhead is needed

---

## Common Mistakes to Avoid

- ❌ **Including the null terminator in `count`** for text unless explicitly desired.
- ❌ **Ignoring the return value** — `write` might write fewer bytes than requested (especially to sockets/pipes).
- ❌ **Using `write` for formatting** — use `printf`/`sprintf` instead if you need formatted output.

---

## Quick Tips

- Write a **single character**:

  ```c
  char c = 'A';
  write(1, &c, 1);
  ```

- Write a **string**:

  ```c
  write(1, "Hello", 5); // '5' is number of visible characters
  ```

- Write an **error message** to `stderr`:

  ```c
  write(2, "Error occurred\n", 15);
  ```

- Safely handle **partial writes** (important for files and sockets):

  ```c
  ssize_t bytes_written = write(fd, buf, len);
  if (bytes_written < 0) {
      // handle error
  } else if (bytes_written < len) {
      // handle partial write
  }
  ```

---

## Summary

`write` is fast, direct, and unformatted — ideal for low-level output where performance and control
are more important than convenience or portability.
For formatted, portable output, use `printf` instead.

````
