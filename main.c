#include <stdio.h>
#include <time.h>
#include <direct.h>
#include <io.h>

#define safefree(p) safefree((void **)&(p))
#define _MAX_FNAME 256
#define ADDR ".\\*.c"
 
const char* SreachAddr=ADDR;

typedef struct _finddata {
    unsigned int attrib;
    time_t time_create;
    time_t time_access;
    time_t time_write;
    _fsize_t size;
    char name[_MAX_FNAME];
} Fileinfo;

void safe_free(void **p) {
    if (p != NULL && *p != NULL) {
        free(*p);
        *p = NULL;
    }
}

char *gettime() {
    time_t timep;
    char *time_n = (char *)malloc(30 * sizeof(char));
    time(&timep);
    strcpy(time_n, asctime(gmtime(&timep)));
    return time_n;
    safefree(time_n);
}

char *getpath() {
    char *path = (char *)malloc(100 * sizeof(char));
    getcwd(path, 100);
    return path;
    safefree(path);
}

int findfile() {
    long Handle;
	struct _finddata_t FileInfo;
	Handle=_findfirst(SreachAddr,&FileInfo);
	if(-1==Handle)
		return -1;
	printf("%s\n",FileInfo.name);
	while(!_findnext(Handle,&FileInfo))
	{
		printf("%s\n",FileInfo.name);
	}
	_findclose(Handle);
	return 0;
}

int main() {
    printf("At %s compile file in %s \n", gettime(), getpath());
    printf("Find the c file:\n");
    findfile();
    system("pause");
    return 0;
}
