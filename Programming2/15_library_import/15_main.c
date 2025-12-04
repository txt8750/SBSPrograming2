#include <stdio.h>
#include "Math.h"
#pragma comment(lib, "DLL_Sound.lib")

int main()
{
	PlayBGM();
	printf("%d\n", Add(3, 5));
}