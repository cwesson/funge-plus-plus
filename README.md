# Funge++
Funge++ is Befunge interpreter originally written by Conlan Wesson in Java for a Programming Language Concepts course
with minimal functionality.  It has since been converted to C++, and an effort is underway to implement all Funge-98
instructions and support N-dimensional Funge.  The Funge++ handprint is 0x464E2B2B (`FN++`).

## Running
The Funge++ executable `funge` uses the first file argument to load the funge program.  The first character of the
file is an instruction at (0,0).  Each subsequent character is an instruction at X+1.  Both carriage returns and
line feed (as well as CRLF) are treated as Y+1 and reset X to zero.  Form feeds in the file represent Z+1 and reset
X and Y to zero.  Carriage returns and line feeds following a form feed are ignored (i.e FF may be own its own line).

### Higher Dimensions
Vertical Tabs in the file represent 4D+1 and reset X, Y, and Z to zero.  Carriage returns and line feeds
following a vertical tab are ignored.  This is not part of the Funge-98 specification, but provides a simple way to
create 4-dimensional funges.

Higher dimension funges can be loaded as BeQunge formatted files can be loaded as `.beq` files.  Loading a `.beq` file
implies `-lNFUN`.

### Arguments
`funge [ARGS] file [YARGS]`

#### ARGS:
`-std=[un93|une98|be93|be98|tre98]` Overrides the automatically detected dimensionality.

`-fconcurrent` `-fno-concurrent` Enable or disable use of split instruction `t`.

`-fexecute` `-fno-execute` Enable or disable use of execute instruction `=`.

`-ffilesystem` `-fno-filesystem` Enable or disable use of filesystem instructions `i` and `o`.

`-ftopo=[torus|lahey]` Set the topology.

`-fstrings=[multispace|sgml|c]` Set the string mode.

`-fcells=[char|int]` Set the cell size.

`-fthreads=[native|funge]` Set the threading mode.

`-l[fingerprint]` Load fingerprint at start.  This does not push the fingerprint ID to the stack.

`-g` Start in [debugger mode](#debugger).

#### YARGS:
Any arguments following the Befunge file are passed to the Befunge program.  These arguments are available to the
program using the `y` instruction.

### Exit Code
`funge` sets the program exit code to the value popped by the quit instruction `q` if encountered.  If `funge` fails
to load the funge program, the exit code is set to an error.  In any other case, the exit code is zero.

## Features

### Native Threads
The split instruction `t` can use native threads rather than the tick mechanism described in the Funge-98
specification.  This mode can be enabled with `-fthreads=native`.

### Auto-Dimensions
The dimensionality (up to 4D) is determined automatically based on the file contents.  This can be overriden with
the `-std` argument.  Higher dimensions can be determined automatically from BeQunge formatted files with or without
the `Dimensions` directive.

Standard instructions which operate on vectors (`g`, `p`, `x`, `?`), operate with vector lengths equal to the number of
dimensions detected.  This enables those instructions to function in a standardized way in higher-dimension funges.  For
example, in 4D mode, `?` will change the delta to one of 8 possible directions, while `x` can move in all possible
directions.

### C-Style Strings
C-style strings can be enabled with `-fstrings=c`.  In this mode, backslashes in strings are not pused to the stack,
instead, it and the following character are interpretted as an escape sequence.  This happens in one tick.  In addition
to special characters, this allows quotes and ANSI escape codes in strings.

## Errata
### High/Low
The Funge-98 specification is inconsistent about the delta of the `h` and `l`  instructions.  Funge++ uses the
definition in the program flow section, that is `h` is "delta <- (0,0,1)" and `l` is "delta <- (0,0,-1)".  This makes
it compatible with BeQunge and Rc/Funge-98.

## Fingerprints
Funge++ supports the following fingerprints.  These can either be loaded at runtime by the '(' instruction, or by
specifying the `-l` command line argument.

`BASE` [I/O for numbers in other bases](http://www.rcfunge98.com/rcfunge2_manual.html#BASE).

`BITW` [Bitwise Operators](doc/BITW.md).

`BOOL` [Boolean Operators](http://www.rcfunge98.com/rcfunge2_manual.html#BOOL).

`CPLI` [Complex Integer Extension](http://www.rcfunge98.com/rcfunge2_manual.html#CPLI).

`DBUG` [Debugger Control](doc/DBUG.md).

`FIXP` [Fixed point math functions](http://www.rcfunge98.com/rcfunge2_manual.html#FIXP).

`FPDP` [Double precision floating point](http://www.rcfunge98.com/rcfunge2_manual.html#FPDP).

`FPRT` [Formatted print](http://www.rcfunge98.com/rcfunge2_manual.html#FPRT).

`FPSP` [Single precision floating point](http://www.rcfunge98.com/rcfunge2_manual.html#FPSP).

`FRTH` [Some common forth commands](http://www.rcfunge98.com/rcfunge2_manual.html#FRTH).

`HRTI` [High Resolution Timer Interface](https://github.com/catseye/Funge-98/blob/master/library/HRTI.markdown).

`MODE` [Standard Modes](https://github.com/catseye/Funge-98/blob/master/library/MODE.markdown).

`MODU` [Modulo Arithmetic Extension](https://github.com/catseye/Funge-98/blob/master/library/MODU.markdown).

`NFUN` [N-Dimensional Funge](doc/NFUN.md).

`NULL` [Null Fingerprint](https://github.com/catseye/Funge-98/blob/master/library/NULL.markdown).

`ORTH` [Orthogonal Easement Library](https://github.com/catseye/Funge-98/blob/master/library/ORTH.markdown).

`PERL` [Generic Interface to the Perl Language](https://github.com/catseye/Funge-98/blob/master/library/PERL.markdown).

`REFC` [Referenced Cells Extension](https://github.com/catseye/Funge-98/blob/master/library/REFC.markdown).

`ROMA` [Roman Numerals](https://github.com/catseye/Funge-98/blob/master/library/ROMA.markdown).

`TERM` [Terminal extension](http://www.rcfunge98.com/rcfunge2_manual.html#TERM).

`TOYS` [Standard Toys](https://github.com/catseye/Funge-98/blob/master/library/TOYS.markdown).

## Debugger
The Funge++ debugger, known as defunge, can be run on any Befunge program by specifying the `-g` command line argument.

### Commands
Defunge supports the follow commands.  All arguments are optional, but must be given in the order shown.  Vector
arguments to commands are a comma separated list of coordinates inside parenthesis, starting with the X dimension:
`(x, y, z)`.  As many dimensions as necessary are allowed.

*run*
Run the IP being debugged.

*quit*
Stop running the program and exit the debugger.

*step*
Execute the current instruction and break again.

*peek c s*
Print element *c* from stack *s*.  Stack 0 is the top stack, element 1 is the top of the stack.  If *c* is 0,
print the entire stack stack.

*read v*
Print the cell at vector *v*.

*get v s d*
Print field vector *s* cells around the cell at vector *v* in the dimensions specified by vector *d*.

*list s d*
Print the field vector *s* cells around the current IP in the dimensions specified by vector *d*.

*break v*
Add a breakpoint on the cell at vector *v*.

*watch v*
Add a write watchpoint on the cell at vector *v*.

*delta*
Print the delta of the current IP.

*storage*
Print the storage offset of the current IP.

*position*
Print the position of the current IP.

*thread n*
Switch the debugger to the IP with ID *n*.

*backtrace*
Print the backtrace of the current IP.

*setdelta v*
Set the delta of the current IP to vector *v*.

*setpos v*
Set the postion of the current IP to vector *v*.

