#include <fstream>

#include <conf.h>
#include <stringlib.h>

using namespace std;

Conf *dfs_conf = new Conf;

Conf::Conf() {
	memset(this->conf_path, 0, MAX_PATH_LEN);
	this->dfs_node_list = new DFS_Node_List;
}

Conf::~Conf() {
	delete this->dfs_node_list;
}

bool Conf::init() {
	if (!(this->read_conf())) {
		return false;
	}
	return true;
}

char *Conf::get_conf_path() {
	return this->conf_path;
}

void Conf::set_conf_path(char *path) {
	strcpy(this->conf_path, path);
}

bool Conf::add_to_dfsnode_list(char *argv[], int type) {
	char *ip = argv[1];
	int port = str2int(argv[2]);
	DFS_NODE_TYPE node_type;

	if (type == 0) {
		node_type = NAME_NODE;
	} else if (type == 1) {
		node_type = DATA_NODE;
	}

	return this->dfs_node_list->addnode(ip, port, node_type);
}

DFS_Node_List *Conf::get_dfsnode_list() {
	return this->dfs_node_list;
}

bool Conf::read_conf() {
	ifstream dfs_conf;
	dfs_conf.open(conf_path, ios::in);
	if (!dfs_conf) {
		return false;
	}

	char line[MAX_CONF_LEN];
	while (!dfs_conf.eof()) {
		memset(line, 0, MAX_CONF_LEN);
		char *argv[3];
		dfs_conf.getline(line, MAX_CONF_LEN);
		int len = strlen(line);
		if (len == 0) {
			continue;
		}
		parse_args(argv, line, len);
		if (strcmp(argv[0], "namenode") == 0) {
			this->add_to_dfsnode_list(argv, 0);
		} else if (strcmp(argv[0], "datanode") == 0) {
			this->add_to_dfsnode_list(argv, 1);
		} else {
			continue;
		}
	}
	return true;
}
