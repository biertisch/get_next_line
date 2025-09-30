#!/bin/bash

BONUS=0
PROG="test/get_next_line"
SRC="test/main.c get_next_line.c get_next_line_utils.c"

if [ "$1" = "bonus" ]; then
    BONUS=1
	PROG="test/get_next_line_bonus"
	SRC="test/main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c"
elif [ -n "$1" ]; then
	echo "Usage: $0 [bonus]"
	exit 1
fi

if [ $BONUS -eq 1 ]; then
	echo -e "Running bonus tests...\n"
else
	echo -e "Running mandatory tests...\n"
fi

compile()
{
	SIZE=$1
	echo "Compiling with BUFFER_SIZE=$SIZE..."
	if [ -n "$SIZE" ]; then
		cc -Wall -Wextra -Werror -D BUFFER_SIZE=$SIZE $SRC -I. -o $PROG
	else
		cc -Wall -Wextra -Werror $SRC -I. -o $PROG
	fi
}

pause()
{
	echo ""
	read -n 1 -s -p "Press Enter to continue..." key
	if [ "$key" != "" ]; then
    	echo -e "\nExiting..."
		exit
	fi
	echo -e "\n"
}

compile
i=0;
for file in test/data/*; do
	echo "------------------------------------"
    echo "Test $i: $file"
	./$PROG $file
	((i++))
	pause
done

# standard input
echo "------------------------------------"
echo "Test $i: standard input"
./$PROG
((i++))
pause

# invalid files
for arg in "test" "non-existent"; do
	echo "------------------------------------"
	echo "Test $i: $arg"
	./$PROG $arg
	((i++))
	pause
done

# different buffer sizes
for SIZE in 10 1 999999 0 -1; do
	compile $SIZE
	echo "------------------------------------"
	echo "Test $i: test/data/test3.txt"
	./$PROG test/data/test3.txt
	((i++))
	pause
done

# bonus: multiple files
if [ $BONUS -eq 1 ]; then
	compile
	echo "------------------------------------"
	echo "Test $i: multiple files interpolated"
	./$PROG test/data/test0.txt test/data/test1.txt test/data/test3.txt
	((i++))
else
	echo -e "To test bonus part, run: ./test/test.sh bonus"
fi

rm -f $PROG