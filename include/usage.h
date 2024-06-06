#ifndef USAGE_H_
#define USAGE_H_

struct usage
{
	int h;
	int w;
	char f;
	int p;
	int m;
	double xc;  
	double yc;  
	double r;
	int conj;
};
typedef struct usage usage;

char prase(int argc, char **argv, char *options, usage *usage);
char prase_switch(int opt, usage *usage);
void check_func(char c);

#endif
