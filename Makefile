def:
	echo "Usage: make <container_name>"
	exit 1

vector:
	g++ -std=c++14 vector_test.cc -o vector.test -msse4.2

list:
	g++ -std=c++14 list_test.cc -o list.test -msse4.2



