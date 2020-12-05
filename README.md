# Funge++
Funge++ is Befunge interpreter originally written by Conlan Wesson in Java for a Programming Laguage Concepts course
with minimal functionality.  It has since been converted to C++, and an effort is underway to implement all Funge-98 instructions
and support N-dimensional Funge.

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
`funge [ARGS] file`

`-std=[un93|une98|be93|be98|tre98]` Overrides the automatically detected dimensionality.

`-fconcurrent` `-fno-concurrent` Enable or disable use of split instruction `t`.

`-fexecute` `-fno-execute` Enable or disable use of execute instruction `=`.

`-ffilesystem` `-fno-filesystem` Enable or disable use of filesystem instructions `i` and `o`.

`-ftopo=[torus|lahey]` Set the topology.

`-fstrings=[multispace|sgml|c]` Set the string mode.

`-fcells=[char|int]` Set the cell size.

`-fthreads=[native|funge]` Set the threading mode.

`-l[fingerprint]` Load fingerprint at start as if loaded by `(`.

`-g` Start in debugger mode.

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

Standard instructions which operate on vectors (`g`, `p`, `x`, `?`), operate with vector lengths egual to the number of
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
`BASE` I/O for numbers in other bases.

`BITW` [Bitwise operators](doc/BITW.md).

`BOOL` Boolean operators.

`HRTI` High Resolution Timer Interface.

`MODE` Standard Modes.

`MODU` Modulo Arithmetic Extension.

`NFUN` [N-Dimensional Funge](doc/NFUN.md).

`NULL` Null Fingerprint.

`ORTH` Orthogonal Easement Library.

`REFC` Referenced Cells Extension.

`ROMA` Roman Numerals.

`TOYS` Standard Toys.
