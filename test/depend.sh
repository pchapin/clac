#!/bin/bash

# This shell script runs the depend tool to produce output suitable for the Makefile.

depend '-I../ClacEntity;../ClacEngine;../SpicaCpp' depend.dep depend.out
