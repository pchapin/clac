#!/bin/bash
#
# This script cleans clac by first running 'make clean' in the two subprojects and then in the
# main folder as well.

(cd ClacEntity; make clean)
(cd ClacEngine; make clean)
make clean
