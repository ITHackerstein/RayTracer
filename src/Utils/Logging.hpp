#pragma once

#define _DUMP_INDENT_SIZE 2

inline void print_indent(int indent) {
	for (int i = 0; i < indent; ++i) {
		for (int j = 0; j < _DUMP_INDENT_SIZE; ++j) {
			printf(" ");
		}
	}
}
