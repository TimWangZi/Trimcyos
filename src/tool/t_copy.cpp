#pragma warning(disable:4996)
#include <Windows.h>
#include <iostream>
#include <io.h>
using namespace std;
/*
*F:文件夹
*f:文件
*/
char code, buffer;//操作码
int main(int argc, char* argv[]) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	/*if (strcmp("F", argv[1]) == 0 && argc > 2) {
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "error:";
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "Unsport\n";
	/*}
	else if (strcmp("f", argv[1]) == 0 && argc > 2) {*/
		FILE *fp = fopen(argv[1], "wb+");
		if (fp == NULL) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "error:";
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << "Can't open the file\n";
		}
		for (int i = 2; i < argc; i++) {
			FILE *fp2 = fopen(argv[i], "rb+");
			if (fp2 == NULL) {
				cout << argv[1] << '\t' << "<-" << argv[i] << '\t';
				cout << "<";
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "fail";
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << ">\n";
				cout << "eixit the process";
				return 1;
			}
			cout << argv[1] << '\t' << "<-" << argv[i] << '\t';
			while (true) {
				fread(&buffer, sizeof(buffer), 1, fp2);
				if (feof(fp2))
					break;
				fwrite(&buffer, sizeof(buffer), 1, fp);
			}
			cout << "<";
			SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "finish";
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << ">\n";
			fclose(fp2);
		}
	/*}
	else {
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "error:";
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "Undefine Command\n";
		return 1;
	}*/
	return 0;
}