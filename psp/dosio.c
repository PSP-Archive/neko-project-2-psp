#include "compiler.h"
#include "dosio.h"
#include "pg.h"
#include "psplib.h"

static char curpath[MAX_PATH];
static char *curfilep = curpath;
static path_list_t *pl_head = NULL;

static path_list_t *add_pl(int fd, char *s)
{
    path_list_t *p;

    p = malloc(sizeof(path_list_t));
    if (p == NULL) {
        return NULL;
    }

    ZeroMemory(p, sizeof(path_list_t));

    p->fd = fd;
    strcpy(p->path, s);

    // 先頭に追加
    p->next = pl_head;
    pl_head = p;

    return p;
}

static void del_pl(int fd)
{
    path_list_t *p, *prev;

    for (p = pl_head, prev = NULL; p != NULL; prev = p, p = p->next) {
        if (p->fd == fd) {
            if (prev != NULL) {
                prev->next = p->next;
            } else {
                pl_head = p->next;
            }
            free(p);
            return;
        }
    }
    plPrintErr("fd not found");
}

// fdからpathの文字列を返す。見つかれなければNULL
static char *fd2path(int fd)
{
    path_list_t *p;

    for (p = pl_head; p != NULL; p = p->next) {
        if (p->fd == fd) {
            return p->path;
        }
    }
    return NULL;
}

static FILEH _file_open(const char* file, int mode, int fmode)
{
    int fd;

    fd = sceIoOpen(file, mode, fmode);
    if (fd < 0) {
        return FILEH_INVALID;
    }

    if (add_pl(fd, (char *)file) == NULL) {
        return FILEH_INVALID;
    }

    return fd;
}



/* ファイル操作 */

FILEH file_open(const char *path)
{
    return(_file_open(path, PSP_O_RDWR, 0777));
}

FILEH file_open_rb(const char *path)
{
    return(_file_open(path, PSP_O_RDONLY, 0777));
}

FILEH file_create(const char *path)
{
    return(_file_open(path, PSP_O_RDWR | PSP_O_CREAT, 0777));
}

long file_seek(FILEH handle, long pointer, int method)
{
    return(sceIoLseek(handle, (long long)pointer, method));
}

UINT file_read(FILEH handle, void *data, UINT length)
{
    return (sceIoRead(handle, data, length));
}

UINT file_write(FILEH handle, const void *data, UINT length)
{
    return (sceIoWrite(handle, data, length));
}

short file_close(FILEH handle)
{
    sceIoClose(handle);
    del_pl(handle);

    return(0);
}

#if 0
/** Structure to hold the status information about a file */
typedef struct SceIoStat {
    unsigned int st_mode;
    unsigned int st_attr;
    /** Size of the file in bytes. */
    unsigned int st_size;
    /** Creation time. */
    struct dirent_tm st_ctime;
    /** Access time. */
    struct dirent_tm st_atime;
    /** Modification time. */
    struct dirent_tm st_mtime;
    /** Device-specific data. */
    unsigned int    st_private[6];
} SceIoStat;
#endif

UINT file_getsize(FILEH handle)
{
    char *s;
    SceIoStat p;

    s = fd2path(handle);
    if (s == NULL) {
        return 0;
    }

    sceIoGetstat(s, &p);

    return(p.st_size);
}

short file_getdatetime(FILEH handle, DOSDATE *dosdate, DOSTIME *dostime)
{
	return(-1);
}

short file_delete(const char *path)
{
	return(-1);
}

short file_attr(const char *path)
{
    return 0; // とりあえず0 typeはdosio.hで定義FILEATTR_
}

short file_dircreate(const char *path)
{
	return(-1);
}


/* カレントファイル操作 */
void file_setcd(const char *exepath)
{
    file_cpyname(curpath, exepath, sizeof(curpath));
    curfilep = file_getname(curpath);
    *curfilep = '\0';
}

char *file_getcd(const char *path)
{
    file_cpyname(curfilep, path, sizeof(curpath) - (curfilep - curpath));
    return(curpath);
}

FILEH file_open_c(const char *path)
{
    file_cpyname(curfilep, path, sizeof(curpath) - (curfilep - curpath));
    return(file_open(curpath));
}

FILEH file_open_rb_c(const char *path)
{
    file_cpyname(curfilep, path, sizeof(curpath) - (curfilep - curpath));
    return(file_open_rb(curpath));
}

FILEH file_create_c(const char *path)
{
    file_cpyname(curfilep, path, sizeof(curpath) - (curfilep - curpath));
    return(file_create(curpath));
}

short file_delete_c(const char *path)
{
    file_cpyname(curfilep, path, sizeof(curpath) - (curfilep - curpath));
    return(file_delete(curpath));
}

short file_attr_c(const char *path)
{
    file_cpyname(curfilep, path, sizeof(curpath) - (curfilep - curpath));
    return(file_attr_c(curpath));
}

static void setflist(SceIoDirent *de, FLINFO *fli)
{
    //    static int y = 3;
    fli->caps = FLICAPS_SIZE | FLICAPS_ATTR;
    fli->size = de->d_stat.st_size;
    fli->attr = 0x01; //とりあえず0x01
//    cnvdatetime(&w32fd->ftLastWriteTime, &fli->date, &fli->time);
    milstr_ncpy(fli->path, de->d_name, NELEMENTS(fli->path));
}

SceIoDirent files;

FLISTH file_list1st(const char *dir, FLINFO *fli)
{
    int fd;

    ZeroMemory(&files, sizeof(files));

    fd = sceIoDopen(dir);
    if (fd == 0) {
        plPrintErr("sceIoDopen() failed");
        return FLISTH_INVALID;
    }

    while(1) {
        if (sceIoDread(fd, &files) <= 0) {
            plPrintErr("sceIoDread() faild");
            break;
        }
        if (files.d_name[0] == '.')
            continue;
        if (files.d_stat.st_attr == FIO_SO_IFDIR) {
            strcat(files.d_name, "/");
        }
        setflist(&files, fli);
        return fd;
    }
    return FLISTH_INVALID;
}

BOOL file_listnext(FLISTH hdl, FLINFO *fli)
{
    while (1) {
        if (sceIoDread(hdl, &files) <= 0)
            return FAILURE;
        if (files.d_name[0] == '.')
            continue;
        if (files.d_stat.st_attr == FIO_SO_IFDIR) {
            strcat(files.d_name, "/");
        }
        setflist(&files, fli);
        return SUCCESS;
    }
}

void file_listclose(FLISTH hdl)
{
    sceIoDclose(hdl);
}

void file_catname(char *path, const char *name, int maxlen) {

	int		csize;

	while(maxlen > 0) {
		if (*path == '\0') {
			break;
		}
		path++;
		maxlen--;
	}
	file_cpyname(path, name, maxlen);
	while((csize = milstr_charsize(path)) != 0) {
		if ((csize == 1) && (*path == '\\')) {
			*path = '/';
		}
		path += csize;
	}
}

char *file_getname(const char *path) {

const char	*ret;
	int		csize;

	ret = path;
	while((csize = milstr_charsize(path)) != 0) {
		if ((csize == 1) && (*path == '/')) {
			ret = path + 1;
		}
		path += csize;
	}
	return((char *)ret);
}

void file_cutname(char *path) {

	char	*p;

	p = file_getname(path);
	*p = '\0';
}

char *file_getext(const char *path) {

const char	*p;
const char	*q;

	p = file_getname(path);
	q = NULL;
	while(*p != '\0') {
		if (*p == '.') {
			q = p + 1;
		}
		p++;
	}
	if (q == NULL) {
		q = p;
	}
	return((char *)q);
}

void file_cutext(char *path) {

	char	*p;
	char	*q;

	p = file_getname(path);
	q = NULL;
	while(*p != '\0') {
		if (*p == '.') {
			q = p;
		}
		p++;
	}
	if (q != NULL) {
		*q = '\0';
	}
}

void file_cutseparator(char *path) {

	int		pos;

	pos = strlen(path) - 1;
	if ((pos > 0) &&							// 2文字以上でー
		(path[pos] == '/') &&					// ケツが \ でー
		((pos != 1) || (path[0] != '.'))) {		// './' ではなかったら
		path[pos] = '\0';
	}
}

void file_setseparator(char *path, int maxlen) {

	int		pos;

	pos = strlen(path);
	if ((pos) && (path[pos-1] != '/') && ((pos + 2) < maxlen)) {
		path[pos++] = '/';
		path[pos] = '\0';
	}
}

