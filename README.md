C - Simple Shell
Second group project at Holberton School : implementation of our own simplified version of a UNIX command line interpreter in C.

Description 

The objective of this project is to create from scratch a simple UNIX command interpreter with limited functionality but applying the core concepts of a more robust shell. In simple words, the shell is a program that takes commands from the keyboard and gives them to the operating system to perform. It incorporates many features and generally executes standard Shell commands found in PATH environment variable.cd command isn't handled.


Requirements

Installed gcc (GNU Compiler Collection) version 9.4.0 or newer.
Clone repository using HTTPS

Compilation

All files will be compiled on Ubuntu 20.04 LTS using :

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

List of allowed functions and system calls+

    all functions from strings.h
    access (man 2 access)
    chdir (man 2 chdir)
    close (man 2 close)
    closedir (man 3 closedir)
    execve (man 2 execve)
    exit (man 3 exit)
    _exit (man 2 _exit)
    fflush (man 3 fflush)
    fork (man 2 fork)
    free (man 3 free)
    getcwd (man 3 getcwd)
    getline (man 3 getline)
    getpid (man 2 getpid)
    isatty (man 3 isatty)
    kill (man 2 kill)
    malloc (man 3 malloc)
    open (man 2 open)
    opendir (man 3 opendir)
    perror (man 3 perror)
    printf (man 3 printf)
    fprintf (man 3 fprintf)
    vfprintf (man 3 vfprintf)
    sprintf (man 3 sprintf)
    putchar (man 3 putchar)
    read (man 2 read)
    readdir (man 3 readdir)
    signal (man 2 signal)
    stat (__xstat) (man 2 stat)
    lstat (__lxstat) (man 2 lstat)
    fstat (__fxstat) (man 2 fstat)
    strtok (man 3 strtok)
    wait (man 2 wait)
    waitpid (man 2 waitpid)
    wait3 (man 2 wait3)
    wait4 (man 2 wait4)
    write (man 2 write)

Features

    Displays a prompt and wait for the user to type a command. A command line always ends with a new line.
    The prompt is displayed again each time a command has been executed.
    The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
    Handles arguments
    Handles errors.
    Handles the end of fil condition (Ctrl+D)
    Handles the PATH
    Handles the exit built-in, that exits the shell. Usage: exit
    Handles the env built-in, that prints the current environment

Examples 

Testing

It works like this in interactive mode:

root@id:/holbertonschool-simple_shell#
./hsh
/bin/ls
hsh main.c shell.c
exit

And like this in non-interactive mode:

root@id:/holbertonschool-simple_shell#
echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
cat test_ls_2
/bin/ls
/bin/ls
cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2

Error management:

root@id:/holbertonschool-simple_shell#
echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found

Valgrind

root@id:/holbertonschool-simple_shell# valgrind ./hsh
==19647== Memcheck, a memory error detector
==19647== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==19647== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==19647== Command: ./hsh
==19647==
/bin/ls
README.md  _getline.c  _strtok.c          hsh     path_values.c   
simple_shell.h
_free.c    _strfunc.c  execute_command.c  main.c  search_path1.c
==19647==
==19647== HEAP SUMMARY:
==19647== in use at exit: 0 bytes in 0 blocks
==19647== total heap usage: 142 allocs, 142 frees, 18,486 bytes allocated
==19647==
==19647== All heap blocks were freed -- no leaks are possible
==19647==
==19647== For lists of detected and suppressed errors, rerun with: -s
==19647== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
root@id:/holbertonschool-simple_shell#

Betty Style

root@5215054250f3:~/holbertonschool-simple_shell# betty *.c

========== execute_command.c ==========
create_args_array
check_command
_fork
execute_command

========== _free.c ==========
free_args_array
_free

========== _getline.c ==========
_getline

========== main.c ==========
main

========== path_values.c ==========
get_path
get_path_values

========== search_path1.c ==========
search_path1

========== _strfunc.c ==========
_strcmp
_strlen
_strcpy
_strcatcp

========== _strtok.c ==========
is_delim
_strtok

Files
All of the following files contain functions written in C :
Filename 	Description
_free.c 	File which content functions that frees strings and arrays of strings
_getline.c 	Gets a line from a stream
_strfunc.c 	Content :
_strcmp (function that compares 2 strings)
_strlen (returns the length of a string)
_strcpy (function that copies the string pointed to by src)
_strcatcp (function that concatenates two strings)
_strtok.c 	Allow to isolates sequential tokens in a null-terminated string
execute_command.c 	Module that allows to execute a command
main.c 	Main of the Simple Shell simulation program
path_values.c 	Get the PATH environment variable value in one single string
search_path1.c 	Allow to searche PATH1 environment variable
simple_shell.h 	Header file which contains all functions prototypes and include librairies

Authors
Abdullatif Alzaher, Donna Almadani
