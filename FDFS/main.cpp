#include <iostream>

#include <conf.h>

using namespace std;

int main() {
	Conf *conf = new Conf;
	char path[] = "/home/luchang/dfs.conf";
	conf->set_conf_path(path);
	bool res = conf->init();
	if (!res) {
		cout << "fail" << endl;
		return -1;
	}
	DFS_Node_List *dfs_node_list = conf->get_dfsnode_list();
	int name_node_num = dfs_node_list->get_namenode_num();
	int data_node_num = dfs_node_list->get_datanode_num();

	int i = 0;
	for ( ; i < name_node_num; ++i) {
		DFS_Node node = dfs_node_list->get_node_struct(i, NAME_NODE);
		cout << node.ip << ' ' << node.port << endl;
	}
	for (i = 0; i < data_node_num; ++i) {
		DFS_Node node = dfs_node_list->get_node_struct(i, DATA_NODE);
		cout << node.ip << ' ' << node.port << endl;
	}
	return 0;
}
