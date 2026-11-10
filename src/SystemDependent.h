/*********************************************************************************
 *                                                                                *
 *                       Source code developed by the    * Imaging Research
 * Laboratory - University of Washington               * (C) Copyright
 * 1994-2012 Department of Radiology                  * University of
 * Washington                             * All Rights Reserved
 *               *
 *                                                                                *
 *********************************************************************************/

/*********************************************************************************
 *
 *			Module Name:		SystemDependent.h
 *			Revision Number:	1.4
 *			Date last revised:	19 December 2012
 *			Programmer:			Robert Harrison
 *			Date Originated:	8 Dec 2001
 *
 *			Module Overview:	An attempt to consolidate the
 * OS-specific library includes
 *
 *			References:
 *
 **********************************************************************************
 *
 *			Global functions defined:
 *
 *			Global variables defined:		none
 *
 **********************************************************************************
 *
 *			Revision Section (Also update version number, if
 * relevant)
 *
 *			Programmer(s):
 *
 *			Revision date:
 *
 *			Revision description:
 *
 **********************************************************************************
 *
 *			Revision Section (Also update version number, if
 * relevant)
 *
 *			Programmer(s):		Steven Gillispie
 *
 *			Revision date:		20 November 2003
 *
 *			Revision description:	Added changes for Mac CW 9
 * compatibility: Removed obsolete #includes
 *
 *********************************************************************************/

#include <errno.h>
#include <stdlib.h>

#ifdef __MWERKS__
#include <Errors.h>
#include <String.h>
#include <Types.h>
#include <ctype.h>
#include <float.h>
#include <fp.h>
#include <limits.h>
#include <math.h>
#define MAXFLOAT FLT_MAX
#include <SIOUX.h>
#include <console.h>
#endif

/* old metroworks definition
#ifdef MWC
        #include 	<Math.h>
        #include 	<fp.h>
        #define		MAXFLOAT	FLT_MAX
#endif
*/

#ifdef DGUX
#include <math.h>
#include <sys/m88kbcs.h>
#include <values.h>
#elif MPW
#include <CursorCtl.h>
#include <ErrMgr.h>
#include <Errors.h>
#include <Types.h>
#include <ctype.h>
#elif __USE_TWRP__
#include "TWrapper.h"
#include "TWrpDoc.h"
#include "TWrpLib.h"
#define APP_DEBUG
#elif defined GEN_UNIX
#include <float.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>
#include <values.h>

#ifdef LINUX
#define MAXFLOAT FLT_MAX
#endif

#elif defined AOS_VS
#include <math.h>
#elif defined WINNT
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
//	#include 	<fp.h>
#include <ctype.h> // need include this inorder to use tolower()
#define MAXFLOAT FLT_MAX
/* windows doesn't have a built-in strtoll, copysign, so we #define
 * them here... */
#define strtoll _strtoi64
#define copysign(val, signval)                                                \
  (((signval) < 0) ? (-fabs (val)) : (fasbs (val)))
#elif defined DARWIN
#include <float.h>
#include <limits.h>
#include <math.h>
#include <sys/times.h>
#include <unistd.h>
#elif defined OSX
#include <float.h>
#include <limits.h>
#include <math.h>
#include <sys/times.h>
#include <unistd.h>
#elif defined COCOA
#include <float.h>
#include <limits.h>
#include <math.h>
#include <sys/times.h>
#include <unistd.h>
#endif

/* old sun definition
#ifdef SUN_OS
        #include 	<unistd.h>
#endif
*/
