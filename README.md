# Funge++
Funge++ is Befunge interpreter originally written by Conlan Wesson in Java for a Programming Language Concepts course
with minimal functionality.  It has since been converted to C++, supports all Funge-98 instructions and N-dimensional
Funge.  The Funge++ handprint is 0x464E2B2B (`FN++`).

## Running
The Funge++ executable `funge` uses the first file argument to load the funge program.  The first character of the
file is an instruction at (0,0).  Each subsequent character is an instruction at X+1.  Both carriage returns and
line feed (as well as CRLF) are treated as Y+1 and reset X to zero.  Form feeds in the file represent Z+1 and reset
X and Y to zero.  Carriage returns and line feeds following a form feed are ignored (i.e FF may be own its own line).

See the [man page](doc/man.md) for more information.

### Higher Dimensions
Vertical Tabs in the file represent 4D+1 and reset X, Y, and Z to zero.  Carriage returns and line feeds
following a vertical tab are ignored.  This is not part of the Funge-98 specification, but provides a simple way to
create 4-dimensional funges.

Trefunge frunges can be loaded as funge-lib formatted `.fl` files.

Higher dimension funges can be loaded as BeQunge formatted `.beq` files.  Loading a `.beq` file implies `-lNFUN`.

## Features

### Native Threads
The split instruction `t` can use native threads rather than the tick mechanism described in the Funge-98
specification.  This mode can be enabled with `-fthreads=native`.

### Auto-Dimensions
The dimensionality (up to 4D) is determined automatically based on the file contents.  This can be overriden with
the `-std` argument.  Funge-lib formatted files are 3D.  Higher dimensions can be determined automatically from BeQunge
formatted files with or without the `Dimensions` directive.

Standard instructions which operate on vectors (`g`, `p`, `x`, `?`), operate with vector lengths equal to the number of
dimensions detected.  This enables those instructions to function in a standardized way in higher-dimension funges.  For
example, in 4D mode, `?` will change the delta to one of 8 possible directions, while `x` can move in all possible
directions.

### C-Style Strings
C-style strings can be enabled with `-fstrings=c`.  In this mode, backslashes in strings are not pused to the stack,
instead, it and the following character are interpretted as an escape sequence.  This happens in one tick.  In addition
to special characters, this allows quotes and ANSI escape codes in strings.

### 64-bit
Funge++ stack and funge-space are 64-bit values.  For that reason, FPDP numbers use a single stack cell, and LONG
numbers are 128-bit.

## Errata
### High/Low
The Funge-98 specification is inconsistent about the delta of the `h` and `l`  instructions (https://github.com/catseye/Funge-98/issues/10).
Funge++ uses thedefinition in the program flow section, that is `h` is "delta <- (0,0,1)" and `l` is
"delta <- (0,0,-1)".  This makes it compatible with BeQunge and Rc/Funge-98.  The `-finvert-hl` argument flips this
behavior.

## Fingerprints
Funge++ supports the following fingerprints.  These can either be loaded at runtime by the `(` instruction, or by
specifying the `-l` command line argument.

Funge++ also supports dynamic Funge fingerprints.  When a fingerprint is loaded, Funge++ will search for funge-lib files
in the `fing` directory before loading a built-in fingerprint.  This allows users to override the built-in fingerprints.
Instructions from dynamic Funges run with the same stack as the IP that called them.

`BASE` [I/O for numbers in other bases](http://www.rcfunge98.com/rcfunge2_manual.html#BASE).

`BITW` [Bitwise Operators](doc/BITW.md).

`BOOL` [Boolean Operators](http://www.rcfunge98.com/rcfunge2_manual.html#BOOL).

`CPLI` [Complex Integer Extension](http://www.rcfunge98.com/rcfunge2_manual.html#CPLI).

`DBUG` [Debugger Control](doc/DBUG.md).

`DIRF` [Directory Functions](http://www.rcfunge98.com/rcfunge2_manual.html#DIRF).

`FING` [Operate on single fingerprint semantics](http://www.rcfunge98.com/rcfunge2_manual.html#FING).

`FIXP` [Fixed point math functions](http://www.rcfunge98.com/rcfunge2_manual.html#FIXP).

`FPDP` [Double precision floating point](http://www.rcfunge98.com/rcfunge2_manual.html#FPDP).

`FPRT` [Formatted print](http://www.rcfunge98.com/rcfunge2_manual.html#FPRT).

`FPSP` [Single precision floating point](http://www.rcfunge98.com/rcfunge2_manual.html#FPSP).

`FRTH` [Some common forth commands](http://www.rcfunge98.com/rcfunge2_manual.html#FRTH).

`HRTI` [High Resolution Timer Interface](https://github.com/catseye/Funge-98/blob/master/library/HRTI.markdown).

`JSTR` [3d string vectors](http://www.rcfunge98.com/rcfunge2_manual.html#JSTR).

`LONG` [Long Integers](http://www.rcfunge98.com/rcfunge2_manual.html#LONG).

`MODE` [Standard Modes](https://github.com/catseye/Funge-98/blob/master/library/MODE.markdown).

`MODU` [Modulo Arithmetic Extension](https://github.com/catseye/Funge-98/blob/master/library/MODU.markdown).

`MVRS` [Multiverse extension](http://www.rcfunge98.com/rcfunge2_manual.html#MVRS).

`NFUN` [N-Dimensional Funge](doc/NFUN.md).

`NULL` [Null Fingerprint](https://github.com/catseye/Funge-98/blob/master/library/NULL.markdown).

`ORTH` [Orthogonal Easement Library](https://github.com/catseye/Funge-98/blob/master/library/ORTH.markdown).

`PERL` [Generic Interface to the Perl Language](https://github.com/catseye/Funge-98/blob/master/library/PERL.markdown).

`REFC` [Referenced Cells Extension](https://github.com/catseye/Funge-98/blob/master/library/REFC.markdown).

`ROMA` [Roman Numerals](doc/ROMA.md).

`STRN` [String functions](http://www.rcfunge98.com/rcfunge2_manual.html#STRN).

`SUBR` [Subroutine extension](http://www.rcfunge98.com/rcfunge2_manual.html#SUBR).

`TERM` [Terminal extension](http://www.rcfunge98.com/rcfunge2_manual.html#TERM).

`TOYS` [Standard Toys](https://github.com/catseye/Funge-98/blob/master/library/TOYS.markdown).

## Debugger
The Funge++ debugger, known as defunge, can be run on any Befunge program by specifying the `-g` command line argument.

See [Defunge](doc/defunge.md) for details.