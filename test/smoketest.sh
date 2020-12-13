#!/usr/bin/bash

function assert_equal() {
    code=$?
    if [ $code != 0 ]; then
        echo Failed to execute test $1 >&2
        exit $code
    fi
    if [ "$2" != "$3" ]; then
        echo Failed test $1: \(\"$2\" != \"$3\"\) >&2
        exit -1
    fi
}

function test_simple() {
    echo TEST $1
    res=`timeout 10 ./bin/funge $1`
    code=$?
    if [ -z "$3" ]; then
        expect=0
    else
        expect=$code
    fi
    assert_equal $1 $code $expect
    assert_equal $1 "$res" "$2"
}

function test_befunge() {
    echo TEST $1
    res=`timeout 10 ./bin/funge -std=be98 $1`
    code=$?
    if [ -z "$3" ]; then
        expect=0
    else
        expect=$code
    fi
    assert_equal $1 $code $expect
    assert_equal $1 "$res" "$2"
}

function test_diff() {
    echo TEST $@
    diff $@
    code=$?
    assert_equal $1 $code 0
}

function test_mycology() {
    echo TEST $1
    cd test/Mycology
    timeout 30 ../../bin/funge -std=be98 mycology.b98 | tee ../../mycology.log | grep BAD
    grep BAD mycology.log
    code=$?
    rm mycotmp*.tmp
    if [ -z "$2" ]; then
        expect=0
    else
        expect=$code
    fi
    assert_equal $1 $code $expect
}

# Funge-93 Tests
test_simple test/test_stop.bf ""
test_simple test/test_outint.bf "6 5 4 3 2 1 "
test_simple test/test_outchar.bf "Hello World!"
test_simple test/test_arith.bf "2 3 5 8 13 21 "
test_simple test/test_flow.bf "4 3 2 1 0 "
test_simple test/test_wrap.bf "1 2 3 4 5 "
test_simple test/test_trampoline.bf "3 2 "
test_simple test/test_dup.bf "5 4 3 3 2 1 "
test_simple test/test_vif.bf "3 2 1 "
test_simple test/test_hif.bf "3 2 1 "
test_simple test/test_not.bf "1 2 "
test_simple test/test_gt.bf "1 0 "
test_simple test/test_pop.bf "3 1 0 "
test_simple test/test_swap.bf "2 3 1 "
test_simple test/test_get.bf "F1 2 "
test_simple test/test_put.bf "2 1 "
# Funge-98 Tests
test_simple test/test_quit.bf "3 2 1 " 4
test_simple test/test_clear.bf "3 2 1 0 0 0 "
test_simple test/test_jump.bf "2 1 0 0 0 0 0 3 "
test_simple test/test_iter.bf "6 5 4 3 2 1 "
test_simple test/test_hex.bf "15 14 13 12 11 10 "
test_simple test/test_turn.bf "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 "
test_simple test/test_comp.bf "3 2 1 "
test_simple test/test_fetch.bf "2 v 1 ^<"
test_simple test/test_store.bf "3 "
test_befunge test/quine.bf `cat test/quine.bf`
test_simple test/fizzbuzz.bf "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16 17 Fizz 19 Buzz Fizz 22 23 Fizz Buzz 26 Fizz 28 29 FizzBuzz 31 32 Fizz 34 Buzz Fizz 37 38 Fizz Buzz 41 Fizz 43 44 FizzBuzz 46 47 Fizz 49 Buzz Fizz 52 53 Fizz Buzz 56 Fizz 58 59 FizzBuzz 61 62 Fizz 64 Buzz Fizz 67 68 Fizz Buzz 71 Fizz 73 74 FizzBuzz 76 77 Fizz 79 Buzz Fizz 82 83 Fizz Buzz 86 Fizz 88 89 FizzBuzz 91 92 Fizz 94 Buzz Fizz 97 98 Fizz Buzz "
test_simple test/test_thread.bf "8 7 6 5 4 3 2 1 "
test_simple test/test_3d.bf "1 2 3 4 5 6 7 8 "
test_simple test/test_stackstack.bf "5 4 3 9 8 7 2 "
test_simple test/test_under.bf "5 4 3 1 2 0 0 "
test_simple test/test_execute.bf "Hello World!" 1
test_simple test/test_in.bf "3 2 1 5 4 6 "
test_diff test/input.txt test/output.txt
# BeQunge Tests
test_simple test/example3d.beq "Hello World"
test_simple test/example5d.beq "Hello World"
test_simple test/hello3d.beq "Hello World!"
# Fingerprint Tests
test_simple test/test_roma.bf "1000 500 100 50 10 5 1 "
test_simple test/test_bool.bf "1 2 "
test_simple test/test_nfun.bf "Funge++ in the Forth Dimension!"
test_simple test/test_television.b98 "9 8 7 6 5 4 3 2 1 0 "
test_simple test/test_tumbler.b98 "0 "
test_simple test/test_fishhook.b98 "1 2 3 4 5 6 "
test_simple test/test_boulder.b98 "1 2 3 4 5 6 "
test_simple test/test_bracelet.b98 "1 2 3 1 2 3 "
test_simple test/test_chicane.b98 "6 5 4 3 2 1 "
test_simple test/test_perl.b98 "78 243"
# Mycology Tests
test_simple test/Mycology/sanity.bf "0 1 2 3 4 5 6 7 8 9 "
test_mycology mycology.b98 15
