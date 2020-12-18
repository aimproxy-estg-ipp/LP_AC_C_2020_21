/* 
 * Created by Micael Dias on 17/12/20.
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include "util.h"
#include "irs.h"
#include "menu.h"
#include "strs.h"
#include "paths.h"
#include "error.h"

s_irs* irs_init(const char* path, int* size);
s_error* main_menu();

#endif //_MAIN_H_
