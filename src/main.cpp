/*
Name:               main.cpp
Description:        Distributech CLI endpoint
Author:             Xavier Mercure-Gagnon
Date of creation:   21-02-2020
Last edit:          21-02-2020
*/

#include <iostream>

#include "include\distributech\cli.h"
 
int main() {
  try {

    DistributechCli cli;
    cli.run();
  }
  catch(...) {
    std::cout << "Exiting program!";
  }

  exit(0);
}