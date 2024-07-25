#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
  "for test_grep/no_file.txt VAR"
  "for test_grep/test_7_grep.txt VAR"
  "-e for -e int test_grep/test_7_grep.txt  VAR"
  "-e for -e 'int' test_grep/test_7_grep.txt VAR"
  "-e regex -e 'print' test_grep/test_7_grep.txt VAR -f test_grep/test_ptrn_grep.txt"
  "-e while -e void test_grep/test_7_grep.txt VAR -f test_grep/test_ptrn_grep.txt"
)

declare -a extra=(
  "-n for test_grep/test_1_grep.txt test_grep/test_2_grep.txt VAR"
  "-n for test_grep/test_1_grep.txt VAR"
  "-n -e ^\} test_grep/test_1_grep.txt VAR"
  "-c -e /\ test_grep/test_1_grep.txt VAR"
  "-c ^int test_grep/test_1_grep.txt test_grep/test_2_grep.txt VAR"
  "-e ^int test_grep/test_1_grep.txt VAR"
  "-e VAR"
  "-echar test_grep/test_1_grep.txt test_grep/test_2_grep.txt VAR"
  "-v test_grep/test_1_grep.txt -e ank VAR"
  "-l for test_grep/test_1_grep.txt test_grep/test_2_grep.txt VAR"
  "-o -e int test_grep/test_4_grep.txt VAR"
  "-e = -e out test_grep/test_5_grep.txt VAR"
  "-l for no_file.txt test_grep/test_2_grep.txt VAR"
  "-e ing -e as -e the -e not -e is test_grep/test_6_grep.txt VAR"
  "-f test_grep/test_3_grep.txt test_grep/test_5_grep.txt VAR"
)

testing() {
  arguments_string=$(echo "$@" | sed "s|VAR|$var|")
  ./s21_grep $arguments_string > s21_grep.log
  grep $arguments_string > grep.log
  DIFF_RES="$(diff -s s21_grep.log grep.log)"
  ((COUNTER++))
  if [ "$DIFF_RES" == "Files s21_grep.log and grep.log are identical" ]; then
    ((SUCCESS++))
    echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $arguments_string"
  else
    ((FAIL++))
    echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $arguments_string"
  fi
  echo
  rm s21_grep.log grep.log
}

#специфические тесты
for i in "${extra[@]}"; do
  testing $i
done

#1 параметр
for var1 in v n c l h o s i; do
  for i in "${tests[@]}"; do
    var="-$var1"
    testing $i
  done
done

#2 параметра
for var1 in "-e ^double" "-e float" "-e char"; do
  for var2 in v c l n h o; do
    for i in "${tests[@]}"; do
      var="$var1 -$var2"
      testing $i
    done
  done
done

# 2 параметра
for var1 in v c l n h o i
do
    for var2 in v c l n h o i
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

## 2 сдвоенных параметра
for var1 in v c l n h o i
do
    for var2 in v c l n h o i
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                testing $i
            done
        fi
    done
done
echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
