% FUNGE++(1) funge v1
% Conlan Wesson
% January 2022

# NAME
funge - N-dimensional Funge-98 interpreter

# SYNOPSIS
**funge** [*OPTIONS*] file [*YARGS*]

# DESCRIPTION
**funge** Funge-98 interpreter with N-Dimensional Funge support and debugger
written in C++. 

# OPTIONS
**-std=[une93|une98|be93|be98|tre98|fish|sfish]**
: Overrides the automatically detected dimensionality.

**-fconcurrent**, **-fno-concurrent**
: Enable or disable use of split instruction `t`.

**-fexecute**, **-fno-execute**
: Enable or disable use of execute instruction `=`.

**-ffilesystem**, **-fno-filesystem**
: Enable or disable use of filesystem instructions `i` and `o`.

**-finvert-hl**
: Invert the `h` and `l` instructions.

**-ftopo=[torus|lahey]**
: Set the topology.

**-fstrings=[multispace|sgml|c]**
: Set the string mode.

**-fcells=[char|int]**
: Set the cell size.

**-fthreads=[native|funge]**
: Set the threading mode.

**-l[fingerprint]**
: Load fingerprint at start.  This does not push the fingerprint ID to the
stack.

**-g**
: Start in debugger mode.

# FILE
If the file path ends in **.beq** the file is interpretted as a BeQunge
file.  Load a BeQunge file imples **-lNFUN**.

If the file path ends in **.fl** the file is interpretted as a funge-lib
file.

If the file path ends in **.fmv** the file is interpretted as a Funge Multiverse
file.  Each line of an FMV file consists of a path to a Funge file to load as a
universe, followed by yargs for that universe.  The yargs specified in the FMV
file are append to the yargs specified on the command line.

# YARGS
Any arguments following the Funge file are passed to the Funge program. These
arguments are available to the program using the `y` instruction.

# EXIT VALUES
**funge** sets the program exit code to the value popped by the quit instruction
`q` of the prime universe if encountered.  If **funge** fails to load the funge
program, the exit code is set to an error.  In any other case, the exit code is
zero.

**0**
: Success

**EINVAL**
: Invalid options

**EIO**
: Error opening file

# BUGS
See https://github.com/cwesson/funge-plus-plus/issues

# COPYRIGHT
Copyright (c) 2022 Conlan Wesson
