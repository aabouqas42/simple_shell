# ALX Simple Shell

This repository contains the implementation of a simple shell program as part of the ALX Software Engineering program.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Introduction

The ALX Simple Shell is a basic command-line interpreter that allows users to execute commands and manage processes. It provides a user-friendly interface for interacting with the underlying operating system.

## Features

- Executes external commands by creating child processes.
- Supports input and output redirection using `<` and `>` operators.
- Implements basic built-in commands such as `cd`, `exit`, and `env`.
- Handles background processes using the `&` operator.
- Provides a prompt for user input.
- Supports command line arguments.

## Getting Started

To get started with the ALX Simple Shell, follow these steps:

1. Clone the repository:

   $ git clone https://github.com/your-username/alx-simple-shell.git
   Change to the project directory:

Copy
$ cd alx-simple-shell

```

Compile the source code:


Copy
$ gcc -Wall -Werror -Wextra -pedantic *.c -o shell
```

Run the shell:

Copy
$ ./shell

```

Usage
Once the shell is running, you can enter commands and execute them. The basic syntax is:


Copy
$ command [arguments]
Here are some examples of supported commands:

Execute an external command:


Copy
$ ls -l
```

Change directory:

Copy
$ cd /path/to/directory

```

Exit the shell:


Copy
$ exit
```

Display environment variables:

Copy
$ env

```

Execute a command in the background:


Copy
$ command &
```

For more information on supported features and usage, please refer to the project documentation or the source code itself.

Contributing
Contributions to the ALX Simple Shell project are welcome. If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request on the project's GitHub repository.

License
This project is licensed under the MIT License. See the LICENSE file for more information.

Acknowledgments
This simple shell project is developed as part of the ALX Software Engineering program. Special thanks to all the instructors and mentors who contributed to the development of this project.
