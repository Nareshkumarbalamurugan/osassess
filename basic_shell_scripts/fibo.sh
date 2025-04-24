read -p "Enter n value " n
echo -n 0,
a=0 b=1
for((i=1;i<n;i++))
do
	echo -n  $b
	if(( i!=n-1));then echo -n ","
	c=$((a+b))
	a=$b
	b=$c

fi
done


