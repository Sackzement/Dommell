#pragma once



#include <SDL/SDL_timer.h>
#include <SDL/SDL_log.h>
#include <vector>
using std::vector;

int ulu = 0;

void doFunc() {
	++ulu;
	int lul = ulu % 3;
	ulu += lul % 2;
}


void test1() {
	int time1 = SDL_GetTicks();
	//for (int i = 0; i < num; ++i)
		doFunc();

	int time2 = SDL_GetTicks() - time1;
	SDL_Log("%i", time2);
}

vector<void(*)()> funcs;
void test2() {
	auto it = funcs.begin();
	auto end = funcs.end();
	int time1 = SDL_GetTicks();
	for (; it != end; ++it)
		(*it)();

	int time2 = SDL_GetTicks() - time1;
	SDL_Log("%i", time2);
}

/*constexpr unsigned const long long getExp(const unsigned long long& numA, const unsigned long long& numB)  {
	long result = 1;
	for (long i = 0; i < numB; ++i)
		result *= numA;
	return result;
}*/

void test3() {
	long long bytenum;

	SDL_Log("(long long) size = %ll  ---  OK?", sizeof(long long));
	getchar();
	SDL_Log("(char) size = %i  ---  OK?", sizeof(char));
	getchar();
	SDL_Log("Stack test Start !!! OK?");
	getchar();
	SDL_Log("Trying to allocate %ll bytes", bytenum);
	try
	{
		//int arr[getExp(2,100)];
		SDL_Log("%ll bytes   SUCCESSFULL", bytenum);
	}
	catch (const std::exception&)
	{

	}
}

struct boolval
{
	bool valid = true;
	int val = 5;
};



void test4() {

	const int num = 100000;
	int      arr1[num];
	boolval  arr2[num + 1];  arr2[num].valid = false;

	SDL_Log("Size of array 1 =  %u", sizeof(arr1));
	SDL_Log("Size of array 2 =  %u", sizeof(arr2));

	SDL_Log("Traversing arr 1 ...");
	int time = SDL_GetTicks();
	for (int i = 0; i <num;++i) {
		doFunc();
	}
	time = SDL_GetTicks() - time;
	SDL_Log("travel time arr1 =  %i", time);

	SDL_Log("Traversing arr 2 ...");
	time = SDL_GetTicks();
//	for (int i = 0; arr2[i].valid; ++i) {
		doFunc();
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


void test6() {

	const int num = 100000;

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

	SDL_Log("Allocating Stack memory long long  %i  times  ENTER", num);
	getchar();
	long long stackMem[num];
	SDL_Log("Allocated Stack memory  ENTER");
	getchar();

	SDL_Log("Allocating Heap memory long long*  %i  times  ENTER", num);
	getchar();
	long long** heapMem = new long long*[num];
	for (int i = 0; i < num; ++i) {
	new long long;
	heapMem[i] = new long long;
	//*heapMem[i] = i;
}
	SDL_Log("Allocated Heap memory  ENTER");
	getchar();
	SDL_Log("Traversing Stack memory  ENTER");
	getchar();
	int time = SDL_GetTicks();
	long long val = 7;
	unsigned long times = 4000;
	for (int j = 0; j < times; ++j)
	for (int i = 0; i < num; ++i)
		val %= stackMem[i];
	time = SDL_GetTicks() - time;
	SDL_Log("Traversed Stack memory  Time = %u millSecs  ENTER", time);
	getchar();
	SDL_Log("Traversing Heap memory  ENTER");
	getchar();
	time = SDL_GetTicks();
	val = 7;
	for (int j = 0; j < times; ++j)
	for (int i = 0; i < num; ++i)
		val %= *(heapMem[i]);
	time = SDL_GetTicks() - time;
	SDL_Log("Traversed Heap memory  Time = %u millSecs  ENTER", time);
	getchar();


}


void start() {

	//test1();
	ulu = 0;
	//for (int i = 0; i < num; ++i)
		//funcs.push_back(doFunc);
	//test2();
	//test3();
	test6();

	try
	{
		//int arr[num];
		//SDL_Log("%ll bytes   SUCCESSFULL", num);
	}
	catch (const std::exception&)
	{

	}
	getchar();
}

