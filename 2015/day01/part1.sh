#!/bin/bash
expr `grep -o '(' input_day1.in |wc -w` - `grep -o ')' input_day1.in |wc -w`
