##set -x ; clang++ -std=c++11 -O2 -W -Wall -pedantic -pthread main.cpp  && ./a.out
##set -x ; g++ -std=c++11 -O2 -W -Wall -Wconversion -pedantic -pthread main.cpp  && ./a.out
##set -x ; gcc -x c -std=c99 -O2 -W -Wall -pedantic  -pthread  main.cpp -lm && ./a.out
set -x ; gcc -x c -std=c99 -O2 -W -Wall -pedantic  -pthread -S main.cpp  && cat main.s
##set -x ; clang -x c -std=c99 -O2 -W -Wall -pedantic  -pthread main.cpp  && ./a.out