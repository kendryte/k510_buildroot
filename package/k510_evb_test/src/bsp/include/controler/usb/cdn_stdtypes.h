/**********************************************************************
 * Copyright (C) 2014 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * cdn_stdtypes.h
 * Cadence types and definitions
 ***********************************************************************/

#ifndef __INCLUDE_CDN_STDTYPES_H___
#define	__INCLUDE_CDN_STDTYPES_H___

#include "cdn_stdint.h"

/* Define NULL constant */
#ifndef NULL
#define	NULL	((void *)0)
#endif

/* Define size_t data type */
typedef	uintptr_t	size_t;

/* Define bool data type */
#define bool	_Bool
#define	true	1
#define	false	0
#define	__bool_true_false_are_defined 1

#endif	/* __INCLUDE_CDN_STDTYPES_H__ */
