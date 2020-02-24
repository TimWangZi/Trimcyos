#pragma once
#define CANT_FIND_FILE 1
class FileManagement{
public:
	inline FileManagement(std::string str, int orgin = 0);
	inline void             add(std::string name, dword file_name, word type, dword size);
	inline void             del();
	inline void				swap_file(int index1, int index2);
	inline void             save();
	inline FileSystemTable &load();
	inline ~FileManagement();

private:
	inline int file_size(std::string name);

	int org, bis;
	int p;

	FILE *fp;
	FileSystemTable table;
	std::queue<std::string> name_list;
};

FileManagement::FileManagement(std::string str, int orgin = 0):org(orgin){
	table.hd.Element_size = sizeof(table.fu[0]);
	table.hd.whole_table_size = TALE_SIZE;
	table.Table_size = MAX_SIZE;
	fp = fopen(str.c_str(), "ab+");
	if (fp == NULL) {
		throw CANT_FIND_FILE;
	}
}
FileManagement::~FileManagement(){
	fclose(fp);
}
inline int FileManagement::file_size(std::string name){
	FILE *fp2 = fopen(name.c_str(), "r");
	if (!fp2) return -1;
	fseek(fp2, 0L, SEEK_END);
	int size = ftell(fp2);
	fclose(fp2);
	return size;
}
inline void FileManagement::add(std::string name, dword file_name, word type, dword size){
	
	bis += file_size(name);
}