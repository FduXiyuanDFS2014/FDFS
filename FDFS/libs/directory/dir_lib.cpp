#include <cstring>
#include <sys/stat.h>

#include <dir_lib.h>

bool Dir_Lib::file_exists(char *path) {
	return access(path, F_OK) == 0;
}

bool Dir_Lib::is_dir(char *path) {
	struct stat st;
	stat(path, &st);
	if (S_ISDIR(st.st_mode)) {
		return true;
	}
	return false;
}

void Dir_Lib::get_standard_path(char *path) {
	int path_len = strlen(path);

	char *fp[MAX_FOLDER_LEN];

	int i = 0;
	int folder_num = 0;
	int sstate = 0;
	int pstate = 0;
	int fstate = 0;
	for ( ; i < path_len; ++i) {
		if (path[i] == '/') {
			if (pstate == 2 && folder_num > 0) {
				--folder_num;
			}
			fstate = 0;
			pstate = 0;
			++sstate;
		} else if (path[i] == '.') {
			++pstate;
			if (pstate == 3 && !fstate) {
				fp[folder_num++] = (char *) path + i - 2;
				fstate = 1;
			}
			sstate = 0;
		} else {
			if (sstate) {
				fp[folder_num++] = (char *) path + i;
				sstate = 0;
			}
			fstate = 1;
		}
	}
	if (folder_num == 0) {
		path[0] = '/';
		path[1] = '\0';
	}
	int j = 0;
	for (i = 1; j < folder_num; ++j) {
		int folderIndex = 0;
		for ( ; fp[j][folderIndex] != '/'; ++folderIndex) {
			path[i++] = fp[j][folderIndex];
		}
		path[i++] = '/';
	}
	path[i] = '\0';
}

bool Dir_Lib::merge_path_with_name(char *path, char *name, char *dest) {
	int i = 0;
	for ( ; path[i]; ++i) {
		dest[i] = path[i];
	}
	int j = 0;
	for ( ; name[j]; ++j, ++i) {
		dest[i] = name[j];
	}
	dest[i] = '\0';
	if (is_dir(dest)) {
		dest[i++] = '/';
		dest[i] = '\0';
		return true;
	}
	return false;
}

void Dir_Lib::get_name_from_path(char *path, char *name) {
	int path_len = strlen(path);
	int i;
	for (i = path_len; i >= 0; --i) {
		if (path_len == '/') {
			break;
		}
	}
	if (i == path_len) {
		name[0] = '\0';
	} else {
		strcpy(name, path + i + 1);
	}
}
