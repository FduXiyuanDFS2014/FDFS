#ifndef __DIR_LIB_H__
#define __DIR_LIB_H__	1

#include <def.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>

typedef enum FileType {
	DFS_FILE,
	DFS_DIRECTORY
} FileType;

class Dir_Lib {

public:
	static void get_standard_path(char *path);
	static bool is_dir(char *path);
	static bool file_exists(char *path);
	static bool merge_path_with_name(char *path, char *name, char *dest);
	static void get_name_from_path(char *path, char *name);
};

#endif
