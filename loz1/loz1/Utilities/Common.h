#ifndef COMMON_H
#define COMMON_H

#include<time.h>
#include<tchar.h>

#define MSGBOX(s) ::MessageBox(0,_T(s),0,MB_OK);

#define SAFE_DELETE(p) {\
	if(p){\
		delete (p);\
		(p) = NULL;\
	}\
}
#define SAFE_DELETE_ARRAY(p) {\
	if(p){\
		delete [] (p);\
		(p) = NULL;\
	}\
}

#define FRAND(r) ((float)rand()/((float)RAND_MAX/(r)))

#endif