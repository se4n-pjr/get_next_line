*This project has been created as part of the 42 curriculum by jpoh.*

# get_next_line

## Description
**get_next_line** is a core programming project in the 42 curriculum. The primary goal of this project is to code a function in C that returns a single line read from a file descriptor (`fd`). Calling this function in a loop allows reading an entire text stream or file line by line until reaching the end of file (EOF).

Recreating this standard I/O mechanism deepens understanding of static variables, persistent state management between function calls, buffer management defined at compile time (`BUFFER_SIZE`), Unix system calls (`read`), and memory leak prevention in C while enforcing strict coding standards (**The Norm**).

---

## Technical Architecture & Function Details

The project is structured into modular utility functions and a core reading engine designed for optimal buffer handling:

### 1. Mandatory Functions
- `get_next_line`: Core function that orchestrates buffer reading, stash maintenance, and line extraction for a single file descriptor.
- `extract_line`: Allocates and extracts a complete line (up to and including `\n` or `\0`) from the current accumulated stash.
- `clean_stash`: Trims the extracted line from the stash and frees old memory, preserving leftover buffer contents for subsequent calls.
- `has_newline`: Scans the stash string to check if a newline character (`\n`) has been buffered.
- `ft_strjoin`: Concatenates the static stash with newly read buffer chunks while safely managing dynamic memory allocation and pointer freeing.

### 2. Bonus Implementation (Multi-FD Support)
- **Concurrent Descriptor Handling**: Extends `get_next_line` to handle multiple open file descriptors simultaneously (e.g., interleaving read calls across `fd 3`, `fd 4`, and `fd 5`) without losing track of individual buffer states or returning mismatched lines.
- **Single Static Array Architecture**: Satisfies the 42 single static variable constraint by using an array of file descriptor buffer pointers (`static char *stash[OPEN_MAX]`) indexed directly by `fd`.
- **Bounds Protection**: Safeguards against invalid array accesses by capping valid file descriptor range (`0` to `OPEN_MAX - 1`).

---

## Instructions

### Prerequisites
- A UNIX-based operating system (Linux or macOS).
- `gcc` or `clang` compiler.
- `make` utility (optional for testing builds).

### Compilation & Installation
Clone the repository and compile the source files alongside your project code, setting a custom `BUFFER_SIZE` at compile time if desired:

```bash
git clone [https://github.com/your-username/get_next_line.git](https://github.com/your-username/get_next_line.git)
cd get_next_line

# Compile mandatory part with a specific buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl

# Compile bonus part (Multi-FD support)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus

Resources:

References
	Standard C I/O & System Calls: man 2 read, man 2 open, and man 3 malloc Linux manual pages.

	C Programming Concepts: The C Programming Language (Kernighan & Ritchie) for standards on static variable lifetimes, pointer manipulation, and stack vs. heap allocation limits.

AI Assistance Declaration

	In accordance with 42 academic policies, AI tools were utilized during the development of this project for the following specific tasks:

	Edge Case Analysis & Memory Leak Verification: Used to review boundary conditions (such as handling BUFFER_SIZE=1, empty files, missing trailing newlines, and immediate read failure cleanup).

	Norminette & Style Verification: Used to verify C syntax rules (such as function line limits, variable declaration blocks, and comma operator return conventions).

	Documentation: Assisting in structuring and generating this README.md file based on project specification requirements.
