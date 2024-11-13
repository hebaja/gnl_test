#!/bin/bash
export LD_LIBRARY_PATH=./criterion-2.4.2/lib:$LD_LIBRARY_PATH
cc -I ./criterion-2.4.2/include gnl_bonus_test.c ../get_next_line/get_next_line_bonus.c ../get_next_line/get_next_line_utils_bonus.c -L ./criterion-2.4.2/lib -lcriterion -o test_b && ./test_b --verbose
