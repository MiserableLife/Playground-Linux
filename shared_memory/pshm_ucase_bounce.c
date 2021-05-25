/* pshm_ucase_bounce.c

	 Licensed under GNU General Public License v2 or later.
	 */
#include <ctype.h>
#include "pshm_ucase.h"
#include <string.h>
static const char shmdir[]="/dev/shm";
char* shmpath2abspath(const char* shmpath)
{
	int len=0;
	char* abspath=0;
	len =  (shmpath[0] !='/'? 1 : 0 )  +
	strlen(shmdir)+strlen(shmpath);
	abspath = (char*)malloc(len);
	strcpy(abspath, shmdir);
	if(shmpath[0] != '/')
		strcat(abspath, "/");
	strcat(abspath, shmpath);
	return abspath;
}
	int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *shmpath = argv[1];
	const char* abs=0;
	const char* abscopy=0;
	/* Create shared memory object and set its size to the size
		 of our structure. */

	int fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
		errExit("shm_open");

	if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
		errExit("ftruncate");

	/* Map the object into the caller's address space. */

	struct shmbuf *shmp = mmap(NULL, sizeof(*shmp),
			PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0);
	if (shmp == MAP_FAILED)
		errExit("mmap");

	/* Initialize semaphores as process-shared, with value 0. */

	if (sem_init(&shmp->sem1, 1, 0) == -1)
		errExit("sem_init-sem1");
	if (sem_init(&shmp->sem2, 1, 0) == -1)
		errExit("sem_init-sem2");

	/* make a symlink with the name "copy" */
	abs = shmpath2abspath(shmpath);
	abscopy = shmpath2abspath("copy");
	symlink(abs, abscopy);


	/* Wait for 'sem1' to be posted by peer before touching
		 shared memory. */

	if (sem_wait(&shmp->sem1) == -1)
		errExit("sem_wait");

	/* Convert data in shared memory into upper case. */

	for (int j = 0; j < shmp->cnt; j++)
		shmp->buf[j] = toupper((unsigned char) shmp->buf[j]);

	/* Post 'sem2' to tell the to tell peer that it can now
		 access the modified data in shared memory. */

	if (sem_post(&shmp->sem2) == -1)
		errExit("sem_post");

	/* Unlink the shared memory object. Even if the peer process
		 is still using the object, this is okay. The object will
		 be removed only after all open references are closed. */

	shm_unlink(shmpath);

	exit(EXIT_SUCCESS);
}
