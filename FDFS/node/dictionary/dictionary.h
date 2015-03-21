#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__	1

#include <directory.h>
#include <conf.h>

class Data_Dictionary {

private:
	int datanode_num;
	Directory **directorys;

public:
	Data_Dictionary(Conf *conf);
	~Data_Dictionary();

	int get_subdir_and_file(char *dest, char *path);
};

extern Data_Dictionary *data_dictionary;

#endif
