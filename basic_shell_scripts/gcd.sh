read -p "Enter two numbers " a b
while ((b!=0)) do
	r=$((a%b))
	a=$b
	b=$r
done
echo "GCD is "$a
