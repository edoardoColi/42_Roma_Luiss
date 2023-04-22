#!/bin/bash
MINIDIR=./
echo "Running make"
make -C $MINIDIR all > /dev/null
echo "Relink?"
make -C $MINIDIR all

function exec_test()
{
	outBash=$($1 > /proc/$2/fd/0)
	retBash=$?
echo ho1 $outBash
echo e ho2 $retBash
	outMini=$($1 > /proc/$3/fd/0)
	retMini=$?
echo ho3 $outMini
echo e ho4 $retMini

	if ["$outBash" == "$outMini"] && ["$retBash" == "$retMini"]; then
		echo ok
	else
		echo nono
	fi
}

echo "Running Tests"

bash &
pidBash=$!
# disown $pidBash
echo "Bash PID=$pidBash"

./$MINIDIR/minishell &
pidMini=$!
# disown $pidMini
echo "Minishell PID=$pidMini"

exec_test 'ls' $pidBash $pidMini

#ADD
# modalita' interattiva dove aspetto input e lo testo

# sleep 5

kill -9 $pidBash
kill -9 $pidMini

echo "Removing objects files"
make -C $MINIDIR clean > /dev/null
