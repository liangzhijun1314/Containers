#include <windows.h>
#include <thread>
#include "Pipe.h"

// 参考： https://www.cnblogs.com/suwings/p/5754943.html
using namespace std;

void read();
void Loop();

Pipe * pipe;        //属于全局变量


int main()
{
	thread t1(read);
	thread t2(Loop);

	pipe = new Pipe("cmd");
	t1.join();
	t2.join();
	return 0;
}
void read() {

	while (true) {
		char str[200];
		cin >> str;
		pipe->sendCommand(str);
	}

}

void Loop() {
	while (true)
	{
		Sleep(1000);
		if (pipe->getStatus() == -11)
		{
			cout << " ERROR " << endl;
			return;
		}
	}

}