xmodmap -e 'clear lock' -e 'keycode 66=less greater' #caps = <>
go() {
	# -Wall -Wshadow -Wreturn-type -Wunused nyalain aja! pasti berguna
	# glibxx debug buat ngecek out of bound di vector
	# -fsanitize=undefined,address buat ngecek out of bound di array
	# -Wl,--stack,1073741824 buat stack size
	g++ -std=c++17 -Wall -Wshadow -Wreturn-type -Wunused -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=undefined,address "$1".cpp -o $1
}

gg() {
	./$1 < in
}