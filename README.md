ds_clean
========

Recursive delete the ".DS_Store" files created by OS X from specified path

Usage: ds_clean [-v] [directory...]

Options
"-h" (help) quick help
"-v" (verbose) print the cleaned folder paths

COMPILE
You can compile the source code with GCC compiler, from Terminal, using the following statement:
gcc ds_clean.c -o ds_clean

After that copy the outputed file "ds_clean" to "/usr/local/bin/" folder using the statement below:
Attention! To do that you need administrative rights
sudo cp ds_clean /usr/local/bin
