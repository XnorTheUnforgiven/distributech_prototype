/*
Name:               main.cpp
Description:        Distributech CLI endpoint
Author:             Xavier Mercure-Gagnon
Date of creation:   21-02-2020
Last edit:          21-02-2020
*/

#include <iostream>
#include <lib\nlohmann\json.hpp>

#include "include\distributech\cli.h"

// for convenience
using json = nlohmann::json;
 
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