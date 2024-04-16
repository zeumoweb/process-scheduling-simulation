#!/bin/bash

make all

# Define test functions
test1() {
    echo -e "\nRunning Test 1:  Jobs Data 1 and First Come First Serve..."
    ./program jobs_data1.txt 1
}

test2() {
    echo -e "\nRunning Test 2:  Jobs Data 2 and First Come First Serve..."
    ./program jobs_data2.txt 1
}

test3() {
    echo -e "\nRunning Test 3: Jobs Data 1 and Round Robin with Quantum 3..."
    ./program jobs_data1.txt 2 3
}

test4() {
    echo -e "\nRunning Test 4: Jobs Data 2 and Round Robin with Quantum 3..."
    ./program jobs_data2.txt 2 3
}

test5() {
    echo -e "\nRunning Test 5: Jobs Data 1 and Shortest Job First..."
    ./program jobs_data1.txt 3
}

test6() {
    echo -e "\nRunning Test 6: Jobs Data 2 and Shortest Job First..."
    ./program jobs_data2.txt 3
}


test7() {
    echo -e "\nRunning Test 7: Jobs Data 1 and Multi-Level Queue..."
    ./program jobs_data1.txt 4 5
}

test8() {
    echo -e "\nRunning Test 8: Jobs Data 2 and Multi-Level Queue.."
    ./program jobs_data2.txt 4 5
}
# Main function to select and run tests
main() {
    case $1 in
        test1)
            test1
            ;;
        test2)
            test2
            ;;
        test3)
            test3
            ;;
        test4)
            test4
            ;;
        test5)
            test5
            ;;
        test6)
            test6
            ;;
        test7)
            test7
            ;;
        test8)
            test8
            ;;
        test9)
            test1
            test2
            test3
            test4
            test5
            test6
            test7
            test8
            ;;
        *)
            echo "Invalid test target. Usage: $0 {1|2|3|4|all}"
            ;;
    esac
}

# Call main function with command-line arguments
main "$@"

make clean
