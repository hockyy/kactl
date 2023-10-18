find /usr/include/ -name stdc++.h
go() {
	g++ -std=c++17 -O3 -Wall -Wshadow -Wreturn-type -Wunused -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=undefined,address -Wl,--stack,1073741824 "$1".cpp -o $1
}

gg() {
  (ulimit -v 4194304; ulimit -s 4194304; ./$1)
}