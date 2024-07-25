#!/bin/bash
#to run using makefile
COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="test_cat/test_1_cat.txt"
VALGRIND_RESULT=""

for var in -b -e -n -t -v; do        #-E -T --number-nonblank --number --squeeze-blank
  for var2 in -b -e -n -t -v; do     #-E -T --number-nonblank --number --squeeze-blank
    for var3 in -b -e -n -t -v; do   #-E -T --number-nonblank --number --squeeze-blank
      for var4 in -b -e -n -t -v; do #-E -T --number-nonblank --number --squeeze-blank
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]; then
          TEST1="$var $var2 $var3 $var4 $TEST_FILE"
          echo "$TEST1"
          valgrind --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --log-file=valgrind.log \
            ./s21_cat $t >s21_cat.log
          VALGRIND_RESULT="$(cat valgrind.log)"
          if [[ "$VALGRIND_RESULT" = *"ERROR SUMMARY: 0 errors from 0 contexts"* ]]; then

          let "COUNTER_SUCCESS=COUNTER_SUCCESS+1"
          else
            echo "TEST FAILED: $TEST1"
          let "COUNTER_FAIL=COUNTER_FAIL+1"
          fi
          echo "$COUNTER_SUCCESS/$COUNTER_FAIL"
          rm -rf s21_cat.log cat.log
        fi
      done
    done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
