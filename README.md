<div align="center">

# ft_printf

**A from-scratch reimplementation of the C standard library's `printf`, built at 42 School.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![School](https://img.shields.io/badge/school-42-000000?style=flat-square&logo=42&logoColor=white)
![Norminette](https://img.shields.io/badge/norminette-compliant-brightgreen?style=flat-square)
![Flags](https://img.shields.io/badge/flags--Wall%20--Wextra%20--Werror-blue?style=flat-square)

</div>

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [How It Works](#how-it-works)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Differences from `printf`](#differences-from-printf)
- [Roadmap](#roadmap)
- [Author](#author)

---

## About

`ft_printf` is a custom implementation of the standard `printf` function, written in C as part of the 42 School curriculum. It handles formatted output for several data types and format specifiers, using **variadic functions** (`<stdarg.h>`) to accept any number of arguments.

The goal of the project is to understand what happens behind one of the most used functions in C:

- parsing a format string character by character
- walking a variable argument list with `va_start`, `va_arg` and `va_end`
- converting numbers to any base and writing them with the `write` system call
- returning the exact number of characters printed, as `printf` does

The only external functions allowed are `write`, `malloc`/`free` and the `va_*` macros. The code follows the 42 **Norm**, a set of strict style rules (for example: at most 25 lines per function, at most 5 functions per file, no `for` loops). The project is built as a static library, `libftprintf.a`, on top of my own [`libft`](libft/), a library of reimplemented libc functions.

---

## Features

| Specifier | Prints | Example | Output |
|:---------:|--------|---------|--------|
| `%c` | A single character | `ft_printf("%c", 'A')` | `A` |
| `%s` | A string | `ft_printf("%s", "hi")` | `hi` |
| `%p` | A pointer address in hexadecimal | `ft_printf("%p", ptr)` | `0x7ffd5e8a` |
| `%d` | A signed decimal integer | `ft_printf("%d", -42)` | `-42` |
| `%i` | A signed decimal integer | `ft_printf("%i", 42)` | `42` |
| `%u` | An unsigned decimal integer | `ft_printf("%u", -1)` | `4294967295` |
| `%x` | A number in lowercase hexadecimal | `ft_printf("%x", 255)` | `ff` |
| `%X` | A number in uppercase hexadecimal | `ft_printf("%X", 255)` | `FF` |
| `%%` | A literal percent sign | `ft_printf("%%")` | `%` |

Other properties:

- **Same return value as `printf`**: the total number of characters written.
- **No heap allocation**: output goes straight to standard output, so there is nothing to free and nothing to leak.
- **Handles edge cases** the same way glibc does: `INT_MIN`, `UINT_MAX`, `NULL` strings (`(null)`) and `NULL` pointers (`(nil)`).
- **One converter for every base**: `%u`, `%x`, `%X` and `%p` all go through the same recursive `print_base` function.

---

## How It Works

```
ft_printf("Hi %s, you are %d (0x%x)\n", "Ada", 36, 36)
          │
          ├─ plain character ──► print_char()          count += 1
          │
          └─ '%' found ──► check_type(next char)
                             ├─ 'c'       ► print_char()
                             ├─ 's'       ► print_string()
                             ├─ 'd' / 'i' ► print_int()
                             ├─ 'u'       ► print_base(n, "0123456789")
                             ├─ 'x' / 'X' ► print_base(n, "0123456789abcdef" / "...ABCDEF")
                             ├─ 'p'       ► "0x" + print_base(address, "0123456789abcdef")
                             └─ '%'       ► print_char('%')
```

1. `ft_printf` opens the argument list with `va_start`.
2. It walks the format string. Plain characters are written as they are.
3. When it meets a `%`, `check_type` reads the next character and sends the next argument to the matching printer. The `va_list` is passed by pointer, so the list stays correct on every platform, including ARM and Apple Silicon.
4. Each printer returns how many characters it wrote, and `ft_printf` adds these up.
5. The list is closed with `va_end` and the total is returned.

`print_base` is the core of the number conversions. It divides the number by the length of the base string, calls itself recursively to print the higher digits first, and then prints `base[n % len]`. Changing the base string is all it takes to switch between decimal, lowercase hex and uppercase hex.

---

## Project Structure

```
42-ft_printf/
├── Makefile          # Builds libftprintf.a (all, clean, fclean, re, test)
├── ft_printf.h       # Prototypes, includes and base strings
├── ft_printf.c       # ft_printf(): format parsing and dispatch, %p
├── print_base.c      # %u, %x, %X and the digits of %p
├── print_char.c      # %c, %% and every plain character
├── print_string.c    # %s
├── print_int.c       # %d and %i
├── main.c            # Test program comparing ft_printf with printf
└── libft/            # My libc reimplementation (ft_strlen, ft_putchar_fd, ...)
```

---

## Installation

### Requirements

- A C compiler (`cc`, `gcc` or `clang`)
- `make`
- A Unix-like system (Linux, macOS, or WSL on Windows)

### Build

```bash
git clone https://github.com/rasiolisufaj/42-ft_printf.git
cd 42-ft_printf
make
```

This builds `libft` first and then creates **`libftprintf.a`** at the root of the repository.

| Command | Description |
|---------|-------------|
| `make` | Build `libftprintf.a` |
| `make test` | Build and run the comparison test against the real `printf` |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the libraries |
| `make re` | Rebuild everything from scratch |

---

## Usage

Include the header and call `ft_printf` the same way you would call `printf`:

```c
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("Hello %s! You scored %d%%.\n", "world", 42);
    ft_printf("That line was %d characters long.\n", count);
    ft_printf("255 in hex: %x / %X\n", 255, 255);
    return (0);
}
```

Compile your program with the library:

```bash
cc main.c libftprintf.a -o my_program
./my_program
```

Output:

```
Hello world! You scored 42%.
That line was 29 characters long.
255 in hex: ff / FF
```

---

## Testing

```bash
make test
```

[`main.c`](main.c) is compiled twice: once with the real `printf` and once with `ft_printf`. Both programs run, and their outputs are compared with `diff`. Every line also prints the function's return value, so the test checks both **what** is printed and **how many** characters are counted.

```
c: [a] [0] = 10
s: [hello] [] [(null)] = 22
d: [0] [-42] [2147483647] [-2147483648] = 39
u: [0] [42] [4294967295] = 24
x: [0] [FF] [ffffffff] [DEADBEEF] = 33
p: [0xdeadbeef] [0xffffffffffffffff] [(nil)] = 44
mix: z str -1 4294967295 ffffffff FFFFFFFF % = 44
 = 0
test: OK
```

Community testers often used for this project:

- [Tripouille/printfTester](https://github.com/Tripouille/printfTester)
- [paulo-santana/ft_printf_tester](https://github.com/paulo-santana/ft_printf_tester)

---

## Differences from `printf`

- **No flags, width or precision.** Modifiers such as `-`, `0`, `.`, `#`, `+` and space are not supported (these are the project's bonus part).
- **`NULL` pointers** print `(nil)`, as glibc on Linux does. macOS's `printf` prints `0x0` instead.
- **A `%` at the end of the format string** is ignored instead of causing undefined behavior.
- **Output goes straight to `stdout`** with no buffering, so each character is a separate `write` call.

---

## Roadmap

- [x] `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, `%%`
- [x] `(null)` / `(nil)` for `NULL` arguments
- [x] `Makefile` that builds `libftprintf.a`
- [x] Automated comparison test against the real `printf`
- [ ] Bonus: flags `-0.# +` and field width / precision

---

## Author

**Rasiol Isufaj** · 42 login `raisufaj`

[![GitHub](https://img.shields.io/badge/GitHub-rasiolisufaj-181717?style=flat-square&logo=github)](https://github.com/rasiolisufaj)

If this project helped you, consider giving it a ⭐ on GitHub!
