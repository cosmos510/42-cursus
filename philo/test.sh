#!/bin/bash

PHILO="./philo"

run_test() {
    local desc="$1"
    local cmd="$2"
    local logfile="$3"
    local sleep_time="${4:-3}"
    local expect_die="$5"
    local must_finish="$6"

    echo -e "\n🧪 $desc"
    eval "$cmd > $logfile &"
    pid=$!
    sleep "$sleep_time"
    if [ "$must_finish" = "yes" ]; then
        wait $pid
    else
        kill $pid 2>/dev/null
    fi

    if grep -q "died" "$logfile"; then
        if [ "$expect_die" = "yes" ]; then
            echo "✅ Success: death detected"
        else
            echo "❌ Failed: unexpected death"
        fi
    else
        if [ "$expect_die" = "yes" ]; then
            echo "❌ Failed: expected death not detected"
        else
            echo "✅ Success: no death detected"
        fi
    fi
}

# Test 1: Normal case
run_test "Test 1: 5 philosophers, no death expected" \
         "$PHILO 5 800 200 200" \
         "test1.log" 3 "no" "no"

# Test 2: Must-eat count, should stop automatically
run_test "Test 2: 3 philosophers, each eats 3 times, program should exit" \
         "$PHILO 3 800 200 200 3" \
         "test2.log" 4 "no" "yes"

# Test 3: Death expected due to tight timing
run_test "Test 3: 2 philosophers, death expected" \
         "$PHILO 2 310 200 200" \
         "test3.log" 3 "yes" "no"

# Test 4: Race condition, high pressure, possible death
run_test "Test 4: 5 philosophers, time_to_die = 200ms, stress test" \
         "$PHILO 5 200 100 100" \
         "test4.log" 4 "yes" "no"

# Test 5: 1 philosopher, can't eat, will die
run_test "Test 5: 1 philosopher, should die" \
         "$PHILO 1 800 200 200" \
         "test5.log" 2 "yes" "yes"

# Test 6: Large number of philosophers
run_test "Test 6: 200 philosophers, no death expected" \
         "$PHILO 200 1000 100 100" \
         "test6.log" 5 "no" "no"

# Test 7: Invalid argument count
echo -e "\n🧪 Test 7: Invalid args (too few)"
$PHILO 4 800 200 > test7.log 2>&1
if grep -qi "error\|usage" test7.log; then
    echo "✅ Success: error message shown for invalid args"
else
    echo "❌ Failed: missing argument not handled properly"
fi

# Test 8: Invalid arguments (negative number)
echo -e "\n🧪 Test 8: Invalid args (negative number)"
$PHILO -5 800 200 200 > test8.log 2>&1
if grep -qi "error\|invalid\|usage" test8.log; then
    echo "✅ Success: negative argument rejected"
else
    echo "❌ Failed: negative number not handled"
fi

# Test 9: Edge case (eat time > die time, always dies)
run_test "Test 9: Eating takes longer than time_to_die, death expected" \
         "$PHILO 3 150 200 100" \
         "test9.log" 3 "yes" "no"

# Test 10: Zero as argument (should error)
echo -e "\n🧪 Test 10: Zero as argument"
$PHILO 0 800 200 200 > test10.log 2>&1
if grep -qi "error\|invalid\|usage" test10.log; then
    echo "✅ Success: zero rejected"
else
    echo "❌ Failed: zero not handled"
fi

# Test 11: Letter in argument (should error)
echo -e "\n🧪 Test 11: Letter in argument"
$PHILO 4 300o 200 200 > test11.log 2>&1
if grep -qi "error\|invalid\|usage" test11.log; then
    echo "✅ Success: letter in argument rejected"
else
    echo "❌ Failed: letter in argument not handled"
fi

echo -e "\n📂 Logs saved from test1.log to test11.log"