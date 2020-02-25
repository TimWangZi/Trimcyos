#pragma once
#pragma warning(disable:4996)
#define CANT_FIND_FILE 1
class FileManagement {
public:
	inline void             add(std::string name, dword file_name, word type);
	inline void             del();
	inline void				swap_file(int index1, int index2);
	template<typename I, typename R>
	inline void             save(I const &I, R const &R);
	inline FileSystemTable load_head();
	inline FileSystemTable ret_table();
	inline ~FileManagement();
	inline FileManagement(std::string str, int orgin = 0);
private:
	inline int file_size(std::string name);

	int org, bis;
	int p;

	FILE *fp;
	FileSystemTable table;
	std::vector<std::string> name_list;
};

FileManagement::FileManagement(std::string str, int orgin) :org(orgin + sizeof(table)) {
	table.hd.Element_size = sizeof(table.fu[0]);
	table.hd.whole_table_size = TALE_SIZE;
	table.Table_size = MAX_SIZE;
	fp = fopen(str.c_str(), "ab+");
	if (fp == NULL) {
		throw CANT_FIND_FILE;
	}
}
FileManagement::~FileManagement() {
	fclose(fp);
}
inline int FileManagement::file_size(std::string name) {
	FILE *fp2 = fopen(name.c_str(), "r");
	if (!fp2) return -1;
	fseek(fp2, 0L, SEEK_END);
	int size = ftell(fp2);
	fclose(fp2);
	return size;
}
inline void FileManagement::add(std::string name, dword file_name, word type) {
	name_list.push_back(name);
	table.fu[p].name = file_name;
	table.fu[p].file_type = type;
	table.fu[p].address_cs = bis + org;
	table.fu[p].address_ds = 0;
	table.fu[p].file_size = file_size(name);
	p++;
	bis += file_size(name);
}
inline void FileManagement::del() {
	bis -= file_size(name_list.back());
	name_list.pop_back();
	p--;
	table.fu[p].address_cs = table.fu[p].address_ds = table.fu[p].file_size = table.fu[p].file_type = table.fu[p].name = 0;
	table.fu[p].state = CS;
}
inline void FileManagement::swap_file(int index1, int index2) {
	std::swap(table.fu[index1], table.fu[index2]);
}
template<typename I, typename R>
inline void FileManagement::save(I const &I, R const &R) {
	fwrite(&table, sizeof(table), 1, fp);
	for (auto &x : name_list) {
		FILE *fp2 = fopen(x.c_str(), "rb");
		if (fp2 == NULL) {
			R();
			return;
		}
		char  c = 0;
		while (true) {
			fread(&c, sizeof(c), 1, fp2);
			if (feof(fp2))
				break;
			fwrite(&c, sizeof(c), 1, fp);
		}
		I();
		fclose(fp2);
	}
}
inline FileSystemTable FileManagement::load_head() {
	fread(&table, sizeof(table), 1, fp);
	return table;
}
inline FileSystemTable FileManagement::ret_table() {
	return table;
}
