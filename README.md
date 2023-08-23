Introduction
This project is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them. It is written in C and follows the Betty style guide.

Features
The shell can execute any command that can be run by the shell on your system.
It supports redirection of input and output.
It can handle pipelines of commands.
It has a number of built-in commands, such as cd, echo, and exit.
Getting Started
To get started, you will need to clone the repository and compile the shell.

git clone https://github.com/your_username/simple_shell.git
cd simple_shell
gcc -Wall -Werror -Wextra -pedantic \*.c -o hsh
Once the shell is compiled, you can run it by typing the following command:

./hsh
The shell will then prompt you for a command. You can enter any command that you would like to run.

Examples
Here are some examples of commands that you can run on the shell:

ls
cd ..
pwd
echo "Hello, world!"
You can also use the shell to run pipelines of commands. For example, the following command will print the contents of the file file.txt to the standard output:

cat file.txt | wc -l
Built-in Commands
The shell has a number of built-in commands, which are commands that are built into the shell itself. These commands do not need to be run by an external program.

The following is a list of the built-in commands:

cd - Change the current directory.
echo - Print a message to the standard output.
exit - Exit the shell.
pwd - Print the current working directory.
Testing
The shell has been tested using the Betty style checker: https://github.com/holbertonschool/Betty. To run the tests, you can use the following command:

betty .
Documentation
The documentation for the shell can be found in the README.md: README.md file.

Contributing
Contributions to this project are welcome. Please follow the contributing guidelines: CONTRIBUTING.md when making a contribution.

License
This project is licensed under the MIT License. See the LICENSE: LICENSE file for more information.
