#include <stringlib.h>

int parse_args(char *argv[], char *line, int len) {
	char *cl = line;
	while (1) {
		char c = *cl;
		if (c != ' ' && c != '\t' && c != '\n') {
			break;
		}
		++cl;
	}
	for ( ; len > 0; --len) {
		char c = line[len - 1];
		if (c != ' ' && c != '\t' && c != '\n') {
			break;
		}
	}
	line[len] = '\0';
	len -= (int)(cl - line);

	int i = 0;
	int argc = 0;
	argv[argc++] = cl;
	for ( ; i < len; ++i) {
		if (cl[i] == ' ') {
			cl[i] = '\0';
			if (cl[i + 1] != ' ') {
				argv[argc++] = cl + i + 1;
			}
		}
	}
	return argc;
}

int str2int(char *str) {
	if (str == NULL) {
		return 0;
	}

	bool positive = true;
	int start = 0;
	if (str[0] == '-') {
		positive = false;
		start = 1;
	}

	int res = 0;
	int i;
	for (i = start; str[i]; ++i) {
		res *= 10;
		res += (str[i] - '0');
	}

	return positive ? res : (0 - res);
}
