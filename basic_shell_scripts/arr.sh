read -p "Enter array elements : " -a arr
min=${arr[0]}
for n in "${arr[@]}"; do
	if ((n < min)); then
		min=$n
fi
done
echo "Minimum element in array is " $min

