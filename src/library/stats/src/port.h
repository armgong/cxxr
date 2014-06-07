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
 *  Copyright (C) 2005   The R Core Team.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 */

#ifndef PORT_PORT_H
#define PORT_PORT_H

/* Header file for the C utilities to accompany the Fortran
 * optimization routines for the port library.
 *
 * Copyright (C) 2005-5  the R Core Team
 * Licensed under the GNU General Public License, version 2 or later.
 */

#include <Rinternals.h>
#include <R_ext/RS.h>

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext ("stats", String)
#else
#define _(String) (String)
#endif

/* PORT interface functions - reverse communication */

/* DRMNF(D, FX, IV, LIV, LV, N, V, X) */
extern void F77_NAME(drmnf)(double[], double*,
			    int[], int*, int*, int*, double[], double[]);

/* DRMNG(D, FX, G, IV, LIV, LV, N, V, X) */
extern void F77_NAME(drmng)(double[], double*, double[],
			    int[], int*, int*, int*, double[], double[]);

/* DRMNH(D, FX, G, H, IV, LH, LIV, LV, N, V, X) */
extern void F77_NAME(drmnh)(double[], double*, double[], double[],
			    int[], int*, int*, int*, int*, double[], double[]);

/* DRMNFB(B, D, FX, IV, LIV, LV, N, V, X) */
extern void F77_NAME(drmnfb)(double[], double[], double*,
			    int[], int*, int*, int*, double[], double[]);

/* DRMNGB(B, D, FX, G, IV, LIV, LV, N, V, X) */
extern void F77_NAME(drmngb)(double[], double[], double*, double[],
			     int[], int*, int*, int*, double[], double[]);

/* DRMNH(B, D, FX, G, H, IV, LH, LIV, LV, N, V, X) */
extern void F77_NAME(drmnhb)(double[], double[], double*, double[], double[],
			     int[], int*, int*, int*, int*, double[], double[]);

/* DRN2GB(B, D, DR, IV, LIV, LV, N, ND, N1, N2, P, R, RD, V, X) */
extern void F77_NAME(drn2gb)(double[], double[], double[],
			     int[], int*, int*, int*, int*, int*, int*, int*,
			     double[], double[], double[], double[]);
/* DRN2G(D, DR, IV, LIV, LV, N, ND, N1, N2, P, R, RD, V, X) */
extern void F77_NAME(drn2g)(double[], double[],
			    int[], int*, int*, int*, int*, int*, int*, int*,
			    double[], double[], double[], double[]);
/* DRNSGB(A, ALF, B, C, DA, IN, IV, L, L1, LA, LIV, LV, N, NDA, P, V, Y) */
extern void F77_NAME(drnsgb)(double[], double[], double[], double[], double[],
			     int[], int[], int*, int*, int*, int*,
			     int*, int*, int*, int*, int*,
			     double[], double[]);
/* DRNSG(A, ALF, C, DA, IN, IV, L, L1, LA, LIV, LV, N, NDA, P, V, Y) */
extern void F77_NAME(drnsg)(double[], double[], double[], double[],
			    int[], int[], int*, int*, int*, int*,
			    int*, int*, int*, int*, int*,
			    double[], double[]);

SEXP port_ivset(SEXP kind, SEXP iv, SEXP v);

SEXP port_nlminb(SEXP fn, SEXP gr, SEXP hs, SEXP rho,
		 SEXP lowerb, SEXP upperb, SEXP d, SEXP iv, SEXP v);

SEXP port_nlsb(SEXP m, SEXP d, SEXP gg, SEXP iv, SEXP v,
	       SEXP lowerb, SEXP upperb);

void Rf_divset(int alg, int iv[], int liv, int lv, double v[]);

void
nlminb_iterate(double b[], double d[], double fx, double g[], double h[],
	       int iv[], int liv, int lv, int n, double v[], double x[]);

void
nlsb_iterate(double b[], double d[], double dr[], int iv[], int liv,
	     int lv, int n, int nd, int p, double r[], double rd[],
	     double v[], double x[]);

#endif
