#include "class/io.h"
#include <windows.h>

void ring(){
	while(true){
		cout << "\a";
		Sleep(500);
	}
}

main(){
	float min;
	cout << "time in minute:";
	cin >> min;
	min*=1000*60;
	Sleep(min);
	ring();
}