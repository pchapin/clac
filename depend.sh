#!/bin/bash

# This shell script runs the depend tool to produce output suitable for the Makefile.

depend '-IClacEntity;ClacEngine' depend.dep depend.out
