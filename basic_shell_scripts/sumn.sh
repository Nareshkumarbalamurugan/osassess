read -p "enter a number :" n
sum=0
for ((i=0;i<=n;i++))
do
	sum=$((sum+i))
done
echo "The sum of" $n " numbers  = " $sum

