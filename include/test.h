#pragma once



#include <SDL/SDL_timer.h>
#include <SDL/SDL_log.h>
#include <vector>
using std::vector;

int processVal = 0;
const long long cycTimes = 5;
const long long memNum = 100000;

void func(long long ul = 3) {
	++ul;
	++processVal;
	int lul = processVal % 3;
	processVal += lul % 2;
}


void doFunction() {
	int time1 = SDL_GetTicks();

	for (long long j = 0; j < cycTimes;++j)
	for (int i = 0; i < memNum; ++i)
		func();

	int time2 = SDL_GetTicks() - time1;
	SDL_Log("%i", time2);
}

void doArray() {

	long long arr[memNum];


	int time1 = SDL_GetTicks();

	for (int j = 0; j<cycTimes; ++j)
	for (int i=0; i<memNum; ++i)
		func(arr[i]);

	int time2 = SDL_GetTicks() - time1;
	SDL_Log("Array Time =  %i", time2);
}

void doVector() {

	vector<long long> vec(memNum,3);

	auto it = vec.begin();
	auto end = vec.end();

	int time1 = SDL_GetTicks();

	for (int j = 0; j<cycTimes; ++j)
	for (auto it = vec.begin(); it != end; ++it)
		func(*it);

	int time2 = SDL_GetTicks() - time1;
	SDL_Log("Vector Time =  %i", time2);
}

void doVector2() {

	vector<long long> vec(memNum, 3);


	int time1 = SDL_GetTicks();

	for (int j = 0; j<cycTimes; ++j)
		for (long long i = 0; i < memNum; ++i)
			func(vec[i]);

	int time2 = SDL_GetTicks() - time1;
	SDL_Log("Vector2 Time =  %i", time2);
}






void test4() {

	const int num = 100000;
	int      arr1[num];
	//boolval  arr2[num + 1];  arr2[num].valid = false;

	SDL_Log("Size of array 1 =  %u", sizeof(arr1));
	//SDL_Log("Size of array 2 =  %u", sizeof(arr2));

	SDL_Log("Traversing arr 1 ...");
	int time = SDL_GetTicks();
	for (int i = 0; i <num;++i) {
		func();
	}
	time = SDL_GetTicks() - time;
	SDL_Log("travel time arr1 =  %i", time);

	SDL_Log("Traversing arr 2 ...");
	time = SDL_GetTicks();
//	for (int i = 0; arr2[i].valid; ++i) {
	func();
	//}
	time = SDL_GetTicks() - time;
	SDL_Log("travel time arr2 =  %i", time);

}


void test5() {


	SDL_Log("sizeofchar =   %u", sizeof(unsigned char));
	getchar();
	//char   arr1[1024000];
	for (int i = 1;; ++i) {
		int time = SDL_GetTicks();
		unsigned char * arr2 = new unsigned char[1000000000];
		time = SDL_GetTicks() - time;
		SDL_Log("arr2   X    _%u_  %u", i, time );
	}

}


void printVarSizes() {


	SDL_Log("Stack vs Heap  ENTER");
	getchar();
	SDL_Log("sizeof (void)      =  NO");
	SDL_Log("sizeof (bool)      =  %u", sizeof(bool));
	SDL_Log("sizeof (char)      =  %u", sizeof(char));
	SDL_Log("sizeof (short)     =  %u", sizeof(short));
	SDL_Log("sizeof (int)       =  %u", sizeof(int));
	SDL_Log("sizeof (long)      =  %u", sizeof(long));
	SDL_Log("sizeof (long long) =  %u", sizeof(long long));

	SDL_Log("sizeof (void*)      =  %u", sizeof(void*));
	SDL_Log("sizeof (bool*)      =  %u", sizeof(bool*));
	SDL_Log("sizeof (char*)      =  %u", sizeof(char*));
	SDL_Log("sizeof (short*)     =  %u", sizeof(short*));
	SDL_Log("sizeof (int*)       =  %u", sizeof(int*));
	SDL_Log("sizeof (long*)      =  %u", sizeof(long*));
	SDL_Log("sizeof (long long*) =  %u", sizeof(long long*));
	getchar();
	


}


void start() {

	printVarSizes();

	doArray();
	doVector();
	doVector2();
	getchar();
}

