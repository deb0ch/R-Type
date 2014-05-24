#ifndef UNISTD_H_
#define UNISTD_H_

#ifdef _WIN32

/**
 * This file replacement unistd.h on Windows
 */

#include <stdlib.h>
#include <io.h>
#include <process.h> /* for getpid() and the exec..() family */
#include <direct.h> /* for _getcwd() and _chdir() */

/* Values for the second argument to access */
#define R_OK    4 /* Test for read permission.  */
#define W_OK    2 /* Test for write permission.  */
#define F_OK    0 /* Test for existence.  */

#define access _access
#define dup2 _dup2
#define execve _execve
#define ftruncate _chsize
#define unlink _unlink
#define fileno _fileno
#define getcwd _getcwd
#define chdir _chdir
#define isatty _isatty
#define lseek _lseek
#define srandom srand
#define random rand

#define ssize_t int

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
/* should be in some equivalent to <sys/types.h> */
typedef __int8            int8_t;
typedef __int16           int16_t;
typedef __int32           int32_t;
typedef __int64           int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;

#define __PRETTY_FUNCTION__ __FUNCTION__

#elif __linux__
#include <unistd.h>
#endif /* _WIN32*/

#endif /* !UNISTD_H_ */
