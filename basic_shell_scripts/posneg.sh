read -p "Enter a Number : " n
if (($n == 0));
then
	echo "It is Zero "
elif (( $n < 0 ));
then
	echo "It is Negative "
else
	echo "It is Positive"
fi
