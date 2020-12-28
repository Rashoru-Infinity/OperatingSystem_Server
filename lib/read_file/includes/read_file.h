#ifndef READ_FILE_H
#define READ_FILE_H

typedef enum {
	success,
	fail
} t_status;

char	*read_file(const char *file_name, size_t buffer_size);

#endif
