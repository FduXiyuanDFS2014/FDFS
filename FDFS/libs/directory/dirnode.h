#ifndef __DIRNODE_H__
#define __DIRNODE_H__	1

#include <node.h>

class F_Node {

protected:
	DFS_Node *dfs_node;
	char name[MAX_NAME_LEN];

public:
	F_Node(char *name);

	DFS_Node *get_dfs_node();
	void set_name(char *name);
	char *get_name();
};

class Dir_Node;
class File_Node;


class Dir_Node: public F_Node {

private:
	int subdir_num;
	int subfile_num;

	Dir_Node *next;
	Dir_Node *parent;
	Dir_Node *first_subdir;
	File_Node *first_subfile;

public:
	Dir_Node(char *name, Dir_Node *parent);

	int get_subdir_num();
	int get_subfile_num();
	void add_subdir_num();
	void add_subfile_num();

	Dir_Node *get_next();
	Dir_Node *get_parent();
	Dir_Node *get_first_subdir();
	File_Node *get_first_subfile();

	void set_next(Dir_Node *next);
	void set_parent(Dir_Node *parent);
	void set_first_subdir(Dir_Node *first_subdir);
	void set_first_subfile(File_Node *first_subfile);
};


class File_Node: public F_Node {

private:
	Dir_Node *parent;
	File_Node *next;

public:
	File_Node(char *name, Dir_Node *parent);

	Dir_Node *get_parent();
	File_Node *get_next();

	void set_next(File_Node *next);
	void set_parent(Dir_Node *parent);
};

#endif
