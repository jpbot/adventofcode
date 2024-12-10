#!/bin/sh

CCOPS=-64
APP=day01

# day01
CC $CCOPS $APP.cpp ../util/chronoMessage.cpp -o $APP
