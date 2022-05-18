#i! /bin/bash

public_test_folder="PA2-data-public"
private_test_folder="PA2-data-hidden"
tmp_out_folder="temp"
filename=""
filename_without_ext=""
execution_cmd=""
fail_count=0
time_out=0
is_py=0
is_java=0
is_cpp=0
deduction=0

# Message constants
compile_failure_msg="[ERROR] Compilation failed. Please check!!"
success_msg="Success"
compile_stage_msg="-------Compiling the code-------"

# Exit code
# 1 - General failures
# 2 - Compilation failed
# 3 - Test failed

print_usage() {
  printf "\n%s\n\n" "
  -- Usage: bash test_aoa_pa2.sh <Program type> <Filename>

    Program type - JAVA/PYTHON/CPP

    Filename - Name of the file name that has to be tested.

  -- Example:

    bash test_aoa_pa2.sh JAVA PA1.java"
}

compile_cpp() {
  g++ -std=c++11 -o $filename_without_ext ${filename}
  ret_val=$?
  if [ $ret_val -ne 0 ]
  then
    printf "\n%s\n\n" "${compile_failure_msg}"
    exit 2
  fi
  printf "\n%s\n" "${success_msg}"
}

compile_java() {
  javac ${filename}
  ret_val=$?
  if [ $ret_val -ne 0 ]
  then
    printf "\n%s\n\n" "${compile_failure_msg}"
    exit 2
  fi
  printf "\n%s\n" "${success_msg}"
}

run_test() {
  input_file=$1
  out_file=$2

  printf "\n%s" "Executing:
        $execution_cmd < $input_file > ${tmp_out_folder}/output$i.txt"

  # Calculate the execution time
  start_time=`date +%s`
  $execution_cmd < $input_file > "${tmp_out_folder}/output$i.txt"
  if [ $? -ne 0 ]
  then
    printf "\n%s\n" "[ERROR] Execution Failed with error."
    let fail_count=fail_count+1
    return 2
  fi
  end_time=`date +%s`
  printf "\n%s" "Execution time:
        `expr $end_time - $start_time` s."

  run_time=`expr $end_time - $start_time`

  failed=0
  timed=0

  if [ $is_py -eq 1 ] && [ $run_time -gt 15 ]
  then
      timed=1
      time_out=1
  fi

  if [ $is_java -eq 1 ] && [ $run_time -gt 10 ]
  then
      timed=1
      time_out=1
  fi

  if [ $is_cpp -eq 1 ] && [ $run_time -gt 2 ]
  then
      timed=1
      time_out=1
  fi

  sed -i.bak 's/^M//g' "${tmp_out_folder}/output$i.txt"
  
  len_diff=`diff <(head -n 1 ${out_file}) <(head -n 1 "${tmp_out_folder}/output$i.txt")`
  if [ ! -z "$len_diff" ]
  then
      failed=1
      let fail_count=fail_count+1
      let deduction=deduction+5
      printf "\n%s" "[FAILED] Incorrect subsequence length for ${input_file}.
          Use 'diff <(head -n 1 ${out_file}) <(head -n 1 ${tmp_out_folder}/output$i.txt)' to know the diff"
  fi

  check_status=`python3 LCS_checker.py $input_file $out_file "${tmp_out_folder}/output$i.txt" | grep "1 Correct" | wc -l`
  if [ $check_status -ne 1 ]
  then
      failed=1
      let fail_count=fail_count+1
      let deduction=deduction+5
      printf "\n\n%s\n" "[FAILED] Output subsequence is incorrect for ${input_file}.
         Use 'python3 LCS_checker.py $input_file $out_file ${tmp_out_folder}/output$i.txt' to know the failure reason"

  fi

  if [ $failed -eq 0 ] && [ $timed -ne 0 ]
  then
      let deduction=deduction+3
  fi 
  return 0
}

run_private_test() {
  for ((i = 6; i <= 10; i++))
  do
    printf "\n%s" "$i.) Testing File: ${private_test_folder}/input$i.txt"
    run_test "${private_test_folder}/input$i.txt" "${private_test_folder}/output$i.txt"
    printf "\n%s" "---------------------"
  done
}

run_public_test() {
  for ((i = 1; i <= 5; i++))
  do
    printf "\n%s" "$i.) Testing File: ${public_test_folder}/input$i.txt"
    run_test "${public_test_folder}/input$i.txt" "${public_test_folder}/output$i.txt"
    printf "\n%s" "---------------------"
  done
}

main() {

  if [ $# -lt 2 ]
  then
    printf "\n%s\n" "[ERROR] Invalid arguments."
    print_usage
    exit 1
  fi

  if [ ! -f "$2" ]
  then
    printf "\n%s\n\n" "[ERROR] No such file $2 in the current path. Check file name is correct and is in current path."
    exit 1
  fi

  if [ ! -d "$public_test_folder" ]
  then
    printf "\n%s\n\n" "[ERROR] No such folder "$public_test_folder" in the current path."
    exit 1
  fi

  mkdir -p $tmp_out_folder
  # Remove old files if any
  rm ${tmp_out_folder}/output*.txt

  program_type=$1
  filename=$2
  filename_without_ext=${filename%.*}

  case $program_type in

    "JAVA")
      is_java=1
      rm "${filename_without_ext}.class"
      printf "\n%s" "$compile_stage_msg"
      compile_java
      execution_cmd="java $filename_without_ext"
      ;;

    "PYTHON")
      is_py=1
      execution_cmd="python3 $filename"
      ;;

    "CPP")
      is_cpp=1
      rm $filename_without_ext
      printf "\n%s" "$compile_stage_msg"
      compile_cpp $filename $filename_without_ext
      execution_cmd="./${filename_without_ext}"
      ;;

    *)
      printf "\n%s\n" "Invalid program type: $program_type"
      print_usage
      exit 1
      ;;
    esac

  printf "\n%s\n" "-------Testing public test cases-------"
  run_public_test

  # printf "\n%s\n" "-------Testing private test cases-------"
  run_private_test
  
  # echo $deduction
  if [ $fail_count -ne 0 ] || [ $time_out -eq 1 ]
  then
    printf "\n\n%s\n\n" "******* Some tests failed or time out. Please check!********"
    exit 3
  else
    printf "\n\n%s\n\n" "******* All tests passed. *******"
  fi
}

main "$@"
