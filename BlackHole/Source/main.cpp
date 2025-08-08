#include "App.h"

#include <windows.h>
#include <iostream>
#include <cstdio>

void CreateConsole() {
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    SetConsoleTitleA("Debug Console");
}

int main() {
    CreateConsole();
	App app;
	app.run();
	return 0;
}