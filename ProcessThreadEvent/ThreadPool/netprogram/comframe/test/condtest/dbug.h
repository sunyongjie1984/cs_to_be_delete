#define dabort() \
 {  printf("Aborting at line %d in source file %s\n",__LINE__,__FILE__); abort(); }
 
