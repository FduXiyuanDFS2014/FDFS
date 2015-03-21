#include <node.h>
#include <conf.h>

DFS_Node_List::DFS_Node_List() {
	this->namenode_head = NULL;
	this->namenode_tail = NULL;

	this->datanode_head = NULL;
	this->datanode_tail = NULL;

	this->namenode_num	= 0;
	this->datanode_num	= 0;
}

DFS_Node_List::~DFS_Node_List() {
	delete_node_list();
}

int DFS_Node_List::get_namenode_num() {
	return this->namenode_num;
}

int DFS_Node_List::get_datanode_num() {
	return this->datanode_num;
}

char *DFS_Node_List::get_node_ip(int index, DFS_NODE_TYPE type) {
	DFS_Node *node = get_node(index, type);
	if (node == NULL) {
		return NULL;
	}
	return node->ip;
}

int DFS_Node_List::get_node_port(int index, DFS_NODE_TYPE type) {
	DFS_Node *node = get_node(index, type);
	if (node == NULL) {
		return 0;
	}
	return node->port;
}

bool DFS_Node_List::addnode(char *ip, int port, DFS_NODE_TYPE type) {
	DFS_Node *node = new DFS_Node;
	if (type == DATA_NODE) {
		if (this->datanode_tail == NULL) {
			this->datanode_head = this->datanode_tail = node;
		} else {
			this->datanode_tail->next = node;
			this->datanode_tail = node;
		}
		node->dfs_node_type = DATA_NODE;
		++(this->datanode_num);
	} else if (type == NAME_NODE) {
		if (this->namenode_tail == NULL) {
			this->namenode_head = this->namenode_tail = node;
		} else {
			this->namenode_tail->next = node;
			this->namenode_tail = node;
		}
		node->dfs_node_type = NAME_NODE;
		++(this->namenode_num);
	} else {
		return false;
	}
	node->ip = new char[strlen(ip)];
	strcpy(node->ip, ip);
	node->port = port;
	return true;
}

bool DFS_Node_List::deletenode(int index, DFS_NODE_TYPE type) {
	if (type == DATA_NODE) {
		if (this->datanode_head == NULL) {
			return false;
		} else {
			if (index < 0 || index >= this->datanode_num) {
				return false;
			} else if (index == 0) {
				DFS_Node *temp = this->datanode_head;
				this->datanode_head = this->datanode_head->next;
				delete [](temp->ip);
				delete temp;
			} else {
				DFS_Node *prev = get_node(index - 1, type);
				DFS_Node *temp = prev->next;
				prev->next = temp->next;
				delete [](temp->ip);
				delete temp;
				if (index == this->datanode_num - 1) {
					this->datanode_tail = prev;
				}
			}
			--(this->datanode_num);
		}
	} else if (type == NAME_NODE) {
		if (this->namenode_head == NULL) {
			return false;
		} else {
			if (index < 0 || index >= this->namenode_num) {
				return false;
			} else if (index == 0) {
				DFS_Node *temp = this->namenode_head;
				this->namenode_head = this->namenode_head->next;
				delete [](temp->ip);
				delete temp;
			} else {
				DFS_Node *prev = get_node(index - 1, type);
				DFS_Node *temp = prev->next;
				prev->next = temp->next;
				delete [](temp->ip);
				delete temp;
				if (index == this->namenode_num - 1) {
					this->namenode_tail = prev;
				}
			}
			--(this->namenode_num);
		}
	} else {
		return false;
	}
	return true;
}

DFS_Node DFS_Node_List::get_node_struct(int index, DFS_NODE_TYPE type) {
	DFS_Node *node = this->get_node(index, type);
	DFS_Node tmp_node;
	if (node == NULL) {
		tmp_node.ip = NULL;
		tmp_node.port = 0;
	} else {
		tmp_node.ip = new char[IP_LEN];
		strcpy(tmp_node.ip, node->ip);
		tmp_node.port = node->port;
	}
	return tmp_node;
}




void DFS_Node_List::delete_node_list() {
	DFS_Node *p = this->datanode_head;
	while (p) {
		DFS_Node *t = p->next;
		delete [](p->ip);
		delete p;
		p = t;
	}
	p = this->namenode_head;
	while (p) {
		DFS_Node *t = p->next;
		delete [](p->ip);
		delete p;
		p = t;
	}
}


DFS_Node *DFS_Node_List::get_node(int index, DFS_NODE_TYPE type) {
	DFS_Node *head = NULL;
	if (type == DATA_NODE) {
		if (index < 0 || index >= this->datanode_num) {
			return NULL;
		}
		head = this->datanode_head;
	} else if (type == NAME_NODE) {
		if (index < 0 || index >= this->namenode_num) {
			return NULL;
		}
		head = this->namenode_head;
	} else {
		return NULL;
	}

	int i = 0;
	for ( ; i < index; ++i) {
		head = head->next;
	}
	return head;
}
