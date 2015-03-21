#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__	1

#include <dir_lib.h>
#include <dirnode.h>

#define DEFAULT_PATH	"/"

class Directory {

private:
	DFS_Node dfs_node;
	char path[MAX_PATH_LEN];
	Dir_Node *dir_node;

public:
	Directory(DFS_Node dfs_node, char *path);
	~Directory();

	char *get_path();
	bool set_path(char *path);

	bool read_dir_s();

	int get_sub_num();
	int get_dir_content(char *dest, int n);

private:
	bool path_is_valid(char *path);
};

#endif
