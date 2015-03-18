#ifndef __DFS_CONF_H__
#define __DFS_CONF_H__	1

#include <iostream>
#include <cstring>

#include <node.h>
#include <def.h>

#define MAX_CONF_LEN	1024

class Conf {

private:
	char conf_path[MAX_PATH_LEN];

	DFS_Node_List *dfs_node_list;

public:
	Conf();
	~Conf();

	bool init();

	char *get_conf_path();
	void set_conf_path(char *path);

	DFS_Node_List *get_dfs_node_list();

private:
	bool read_conf();
	bool add_to_list(char *ip, int port, DFS_NODE_TYPE type);
	
};

#endif
