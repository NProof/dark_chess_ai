search:
	g++ -std=c++11 -o search *.cpp -lws2_32 -static-libstdc++ -static-libgcc
	mv search.exe ../CreateRoom/Search/search.exe