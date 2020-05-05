# C-Funge
C-Funge is Befunge interpreter originally written by Conlan Wesson in Java for a Programming Laguage Concepts course
with minimal functionality.  It has since been converted to C++, and an effort is underway to implement all Funge-98 instructions
and support N-dimensional Funge.

## Running
The C-Funge executable `funge` uses the first file argument to load the funge program.  The first character of the
file is an instruction at (0,0).  Each subsequent character is an instruction at X+1.  Both carriage returns and
line feed (as well as CRLF) are treated as Y+1 and reset X to zero.  Form feeds in the file represent Z+1 and reset
X and Y to zero.  Carriage returns and line feeds following a form feed are ignore (i.e FF may be own its own line).

### Arguments
`funge [ARGS] file`

`-std=[un93|une98|be93|be98|tre98]` Overrides the automatically detected dimensionality.

`-fconcurrent` `-fno-concurrent` Enable or disable use of split instruction `t`.

`-fexecute` `-fno-execute` Enable or disable use of execute instruction `=`.

`-ffilesystem` `-fno-filesystem` Enable or disable use of filesystem instructions `i` and `o`.

`-ftopo=[torus|lahey]` Set the topology.

`-fstrings=[multispace|sgml]` Set the string mode.

`-fcells=[char|int]` Set the cell size.

`-fthreads=[native|funge]` Set the threading mode.

### Exit Code
`funge` sets the program exit code to the value popped by the quit instruction `q` if encountered.  If `funge` fails
to load the funge program, the exit code is set to an error.  In any other case, the exit code is zero.

## Caveats
1. The split instruction `t` can use native threads rather than the tick mechanism described in the Funge-98
specification.  This mode can be enabled with `-fthreads=native`.
2. The dimensionality (up to 3D) is determined automatically based on the file contents.  This can be overriden with
the `-std` argument.

## Fingerprints
`BASE` I/O for numbers in other bases.

`BOOL` Boolean operators.

`BITW` Bitwise operators.

`HRTI` High Resolution Timer Interface.

`MODU` Modulo Arithmetic Extension.

`NFUN` N-Dimensional Funge.

`NULL` Null Fingerprint.

`ORTH` Orthogonal Easement Library.

`REFC` Referenced Cells Extension.

`ROMA` Roman Numerals.
