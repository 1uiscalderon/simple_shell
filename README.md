# Shell project

A shell is a program designed to read commands typed by the user and execute apropiate programs in response to those commands.
The shell is usually known as a command interpreter.

The following are important versions of the shell that have appeered over time:

* Bourne shell (sh):\
The oldest of the most used shells, written by Steve Bourne.
It contains many of the features familiar in all shells: I/O redirection, pipe- lines, filename generation, variables, manipulation of environment variables, command substitution, background command execution, and functions.

* C shell (csh):\
Written by Bill Joy.\
It provides several useful interactive features unavaliable in the Bourne shell including command history, command-line editing, job control, and aliases.

* Bourne again shell (bash):\
It is the GNU project's reimplementation of the Bourne shell. It supplies interactive features similar to those available in the C and Korn shells.


## simple_shell

The program written for this shell project, is based on the sh shell, and the outputs and errors it produces.


The simple_shell can be used in two different ways:
* Interpretation of shell scripts.
* Interactive use.

### Synopsis

./hsh
<command> <argument 1> <argument 2>

### Prompt

When used interactively, the Simple Shell prompts
the value "$" before reading a command.

### The Environment

The simple shell creates a copy of the environment to be passed to the programs it will execute.

### The PATH
With the function path, the simple_shell searches for the environment variable PATH, and verifies if the first argument of the line written by the user is in fact an executable file. 

### The Built ins

The simple_shell supports the builtins:
* env
* exit

### Executing programs

Using the function start_new_process, the simple_shell, call the fork system call. 

The child process of this fork uses the function execve to execute the first argument passed by the user, first without concatenating it with any path, and if it is not possible to execute that way, it calls the execve function again to execute it but now concatenated with its corresponding path if it actually has one.
If the child process cant execute the passed program, it frees the array of arguments and exits with EXIT_FAILURE.

THe parent process waits for the child to terminate, and if there is any problem while waiting, it returns 0.

### Freeing memory allocations 
The simple_shell frees all the dynamically allocated memory used in its functions.

### Exiting the shell

To exit the simple_shell you can either type "exit" or type CRL + D.

## Use case

vagrant@vagrant-ubuntu-trusty-64:~/holberton/projects/simple_shell$ ./hsh\
$ pwd\
/home/vagrant/holberton/projects/simple_shell

## Authors
* Luis Miguel Calderon Escobar.
* Tomas Gomez Velez.









