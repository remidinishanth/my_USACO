%: %.cpp
	g++ -Wl,-stack_size,0x100000000 -Wall -Wextra -std=c++11 -O2 -Wshadow -Wcast-qual \
	-Wcast-align -Wno-unused-result -O2 -DLOCAL \
	$< -o $@