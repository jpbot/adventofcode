#!/bin/sh

CCOPS=-64
APP=day08

# standard daily solution
CC $CCOPS $APP.cpp ../util/chronoMessage.cpp -o $APP
