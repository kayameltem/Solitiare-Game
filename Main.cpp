#include  <stdio.h>
#include <iostream>
#include "FileIO.h"

using namespace std;


int main(int argc, char* argv[]) {
        FileIO file;
		file.input(argv[1]);
        file.out(argv[2],argv[3]);
    return 0;
}


