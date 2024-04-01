# simple_shell
A basic UNIX-like shell implementation in C for our ALX Software Engineering course

# Simple Shell

This project is a simple UNIX-like shell implementation in C as part of our ALX Software Engineering course. It aims to demonstrate our understanding of various low-level programming concepts, such as system calls, file I/O, and memory management.

## Features

- Execution of built-in and external commands
- Command parsing
- Support for `PATH` environment variable
- Support for the following built-in commands:
  - `exit`
  - `setenv`
  - `unsetenv`
  - `cd`
- Error handling

## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection) to compile the code
- A UNIX-like environment (Linux, macOS, or WSL on Windows)

### Compilation

To compile the simple shell, run the following command in the project directory:

```sh
gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell
```

This will create an executable file named simple_shell.

# Usage
To start the shell, run the following command:
```
./simple_shell
```
You will be presented with a prompt ($ ) where you can enter commands.

# Examples
Here are some examples of how to use the shell:
```sh
$ ls
$ pwd
$ cd ..
$ setenv MY_VARIABLE my_value
$ unsetenv MY_VARIABLE
$ exit
```

To quit the shell you can use either of these commands: `Ctrl+d` || type `exit`

# Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

For more information, consult the documentation included in the doc folder.

# Authors
- Jason Kvist <nftsingularity8@gmail.com>
- Rose-Sarah Glover <rosesarahglover@gmail.com>
