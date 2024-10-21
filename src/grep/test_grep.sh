#!/bin/bash
TEMPLATE_FILE0="test_0_grep.txt"
TEMPLATE_FILE1="test_1_grep.txt"
TEMPLATE_FILE2="test_2_grep.txt"
TEMPLATE_FILE3="test_3_grep.txt"
TEMPLATE_FILE4="test_4_grep.txt"
TEMPLATE_FILE5="test_5_grep.txt"
TEMPLATE_FILE6="test_6_grep.txt"


SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"s ${TEMPLATE_FILE1}"
"abc ${TEMPLATE_FILE2}"
"10 ${TEMPLATE_FILE3}"
"VAR abc ${TEMPLATE_FILE4}"
"VAR abc ${TEMPLATE_FILE5}"
"-e while ${TEMPLATE_FILE2}"
)


declare -a extra=(
"-e '[0-9]' ${TEMPLATE_FILE1}"
"-n asdsad ${TEMPLATE_FILE2}"
"-n a ${TEMPLATE_FILE1}"
"-e 2554¬ßßå¡¬ÎÒÅÍ ${TEMPLATE_FILE2}"
"-l 123 ${TEMPLATE_FILE2} ${TEMPLATE_FILE4}"
"-e 123 ${TEMPLATE_FILE4}"
"-e 5 ${TEMPLATE_FILE3}"
"-c фывфыв ${TEMPLATE_FILE2}"
"-l 123 ${TEMPLATE_FILE4} ${TEMPLATE_FILE4}"
)


testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "$FAIL\033[0m/$SUCCESS\033[0m/$COUNTER success\033[0m grep $t"
    else
      (( FAIL++ ))
    echo "\033[31mFAIL\033[0m/\033[35m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"

    fi
    rm test_s21_grep.log test_sys_grep.log
}


for i in "${extra[@]}"
do
    var="-"
    testing $i
done



for var1 in e i v c l n
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"