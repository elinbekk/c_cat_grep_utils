#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""
declare -a tests=(
  "s test_grep/test_0_grep.txt test_grep/file2.txt VAR"
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
  "-c -e ^int test_grep/test_1_grep.txt test_grep/test_2_grep.txt VAR"
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
  t=$(echo $@ | sed "s|VAR|$var|")
  valgrind --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --log-file=valgrind.log \
    ./s21_grep $t > s21_grep.log
  cat valgrind.log
  #    (( COUNTER++ ))
  #    echo $DIFF_RES
  #    if [ "$DIFF_RES" == "Files s21_grep.log and grep.log are identical" ]
  #    then
  #      (( SUCCESS++ ))
  #      echo "$FAILm$SUCCESS$COUNTER success grep $t"
  #    else
  #      (( FAIL++ ))
  #      echo "$FAIL $SUCCESS $COUNTER fail grep $t"
  #    fi
  #    rm -rf s21_grep.log grep.log
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
