#ifndef __DFS_NODE_H__
#define __DFS_NODE_H__	1

#include <cstring>
#include <type.h>
#include <def.h>

typedef enum DFS_NODE_TYPE {
	NAME_NODE,
	DATA_NODE,
} DFS_NODE_TYPE;

typedef struct DFS_Node {
	DFS_NODE_TYPE dfs_node_type;
	char *ip;
	int port;

	DFS_Node *next;
} DFS_Node;



class DFS_Node_List {

private:
	DFS_Node *namenode_head;
	DFS_Node *namenode_tail;

	DFS_Node *datanode_head;
	DFS_Node *datanode_tail;
	int namenode_num;
	int datanode_num;

public:
	DFS_Node_List();
	~DFS_Node_List();

	int get_namenode_num();
	int get_datanode_num();

	char *get_node_ip(int index, DFS_NODE_TYPE type);
	int get_node_port(int index, DFS_NODE_TYPE type);
	DFS_Node get_node_struct(int index, DFS_NODE_TYPE type);

	bool addnode(char *ip, int port, DFS_NODE_TYPE type);
	bool deletenode(int index, DFS_NODE_TYPE type);

private:
	void delete_node_list();

	DFS_Node *get_node(int index, DFS_NODE_TYPE type);

};


#endif
