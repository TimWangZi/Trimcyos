#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "file_struct.h"
#include "file_management.h"
std::string str_name, op_code;
bool saved = false;
int main(int argc, char* argv[]) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (argc != 3) {
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "Operands error\n";
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return 1;
	}else {
		str_name = argv[1];
		std::stringstream strs;
		strs << argv[2];
		int org;
		strs >> org;
		if (org < 0) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::cout << "Orgin error\n";
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		try{
			FileManagement fm(str_name, org);
			while (1) {
				std::cin >> op_code;
				if (op_code == "save") {
					fm.save([&]() {
						SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						std::cout << "Success:" << str_name << '\n';
						SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						saved = true;
					}, [&]() {
						SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
						std::cout << "Can't save the file:" << str_name << '\n';
						SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					});
				}
				if (op_code == "load") {
					auto buf = fm.load_head();
					SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					std::cout << "<attribute>\t\t<value>\n";
					SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					std::cout << "Static tag:\t\t" << "tag " << '\n';
					std::cout << "Element size:\t\t" << buf.hd.Element_size << '\n';
					std::cout << "Table size:\t\t" << buf.hd.whole_table_size << '\n';
					std::cout << "Number of unit:\t\t" << buf.Table_size << '\n';
					SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					saved = false;
				}
				if (op_code == "check") {
					auto buf = fm.ret_table();
					int index;
					std::cout << "index:";
					std::cin >> index;
					printf("name:\t\t0x%X\n", buf.fu[index].name);
					if (buf.fu[index].file_type == TYPE_APP)
						printf("type:\t\tapp\n");
					if (buf.fu[index].file_type == TYPE_FILE)
						printf("type:\t\tfile\n");
					printf("tag:\t\t%d\n", buf.fu[index].tag);
					if (buf.fu[index].state == CS) {
						printf("address/cs:\t0x%X\n", buf.fu[index].address_cs);
					}
					else if (buf.fu[index].state == DS) {
						printf("address/ds:\t0x%X\n", buf.fu[index].address_ds);
					}
					else {
						printf("address:\t\tUNDEFINE\n");
					}
					printf("size:\t\t0x%X\n", buf.fu[index].file_size);
				}
				if (op_code == "add") {
					std::string str1, str2;
					char str3[5];
					std::cin >> str1 >> str2 >> str3;
					dword name;
					memccpy(&name,&str3,1,sizeof(dword));
					if (str2 == "file") {
						fm.add(str1, name, TYPE_FILE);
					}else if (str2 == "app") {
						fm.add(str1, name, TYPE_APP);
					}else {
						SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
						std::cout << "Error:undefine type!";
						SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						return 1;
					}
					saved = false;
				}
				if (op_code == "del") {
					fm.del();
					saved = false;
				}
				if (op_code == "QUIT")
					break;
				op_code.clear();
			}
			if (!saved) {
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << "This file has not be saved yet\n" << "if you want to save it please enter(Yes)\n";
				std::string str;
				std::cin >> str;
				if (str == "Yes" || str == "yes" || str == "YES") {
					fm.save([&]() {
						SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
						std::cout << "Can't save the file:" << str_name << '\n';
						SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					}, [&]() {
						SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						std::cout << "Success:" << str_name << '\n';
						SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						saved = true;
					});
					return 0;
				}
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
		catch (int a){
			if (a == CANT_FIND_FILE) {
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << "Can't open the file\n";
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	return 0;
}