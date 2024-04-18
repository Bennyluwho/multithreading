#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;

mutex print_boi;
atomic_llong bigsum;
//long long bigsum;

void helloer(int x) {
	int sum = 0;
	for (int i = 0; i < 2'000'000; i++)
		sum += rand() % 10;

	bigsum += sum; //Atoms cannot be split

	//Critical Section that is Mutually Exclusive
	lock_guard lock(print_boi);
	cout << "I am thread: " << x << '\n';
	cout << "Sum is: " << sum << '\n';
}

int main() {
	thread t1(helloer,0);
	thread t2(helloer,1);
	thread t3(helloer,2);
	thread t4(helloer,3);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cout << "The big sum is: " << bigsum << endl;
}
