#include <directory.h>
#include <cstring>

Directory::Directory(DFS_Node dfs_node, char *path) {
	this->dfs_node.dfs_node_type = dfs_node.dfs_node_type;
	strcpy(this->dfs_node.ip, dfs_node.ip);
	this->dfs_node.port = dfs_node.port;
	this->dfs_node.next = NULL;

	if (path != NULL) {
		strcpy(this->path, path);
		Dir_Lib::get_standard_path(this->path);
	} else {
		strcpy(this->path, DEFAULT_PATH);
	}
	char name[MAX_NAME_LEN];
	Dir_Lib::get_name_from_path(name, this->path);
	this->dir_node = new Dir_Node(name, NULL);
}

Directory::~Directory() {
	if (this->dir_node == NULL) {
		return;
	}
	Dir_Node *d = this->dir_node->get_first_subdir();
	while (d) {
		Dir_Node *t = d->get_next();
		delete d;
		d = t;
	}
	File_Node *f = this->dir_node->get_first_subfile();
	while (f) {
		File_Node *t = f->get_next();
		delete f;
		f = t;
	}
}

char *Directory::get_path() {
	return this->path;
}

bool Directory::set_path(char *path) {
	if (path != NULL) {
		char temp_path[MAX_PATH_LEN];
		strcpy(temp_path, path);
		Dir_Lib::get_standard_path(temp_path);
		if (this->path_is_valid(temp_path)) {
			strcpy(this->path, temp_path);
			return true;
		} else {
			return false;
		}
	} else {
		strcpy(this->path, DEFAULT_PATH);
	}
	return true;
}

bool Directory::path_is_valid(char *path) {
	return (Dir_Lib::is_dir(path) && Dir_Lib::file_exists(path));
}

bool Directory::read_dir_s() {
	if (this->path[0] == '\0') {
		return false;
	}
	struct dirent *fip;
	DIR *dp;

	if ((dp = opendir(this->path)) == NULL) {
		return false;
	}
	int pathLen = strlen(path);

	Dir_Node *prevDirNode = NULL;
	File_Node *prevFileNode = NULL;

	while ((fip = readdir(dp)) != NULL) {
		char *fipName = fip->d_name;
		int fipPathLen = pathLen + strlen(fipName) + 2;
		char *fipPath = new char[fipPathLen];
		int is_dir = Dir_Lib::merge_path_with_name(this->path, fipName, fipPath);

		if (is_dir) {
			Dir_Node *childDirNode = new Dir_Node(fipName, this->dir_node);

			if (this->dir_node->get_first_subdir() == NULL) {
				this->dir_node->set_first_subdir(childDirNode);
			} else {
				prevDirNode->set_next(childDirNode);
			}
			prevDirNode = childDirNode;
			this->dir_node->add_subdir_num();

		} else {
			File_Node *childFileNode = new File_Node(fipName, this->dir_node);

			if (this->dir_node->get_first_subfile() == NULL) {
				this->dir_node->set_first_subfile(childFileNode);
			} else {
				prevFileNode->set_next(childFileNode);
			}
			prevFileNode = childFileNode;
			this->dir_node->add_subfile_num();
		}
		delete []fipPath;
	}
	closedir(dp);
	return true;
}

int Directory::get_sub_num() {
	return this->dir_node->get_subdir_num() + this->dir_node->get_subfile_num();
}

int Directory::get_dir_content(char *dest, int len) {
	int i = len;
	Dir_Node *childDirNode = this->dir_node->get_first_subdir();
	while (childDirNode) {
		int j = 0;
		char c;
		char *name = childDirNode->get_name();
		for ( ; (c = name[j]) != '\0'; ++j) {
			dest[i++] = c;
		}
		dest[i++] = '\n';
		childDirNode = childDirNode->get_next();
	}
	File_Node *childFileNode = this->dir_node->get_first_subfile();
	while (childFileNode) {
		int j = 0;
		char c;
		char *name = childFileNode->get_name();
		for ( ; (c = name[j]) != '\0'; ++j) {
			dest[i++] = c;
		}
		dest[i++] = '\n';
		childFileNode = childFileNode->get_next();
	}
	return i;
}
