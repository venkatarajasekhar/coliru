echo "C++11" && g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out; echo -e "\n\nC++1y:" && g++ -std=c++1y -O2 -Wall -pedantic -pthread main.cpp && ./a.out