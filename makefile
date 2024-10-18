default: HashTable.cpp
	# write command to test your files (you do not need it for your submissions)
	g++ -Wall HashTable.cpp -o HashTable.out 
	g++ -Wall main.cpp -o main.out 
clean:
	rm *.out
