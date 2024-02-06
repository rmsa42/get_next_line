# get_next_line [42 Project]
This 42 Project challenges us to create a function that reads from a fd and return the next line read. All files containing `*_bonus` are for the [Bonus](#bonus) part

## Table of Contents
1. [Overview](#overview)
2. [About File Descriptors](#about-file-descriptors)
3. [About Static Variables](#about-static-variables)
4. [Project Structure](#project-structure)
5. [Dependencies](#dependencies)
6. [How to Use](#how-to-use)
7. [Code Examples](#code-examples)
8. [Bonus](#bonus)
9. [Contributing](#contributing)

## Overview
This project tests our knowledge about String manipulation, handling file descriptors and static variables.

The `get_next_line()` reads from a fd until it finds a delimiter, `\n` or an `EOF`, returning the line it read until the delimiter.
If the function reads past the delimiter it will only return unitl the delimiter.

The function is formatted as follow:
```c
char *get_next_line(int fd)
```
The `int fd` argument is the file descriptor that will be read.

The `get_next_line()` function has a `BUFFER_SIZE`, already defined in the header, which is the number of characters the function reads until finding a `\n` character.
If `BUFFER_SIZE = 3`, `get_next_line()` reads 3 by 3 characters until a delimiter is found.

## About File Descriptors
In a Unix operating system, a file descriptor is an abstract identifier that the operating system assigns to a file when it is opened.

File Descriptors have non-negative integer values and the 0, 1, 2 are reserved for, `STDIN_FILENO`, `STDOUT_FILENO`, `STDERR_FILENO`, respectively

Here we can see the three reserved file descriptors and an open file called `example.txt`. More about [fd](https://en.wikipedia.org/wiki/File_descriptor)
| Integer value | Name           |
|---------------|----------------|
| 0             | STDIN_FILENO   |
| 1             | STDOUT_FILENO  |
| 2             | STDERR_FILENO  |
| 3             | example.txt    |

## About Static Variables
A `static variable` is a variable that preserves their value even when they are out the function that created it. This type of variable extend their lifetime to be the entire run of the program.

Example: A `normal variable` will always disappear when the function ends and be created when the function is called.
         A `static variable` will not disappear when the funcion ends and will not be initialized again when the function is called. It will remain until the program finishes.

This type of variable is essential in `get_next_line()` as it plays a critical role in remembering what was read during the last function call. Specifically, the static variable is employed to retain the portion that was read after the delimiter. Its purpose is to keep track of the state between function calls.


## Project Structure
- `get_next_line/`: Main directory containing the source code and header files.

## Dependencies
- None

## How to Use
1. Clone the repository.
2. Include the header in your source files: `#include "get_next_line.h"`.
3. Compile your program with the two gnl files: `gcc your_program.c get_next_line.c get_next_line_utils.c`.
If you want to define yourself the BUFFER_SIZE you need to compile the program with this line: `-D BUFFER_SIZE=random_non-negative_nbr`.

## Code Examples 
```c
/* Example: The get_next_line() reads a string directly from STDIN_FILENO, two times */
#include "get_next_line.h"

int main()
{
	char *line;
	int i = 0;
	while (i < 2)
	{
		line = get_next_line(0);
		printf("get_next_line:%s\n", line);
		free(line);
		i++;
	}
}
```

## Bonus
The Bonus part of this project challenges us to make the `get_next_line()` handle multiple file descriptors at the same time.

We can achieve this using the macro from `<stdio.h>` called `FOPEN_MAX`. Basically this macro is the maximum number of file descriptors that can be open at the same time.

We can make an array of strings, like `static char	*line[FOPEN_MAX]`, that basically holds the line of every fd.

Now, if i call `get_next_line(4)` the part after the delimiter will be remembered in the `*line[4]`, and if i call again `get_next_line(5)`
the part after the delimiter will be remembered in the `*line[5]`, essentially rembering information about fd `4` and `5` if they are called again.

## Contributing
I welcome contributions. If you have any bug fix or improvement, feel free to submit a pull request on the repository.
