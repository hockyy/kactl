alias c='g++ -Wall -Wconversion -Wfatal-errors -g -std=c++14 \
	-fsanitize=undefined,address'
alias com='g++ -std=c++17 -O2 -Ofast -s -lm -pipe -Wall -Wshadow \
	-Wreturn-type -Wunused -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
	-Wl,--stack,1073741824'
xmodmap -e 'clear lock' -e 'keycode 66=less greater' #caps = <>
