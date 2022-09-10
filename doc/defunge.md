# Defunge
The Funge++ debugger, known as defunge, can be run on any Befunge program by specifying the `-g` command line argument.

## Commands
Defunge supports the follow commands.  All arguments are optional, but must be given in the order shown.  Vector
arguments to commands are a comma separated list of coordinates inside parenthesis, starting with the X dimension:
`(x, y, z)`.  As many dimensions as necessary are allowed.

**run**, **continue**, **con**, **c**
: Run the IP being debugged.

**quit**, **q**
: Stop running the program and exit the debugger.

**step**, **stp**, **s**
: Execute the current instruction and break again.

**peek [*c* [*s*]]**, **p [*c* [*s*]]**
: Print element *c* from stack *s*.  Stack 0 is the top stack, element 1 is the top of the stack.  If *c* is not given,
print the entire stack stack.

**read *v***
: Print the cell at vector *v*.

**get [*v* [*s* [*d*]]]**, **g [*v* [*s* [*d*]]]**
: Print field vector *s* cells around the cell at vector *v* in the dimensions specified by vector *d*.

**list [*s* [*d*]]**, **l [*s* [*d*]]**
: Print the field vector *s* cells around the current IP in the dimensions specified by vector *d*.

**break *v***, **bp *v***
: Add a breakpoint on the cell at vector *v*.

**watch *v***, **wp *v***
: Add a write watchpoint on the cell at vector *v*.

**delta**, **dir**
: Print the delta of the current IP.

**storage**
: Print the storage offset of the current IP.

**position**, **pos**
: Print the position of the current IP.

**thread [*n*]**, **t [*n*]**
: Switch the debugger to the IP with ID *n*.  If *n* is not given, list all threads.

**backtrace**, **bt**
: Print the backtrace of the current IP.

**setdelta *v***
: Set the delta of the current IP to vector *v*.

**setpos *v***
: Set the postion of the current IP to vector *v*.

**universe**, **u**
: Print a list universe names.

## Fungespace
The **get** and **list** command display the current state of fungespace.  The center cell of the requested range is
underlined.

If terminal colors are available, the position of the current IP is highlight in green, the position of other IPs
are highlighted yellow.  The position of breakpoints are highlighted red, and watchpoints blue.
