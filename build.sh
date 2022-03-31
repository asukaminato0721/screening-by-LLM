#!/bin/bash
rm -v ./*.o ;
gcc -Wall -Wextra -c ./third_party/cJSON/cJSON.c main.c parse.c;
gcc -Wall -Wextra -o main ./*.o ;
./main
