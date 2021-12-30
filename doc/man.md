% FUNGE++(1) funge v1
% Conlan Wesson
% December 2021

# NAME
funge - N-dimensional Funge-98 interpreter

# SYNOPSIS
**funge** [*OPTIONS*] file [*YARGS*]

# DESCRIPTION
**funge** Funge-98 interpreter with N-Dimensional Funge support and debugger written in C++. 

# OPTIONS
**-std=[un93|une98|be93|be98|tre98]**
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
: Load fingerprint at start.  This does not push the fingerprint ID to the stack.

**-g**
: Start in debugger mode.

# YARGS
Any arguments following the Funge file are passed to the Funge program. These arguments are available to the program using the `y` instruction.

# EXIT VALUES
**funge** sets the program exit code to the value popped by the quit instruction `q` if encountered.  If **funge** fails
to load the funge program, the exit code is set to an error.  In any other case, the exit code is zero.

**0**
: Success

**EINVAL**
: Invalid options

**EIO**
: Error opening file

# COPYRIGHT
Copyright (c) 2021 Conlan Wesson
