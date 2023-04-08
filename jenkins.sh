#
# This shell script is executed by Jenkins. It defines a "build."

# This script will exit immediately if any command returns a failing exit status.
set -e

# Make sure we have the environment we need.
#export PATH=/opt/gnat/bin:/opt/spark/bin:/opt/codepeer/bin:/opt/gnatstudio/bin:$PATH

# Build the executable and the unit test program. Execute the unit test program.
make
cd check
./u_tests
cd ..

# Do a style check using GNATcheck using a helper shell script.
# See the comments in the script file for an explanation.
#run-gnatcheck.sh

# Build the API documentation.
doxygen

# Build the main documentation.
cd doc
pdflatex -file-line-error -halt-on-error Tutorial.tex
bibtex Tutorial
pdflatex -file-line-error -halt-on-error Tutorial.tex > /dev/null
pdflatex -file-line-error -halt-on-error Tutorial.tex > /dev/null
cd ..

# TODO: Copy documentation to the web site for public review.
