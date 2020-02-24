# distributech_prototype

## Description
This project is command line interactive interface trying to emulate the functionality of a vending machine.
It has the following main features:
- Customisable item inventory
- Region based item inventory
- Variable user restriction based user type

As of now, the project can only be used on Windows, but since it is a CMake based project, it can easily be built on Linux as well. Only need to test with other build tools.

## Building the project
This section explains how to build the project, from setuping the environment to building the executable.
### Setuping the environment
Use the following tutorial to setup your developer environment:

https://www.40tude.fr/blog/compile-cpp-code-with-vscode-cmake-nmake/

Once that is done, clone the repository and checkout the master branch.
### Build
Once your environment is properly setuped, you can enter the following shortcuts to build the project in VSCode:
- Press ctrl-p
- Enter the following command: 
`>CMake: Build`

## How to use
Once the project is built, the CLI executable can be found in the generated "build" folder
You can run it with this command in a prompt: 
`Distributech.exe`
You should see a similar prompt:

![Default entry](https://github.com/XnorTheUnforgiven/distributech_prototype/blob/first-draft/images/DefaultEntry.png)

### Customer entry
If the user who enters the prompt is a customer, the example below should explain how the CLI works overall:

![Customer entry](https://github.com/XnorTheUnforgiven/distributech_prototype/blob/first-draft/images/CustomerEntry.png)

### Employee entry
If the user who enters the prompt is an employee, the example below should explain how the CLI works overall:

![Employee entry](https://github.com/XnorTheUnforgiven/distributech_prototype/blob/first-draft/images/EmployeeEntry.png)

The list of accepted employee user names who can have free coffees can be found in doc/special_users.json

### Technician entry
If the user who enters the prompt is a technician, the example below should explain how the CLI works overall:

![Technician entry](https://github.com/XnorTheUnforgiven/distributech_prototype/blob/first-draft/images/TechnicianEntry.png)

The list of accepted technician user names who can have free coffees can be found in doc/special_users.json

## Remaining tasks
These are the documented remaining tasks to have a project minimally worthy of being released
### Features
- Allow user to enter specific change coins
- Support on Linux platform (Create CMake configuration)

### Tests
- Setup unittests framework (GoogleTest C++ would be a good idea)
- Implement unittests
- Setup integration tests framework (Python with Pytest would be the more efficient solution)
- Implement integration tests

### Improvements
- Add a robust error handling mechanism
- Display row and columns numbers to items display
- Move CLI code intelligence into separate functions
- Fragment code in clearer methods and classes
- Make CLI less ugly and clunky