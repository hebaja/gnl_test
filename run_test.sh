#!/bin/bash
export LD_LIBRARY_PATH=./criterion-2.4.2/lib:$LD_LIBRARY_PATH
cc -I ./criterion-2.4.2/include gnl_test.c ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c -L ./criterion-2.4.2/lib -lcriterion -o test && ./test
