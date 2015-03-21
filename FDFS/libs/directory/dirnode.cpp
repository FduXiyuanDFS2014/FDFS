#include <cstring>

#include <dirnode.h>

F_Node::F_Node(char *name) {
	this->set_name(name);
	this->dfs_node = NULL;
}

DFS_Node *F_Node::get_dfs_node() {
	return this->dfs_node;
}

void F_Node::set_name(char *name) {
	if (name != NULL) {
		strcpy(this->name, name);
	} else {
		this->name[0] = '\0';
	}
}

char *F_Node::get_name() {
	return this->name;
}



Dir_Node::Dir_Node(char *name, Dir_Node *parent): F_Node(name) {
	this->subdir_num = 0;
	this->subfile_num = 0;

	this->next = NULL;
	this->parent = parent;
	this->first_subdir = NULL;
	this->first_subfile = NULL;
}

int Dir_Node::get_subdir_num() {
	return this->subdir_num;
}

int Dir_Node::get_subfile_num() {
	return this->subfile_num;
}

void Dir_Node::add_subdir_num() {
	++(this->subdir_num);
}

void Dir_Node::add_subfile_num() {
	++(this->subfile_num);
}

Dir_Node *Dir_Node::get_next() {
	return this->next;
}

Dir_Node *Dir_Node::get_parent() {
	return this->parent;
}

Dir_Node *Dir_Node::get_first_subdir() {
	return this->first_subdir;
}

File_Node *Dir_Node::get_first_subfile() {
	return this->get_first_subfile();
}

void Dir_Node::set_next(Dir_Node *next) {
	this->next = next;
}

void Dir_Node::set_parent(Dir_Node *parent) {
	this->parent = parent;
}

void Dir_Node::set_first_subdir(Dir_Node *first_subdir) {
	this->first_subdir = first_subdir;
}

void Dir_Node::set_first_subfile(File_Node *first_subfile) {
	this->first_subfile = first_subfile;
}



File_Node::File_Node(char *name, Dir_Node *parent): F_Node(name) {
	this->next = NULL;
	this->parent = parent;
}

File_Node *File_Node::get_next() {
	return this->next;
}

Dir_Node *File_Node::get_parent() {
	return this->parent;
}

void File_Node::set_next(File_Node *next) {
	this->next = next;
}

void File_Node::set_parent(Dir_Node *parent) {
	this->parent = parent;
}
