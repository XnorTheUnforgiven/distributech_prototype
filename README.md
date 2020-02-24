# distributech_prototype

## Description
This project is command line interactive interface trying to emulate the functionality of a vending machine.
It has the following main features:
- Customisable item inventory
- Region based item inventory
- Varaible user restriction based user type

As of now, the project can only be used on Windows, but since it is a CMake based project, it can easily be built on Linux as well if deemed necessary.

## Building the project
This section explains how to build the project, from setuping the environment to building the executable.
### Setuping the environment
Use the following tutorial to setup your developer environment:

https://www.40tude.fr/blog/compile-cpp-code-with-vscode-cmake-nmake/

Once that is done, clone the distributech_prototype repository 
### Build
Once your environment is properly setuped, you can enter the following shortcuts to build the project:
- Press ctrl-p
- Enter the following command
`>CMake: Build`

## How to use

## Remaining tasks
These are the documented remaining tasks to have a project minimally worthy of being released
### Features
- Allow user to enter specific change coins

### Tests
- Setup unittests framework (GoogleTest C++ would be a good idea)
- Implement unittests
- Setup integration tests framework (Python with Pytest would be the more efficient solution)
- Implement integration tests

### Improvements
- Add a robust error handling mechanism
- Display row and columns numbers to items display
- Move CLI code intelligence into separate functions