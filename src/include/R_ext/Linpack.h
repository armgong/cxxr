/*CXXR $Id$
 *CXXR
 *CXXR This file is part of CXXR, a project to refactor the R interpreter
 *CXXR into C++.  It may consist in whole or in part of program code and
 *CXXR documentation taken from the R project itself, incorporated into
 *CXXR CXXR (and possibly MODIFIED) under the terms of the GNU General Public
 *CXXR Licence.
 *CXXR 
 *CXXR CXXR is Copyright (C) 2008-14 Andrew R. Runnalls, subject to such other
 *CXXR copyrights and copyright restrictions as may be stated below.
 *CXXR 
 *CXXR CXXR is not part of the R project, and bugs and other issues should
 *CXXR not be reported via r-bugs or other R project channels; instead refer
 *CXXR to the CXXR website.
 *CXXR */

/*
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 1997        Robert Gentleman and Ross Ihaka
 *  Copyright (C) 1999-2002   The R Core Team.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 */

/* 
   C declarations of double-precision LINPACK Fortran subroutines
   included in R, and some others.
   
   Those which are listed as part of R are in the API
 */

#ifndef R_LINPACK_H_
#define R_LINPACK_H_

#include <R_ext/RS.h>		/* for F77_... */
#include <R_ext/BLAS.h>

#ifdef  __cplusplus
extern "C" {
#endif

	/* Double Precision Linpack */

extern void F77_NAME(dpbfa)(double*, int*, int*, int*, int*);
extern void F77_NAME(dpbsl)(double*, int*, int*, int*, double*);
extern void F77_NAME(dpoco)(double*, int*, int*, double*, double*, int*);
extern void F77_NAME(dpodi)(double*, int*, int*, double*, int*);
extern void F77_NAME(dpofa)(double*, int*, int*, int*);
extern void F77_NAME(dposl)(double*, int*, int*, double*);
extern void F77_NAME(dqrdc)(double*, int*, int*, int*, double*, int*, double*, int*);
extern void F77_NAME(dqrsl)(double*, int*, int*, int*, double*, double*, double*, double*, double*, double*, double*, int*, int*);
extern void F77_NAME(dsvdc)(double*, int*, int*, int*, double*, double*, double*, int*, double*, int*, double*, int*, int*);
extern void F77_NAME(dtrco)(double*, int*, int*, double*, double*, int*);
extern void F77_NAME(dtrsl)(double*, int*, int*, double*, int*, int*);


/* The following routines are listed as they have always been declared
   here, but they are not currently included in R */
extern void F77_NAME(dchdc)(double*, int*, int*, double*, int*, int*, int*);
extern void F77_NAME(dchdd)(double*, int*, int*, double*, double*, int*, int*, double*, double*, double*, double*, int*);
extern void F77_NAME(dchex)(double*, int*, int*, int*, int*, double*, int*, int*, double*, double*, int*);
extern void F77_NAME(dchud)(double*, int*, int*, double*, double*, int*, int*, double*, double*, double*, double*);
extern void F77_NAME(dgbco)(double*, int*, int*, int*, int*, int*, double*, double*);
extern void F77_NAME(dgbdi)(double*, int*, int*, int*, int*, int*, double*);
extern void F77_NAME(dgbfa)(double*, int*, int*, int*, int*, int*, int*);
extern void F77_NAME(dgbsl)(double*, int*, int*, int*, int*, int*, double*, int*);
extern void F77_NAME(dgeco)(double*, int*, int*, int*, double*, double*);
extern void F77_NAME(dgedi)(double*, int*, int*, int*, double*, double*, int*);
extern void F77_NAME(dgefa)(double*, int*, int*, int*, int*);
extern void F77_NAME(dgesl)(double*, int*, int*, int*, double*, int*);
extern void F77_NAME(dgtsl)(int*, double*, double*, double*, double*, int*);
extern void F77_NAME(dpbco)(double*, int*, int*, int*, double*, double*, int*);
extern void F77_NAME(dpbdi)(double*, int*, int*, int*, double*);
extern void F77_NAME(dppco)(double*, int*, double*, double*, int*);
extern void F77_NAME(dppdi)(double*, int*, double*, int*);
extern void F77_NAME(dppfa)(double*, int*, int*);
extern void F77_NAME(dppsl)(double*, int*, double*);
extern void F77_NAME(dptsl)(int*, double*, double*, double*);
extern void F77_NAME(dsico)(double*, int*, int*, int*, double*, double*);
extern void F77_NAME(dsidi)(double*, int*, int*, int*, double*, int*, double*, int*);
extern void F77_NAME(dsifa)(double*, int*, int*, int*, int*);
extern void F77_NAME(dsisl)(double*, int*, int*, int*, double*);
extern void F77_NAME(dspco)(double*, int*, int*, double*, double*);
extern void F77_NAME(dspdi)(double*, int*, int*, double*, int*, double*, int*);
extern void F77_NAME(dspfa)(double*, int*, int*, int*);
extern void F77_NAME(dspsl)(double*, int*, int*, double*);

#ifdef  __cplusplus
}
#endif

#endif /* R_LINPACK_H_ */
