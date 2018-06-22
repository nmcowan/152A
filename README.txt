# ECS 152A Project 1

Natalie Cowan, 
Margaret Sit, 



Compiled with: 

g++ -std=c++11 
ip2as.cpp
./a.out DB_091803.txt IPlist2.txt

Windows platform was used throughout the assignment. 


We used two nested while loops in our program. One to receive input from the IPlist.txt file and the other to receive input from the DB_091803.txt file. Each line was parsed into its respective category including IP address, mask, AS number, etc. Then, the IP address from each file was tokenized by "." to make comparisons easier. Tokenizing was implemented with the boost tokenizer. Then, each number seperated by the period was stored into a vector of strings. 



We then used a for loop to go through each element in our vector (each element is a byte in the IP address). Since each mask was greater than 8, we first just used string compare to compare the first 8 bits of the IP address. Then, we decremented the mask by 8 and began comparing the rest. Then, if the mask is still greater than 8 we continue to used string compare and decrement the mask by 8. However, once the mask is less than 8, we converted the strings to an int and used shifts to compare the necessary bits. 



Then, if the two IP addresses match according to the given mask, we append the necessary characters and symbols so that it's in the final output version of '[IP Adress/Mask] [AS Number] [Original IP Address]'. This would then get stored in vector so that if another IP address matched and the mask was larger, we would push a new string onto the longestPrefix vector. 