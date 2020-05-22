#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for setreuid()
#include <sys/types.h>
#include <unistd.h>

extern char **environ;

// tired of fixing values...
// - morla
unsigned long get_sp(void) {
       __asm__("movl %esp,%eax\n\t"
               "and $0xff000000, %eax"
               );
}

int main(int argc, char *argv[]){
	char b1[8], b2[8];
	int  (*fp)(char *)=(int(*)(char *))&puts, i;

	if(argc!=3){ printf("%s b1 b2\n", argv[0]); exit(-1); }

	/* clear environ */
	for(i=0; environ[i] != NULL; i++)
		memset(environ[i], '\0', strlen(environ[i]));
	/* clear argz    */
	for(i=3; argv[i] != NULL; i++)
		memset(argv[i], '\0', strlen(argv[i]));

	strcpy(b1,argv[1]);
	strcpy(b2,argv[2]);
	//if(((unsigned long)fp & 0xff000000) == 0xff000000)

	/* Hmm... unsure what these values are. Let's print them out! */
	printf("DEBUG: fp = %08lx\n", (unsigned long)fp);
	printf("DEBUG: fp & 0xff000000 = %08lx\n", (unsigned long)fp & 0xff000000);
	printf("DEBUG: get_sp() = %08lx\n", get_sp());

	if(((unsigned long)fp & 0xff000000) == get_sp())
		exit(-1);
	setreuid(geteuid(),geteuid());
	fp(b1);

	exit(1);
}

