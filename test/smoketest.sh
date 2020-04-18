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
    res=`./bin/funge $1`
    code=$?
    if [ -z "$3" ]; then
        expect=0
    else
        expect=$code
    fi
    assert_equal $1 $code $expect
    assert_equal $1 "$res" "$2"
}

# Funge-93 Tests
test_simple test/test_stop.bf ""
test_simple test/test_outint.bf "6 5 4 3 2 1 "
test_simple test/test_outchar.bf "Hello!"
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
test_simple test/quine.bf `cat test/quine.bf`
test_simple test/test_thread.bf "6 5 4 3 2 1 "
test_simple test/test_3d.bf "1 2 3 4 5 6 7 8 "
