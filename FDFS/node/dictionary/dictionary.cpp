#include <dictionary.h>

extern Conf *dfs_conf;
Data_Dictionary *data_dictionary = new Data_Dictionary(dfs_conf);

Data_Dictionary::Data_Dictionary(Conf *conf) {
	DFS_Node_List *dfs_node_list = conf->get_dfsnode_list();
	this->datanode_num = dfs_node_list->get_datanode_num();
	if (this->datanode_num == 0) {
		return;
	}
	this->directorys = new (Directory *);
	int i = 0;
	for (i = 0; i < this->datanode_num; ++i) {
		this->directorys[i] = new Directory(dfs_node_list->get_node_struct(i, DATA_NODE), NULL);
	}
}

Data_Dictionary::~Data_Dictionary() {
	int i = 0;
	for (i = 0; i < this->datanode_num; ++i) {
		delete this->directorys[i];
	}
	delete this->directorys;
}

int Data_Dictionary::get_subdir_and_file(char *dest, char *path) {
	int sub_num = 0;
	int i = 0;
	for (i = 0; i < this->datanode_num; ++i) {
		if (this->directorys[i]->set_path(path)) {
			this->directorys[i]->read_dir_s();
			sub_num += this->directorys[i]->get_sub_num();
		}
	}
	dest = new char[sub_num * MAX_NAME_LEN];
	int cur_len = 0;
	for (i = 0; i < this->datanode_num; ++i) {
		int end = this->directorys[i]->get_dir_content(dest, cur_len);
		cur_len  = end;
	}
	return sub_num;
}
