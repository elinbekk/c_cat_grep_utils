#!/bin/bash
#to run using makefile
COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="test_cat/test_1_cat.txt"

for var in -b -e -n -s -t -v; do #-E -T --number-nonblank --number --squeeze-blank
  TEST1="$var $TEST_FILE"
  echo "$TEST1"
  ./s21_cat $TEST1 >s21_cat.log
  cat $TEST1 >cat.log
  DIFF_RES="$(diff -s s21_cat.log cat.log)"
          if [[ "$DIFF_RES" = *"are identical"* ]]; then
    ((COUNTER_SUCCESS++))
  else
    ((COUNTER_FAIL++))
  fi
  rm -rf s21_cat.log cat.log
done
#
for var in -b -e -n -s -t -v; do    #-E -T --number-nonblank --number --squeeze-blank
  for var2 in -b -e -n -s -t -v; do #-E -T --number-nonblank --number --squeeze-blank
    if [ $var != $var2 ]; then
      TEST1="$var $var2 $TEST_FILE"
      echo "$TEST1"
      ./s21_cat $TEST1 >s21_cat.log
      cat $TEST1 >cat.log
      DIFF_RES="$(diff -s s21_cat.log cat.log)"
          if [[ "$DIFF_RES" = *"are identical"* ]]; then
        ((COUNTER_SUCCESS++))
      else
        echo $DIFF_RES
        echo "TEST FAILED: $TEST1"
        ((COUNTER_FAIL++))
      fi
      rm -rf s21_cat.log cat.log
    fi
  done
done
#
for var in -b -e -n -s -t -v; do      #-E -T --number-nonblank --number --squeeze-blank
  for var2 in -b -e -n -s -t -v; do   #-E -T --number-nonblank --number --squeeze-blank
    for var3 in -b -e -n -s -t -v; do #-E -T --number-nonblank --number --squeeze-blank
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]; then
        TEST1="$var $var2 $var3 $TEST_FILE"
        echo "$TEST1"
        ./s21_cat $TEST1 >s21_cat.log
        cat $TEST1 >cat.log
        DIFF_RES="$(diff -s s21_cat.log cat.log)"
          if [[ "$DIFF_RES" = *"are identical"* ]]; then
          ((COUNTER_SUCCESS++))
        else
          echo $DIFF_RES
          ((COUNTER_FAIL++))
        fi
        rm -rf s21_cat.log cat.log

      fi
    done
  done
done

for var in -b -e -n -s -t -v; do        #-E -T --number-nonblank --number --squeeze-blank
  for var2 in -b -e -n -s -t -v; do     #-E -T --number-nonblank --number --squeeze-blank
    for var3 in -b -e -n -s -t -v; do   #-E -T --number-nonblank --number --squeeze-blank
      for var4 in -b -e -n -s -t -v; do #-E -T --number-nonblank --number --squeeze-blank
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]; then
          TEST1="$var $var2 $var3 $var4 $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 >s21_cat.log
          cat $TEST1 >cat.log

          DIFF_RES="$(diff -s s21_cat.log cat.log)"
          if [[ "$DIFF_RES" = *"are identical"* ]]; then
            ((COUNTER_SUCCESS++))
          else
            echo "TEST FAILED: $TEST1"
            ((COUNTER_FAIL++))
          fi
          rm -rf s21_cat.log cat.log
        fi
      done
    done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
