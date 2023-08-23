# Simple Shell

Simple Shell is a project that implements a basic command-line interpreter or shell. It provides a simple interface for users to interact with the operating system by executing commands.

## Features

- Executes commands entered by the user.
- Handles built-in commands such as `cd`, `exit`, etc.
- Supports execution of external commands.
- Parses command line arguments and handles input/output redirection.
- Supports piping of commands.
- Implements signal handling for Ctrl+C (`SIGINT`) and Ctrl+D (`EOF`).

## Getting Started

To get started with the Simple Shell project, follow these steps:

1. Clone the repository:
   ```shell
   git clone https://github.com/your-username/simple_shell.git
   Change into the project directory:
   ```

Copy
cd simple_shell

```

Compile the source code:


Copy
gcc -Wall -Werror -Wextra -pedantic *.c -o shell
```

Run the shell:

Copy
./shell

```

Usage
The Simple Shell supports the following features and commands:

Interactive mode:


Copy
$ ./shell
Simple Shell$ ls
file1 file2 file3
Simple Shell$ pwd
/path/to/current/directory
Simple Shell$ exit
```

Non-interactive mode:

Copy
$ echo "ls" | ./shell
file1 file2 file3

```

Built-in commands:

cd [directory]: Change the current working directory.
exit: Exit the shell.
Redirecting input/output:


Copy
$ ls > files.txt   # Redirect the output of ls to a file
$ cat < files.txt  # Read input from a file
```

Piping commands:

Copy
$ ls | grep file # Pipe the output of ls to grep

```

File Structure
The project repository is organized as follows:

Copy
.
├── main.c           # Entry point of the shell
├── shell.h          # Header file with function prototypes and structure definitions
└── README.md        # Project documentation
Contributing
Contributions to the Simple Shell project are welcome! If you find any issues or want to add new features, feel free to open an issue or submit a pull request.

License
This project is licensed under the MIT License. See the LICENSE file for more information.

Acknowledgments
The Simple Shell project is part of the ALX Software Engineering curriculum and is based on the Unix shell.

```
