#!/bin/sh

CCOPS=-64
APP=day02

# standard daily solution
CC $CCOPS $APP.cpp ../util/chronoMessage.cpp -o $APP
