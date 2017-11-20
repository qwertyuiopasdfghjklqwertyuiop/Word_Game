#include <iostream>
#include <fstream>

#include "dictionary_tree.h"


int main() {
  try {
  Dictionary dict("error");
  }
  catch( const std::exception& e ) {
    std::cout << "Exception: " << e.what() << std::endl;
  }



    return 0;
}
