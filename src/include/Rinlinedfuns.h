/*
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 1995, 1996  Robert Gentleman and Ross Ihaka
 *  Copyright (C) 1999-2007   The R Development Core Team.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 */

/* this header is always to be included from others.
   It is only called if COMPILING_R is defined (in util.c) or
   from GNU C systems.

   There are different conventions for inlining across compilation units.
   See http://www.greenend.org.uk/rjk/2003/03/inline.html
 */
#ifndef R_INLINES_H_
#define R_INLINES_H_

#ifndef __cplusplus
#define RBOOL(x) x
#else
#define RBOOL(x) Rboolean(x)

extern "C" {
#endif /* __cplusplus */

/* Probably not able to use C99 semantics in gcc < 4.3.0 but who knows what
   unofficial versions Debian or RedHat will distribute */
#if __GNUC__ == 4 && __GNUC_MINOR__ >= 3 && defined(__GNUC_STDC_INLINE__) && !defined(C99_INLINE_SEMANTICS)
#define C99_INLINE_SEMANTICS 1
#endif

/* Apple's gcc build >5400 (since Xcode 3.0) doesn't support GNU inline in C99 mode */
#if __APPLE_CC__ > 5400 && !defined(C99_INLINE_SEMANTICS)
#define C99_INLINE_SEMANTICS 1
#endif

#ifdef COMPILING_R
/* defined only in inlined.c: this emits standalone code there */
# define INLINE_FUN
#else
/* This section is normally only used for versions of gcc which do not
   support C99 semantics.  __GNUC_STDC_INLINE__ is defined if
   GCC is following C99 inline semantics by default: we
   switch R's usage to the older GNU semantics via attributes.
   Do this even for __GNUC_GNUC_INLINE__ to shut up warnings in 4.2.x.
   __GNUC_STDC_INLINE__ and __GNUC_GNU_INLINE__ were added in gcc 4.2.0.
*/
# if defined(__GNUC_STDC_INLINE__) || defined(__GNUC_GNU_INLINE__)
#  define INLINE_FUN extern __attribute__((gnu_inline)) inline
# else
#  define INLINE_FUN extern R_INLINE
# endif
#endif /* ifdef COMPILING_R */

#if C99_INLINE_SEMANTICS
# undef INLINE_FUN
# ifdef COMPILING_R
/* force exported copy */
#  define INLINE_FUN extern inline
# else
/* either inline or link to extern version at compiler's choice */
#  define INLINE_FUN inline
# endif /* ifdef COMPILING_R */
#endif /* C99_INLINE_SEMANTICS */


#include <string.h> /* for strlen, strcmp */

/* define inline-able functions */


/* from dstruct.c */

/*  length - length of objects  */

int Rf_envlength(SEXP rho);

INLINE_FUN R_len_t Rf_length(SEXP s)
{
    int i;
    switch (TYPEOF(s)) {
    case NILSXP:
	return 0;
    case LGLSXP:
    case INTSXP:
    case REALSXP:
    case CPLXSXP:
    case STRSXP:
    case CHARSXP:
    case VECSXP:
    case EXPRSXP:
    case RAWSXP:
	return LENGTH(s);
    case LISTSXP:
    case LANGSXP:
    case DOTSXP:
	i = 0;
	while (s != NULL && s != R_NilValue) {
	    i++;
	    s = CDR(s);
	}
	return i;
    case ENVSXP:
	return Rf_envlength(s);
    default:
	return 1;
    }
}


/* from list.c */
/* Return a dotted pair with the given CAR and CDR. */
/* The (R) TAG slot on the cell is set to NULL. */


/* Get the i-th element of a list */
INLINE_FUN SEXP Rf_elt(SEXP list, int i)
{
    int j;
    SEXP result = list;

    if ((i < 0) || (i > Rf_length(list)))
	return R_NilValue;
    else
	for (j = 0; j < i; j++)
	    result = CDR(result);

    return CAR(result);
}


/* Return the last element of a list */
INLINE_FUN SEXP Rf_lastElt(SEXP list)
{
    SEXP result = R_NilValue;
    while (list != R_NilValue) {
	result = list;
	list = CDR(list);
    }
    return result;
}


/* Shorthands for creating small lists */

INLINE_FUN SEXP Rf_list1(SEXP s)
{
    return CONS(s, R_NilValue);
}


INLINE_FUN SEXP Rf_list2(SEXP s, SEXP t)
{
    PROTECT(s);
    s = CONS(s, Rf_list1(t));
    UNPROTECT(1);
    return s;
}


INLINE_FUN SEXP Rf_list3(SEXP s, SEXP t, SEXP u)
{
    PROTECT(s);
    s = CONS(s, Rf_list2(t, u));
    UNPROTECT(1);
    return s;
}


INLINE_FUN SEXP Rf_list4(SEXP s, SEXP t, SEXP u, SEXP v)
{
    PROTECT(s);
    s = CONS(s, Rf_list3(t, u, v));
    UNPROTECT(1);
    return s;
}


/* Destructive list append : See also ``append'' */

INLINE_FUN SEXP Rf_listAppend(SEXP s, SEXP t)
{
    SEXP r;
    if (s == R_NilValue)
	return t;
    r = s;
    while (CDR(r) != R_NilValue)
	r = CDR(r);
    SETCDR(r, t);
    return s;
}


/* Language based list constructs.  These are identical to the list */
/* constructs, but the results can be evaluated. */

/* Return a (language) dotted pair with the given car and cdr */

INLINE_FUN SEXP Rf_lcons(SEXP car, SEXP cdr)
{
    SEXP e = Rf_cons(car, cdr);
    SET_TYPEOF(e, LANGSXP);
    return e;
}

INLINE_FUN SEXP Rf_lang1(SEXP s)
{
    return LCONS(s, R_NilValue);
}

INLINE_FUN SEXP Rf_lang2(SEXP s, SEXP t)
{
    PROTECT(s);
    s = LCONS(s, Rf_list1(t));
    UNPROTECT(1);
    return s;
}

INLINE_FUN SEXP Rf_lang3(SEXP s, SEXP t, SEXP u)
{
    PROTECT(s);
    s = LCONS(s, Rf_list2(t, u));
    UNPROTECT(1);
    return s;
}

INLINE_FUN SEXP Rf_lang4(SEXP s, SEXP t, SEXP u, SEXP v)
{
    PROTECT(s);
    s = LCONS(s, Rf_list3(t, u, v));
    UNPROTECT(1);
    return s;
}

/* from util.c */

/* Check to see if the arrays "x" and "y" have the identical extents */

INLINE_FUN Rboolean Rf_conformable(SEXP x, SEXP y)
{
    int i, n;
    PROTECT(x = Rf_getAttrib(x, R_DimSymbol));
    y = Rf_getAttrib(y, R_DimSymbol);
    UNPROTECT(1);
    if ((n = Rf_length(x)) != Rf_length(y))
	return FALSE;
    for (i = 0; i < n; i++)
	if (INTEGER(x)[i] != INTEGER(y)[i])
	    return FALSE;
    return TRUE;
}

INLINE_FUN Rboolean Rf_inherits(SEXP s, const char *name)
{
    SEXP klass;
    int i, nclass;
    if (OBJECT(s)) {
	klass = Rf_getAttrib(s, R_ClassSymbol);
	nclass = Rf_length(klass);
	for (i = 0; i < nclass; i++) {
	    if (!strcmp(CHAR(STRING_ELT(klass, i)), name))
		return TRUE;
	}
    }
    return FALSE;
}

INLINE_FUN Rboolean Rf_isValidString(SEXP x)
{
    return RBOOL(TYPEOF(x) == STRSXP && LENGTH(x) > 0
		 && TYPEOF(STRING_ELT(x, 0)) != NILSXP);
}

/* non-empty ("") valid string :*/
INLINE_FUN Rboolean Rf_isValidStringF(SEXP x)
{
    return RBOOL(Rf_isValidString(x) && CHAR(STRING_ELT(x, 0))[0]);
}

INLINE_FUN Rboolean Rf_isUserBinop(SEXP s)
{
    if (TYPEOF(s) == SYMSXP) {
	const char *str = CHAR(PRINTNAME(s));
	if (strlen(str) >= 2 && str[0] == '%' && str[strlen(str)-1] == '%')
	    return TRUE;
    }
    return FALSE;
}

INLINE_FUN Rboolean Rf_isFunction(SEXP s)
{
    return RBOOL(TYPEOF(s) == CLOSXP ||
		 TYPEOF(s) == BUILTINSXP ||
		 TYPEOF(s) == SPECIALSXP);
}

INLINE_FUN Rboolean Rf_isPrimitive(SEXP s)
{
    return RBOOL(TYPEOF(s) == BUILTINSXP ||
		 TYPEOF(s) == SPECIALSXP);
}

INLINE_FUN Rboolean Rf_isList(SEXP s)
{
    return RBOOL(s == R_NilValue || TYPEOF(s) == LISTSXP);
}


INLINE_FUN Rboolean Rf_isNewList(SEXP s)
{
    return RBOOL(s == R_NilValue || TYPEOF(s) == VECSXP);
}

INLINE_FUN Rboolean Rf_isPairList(SEXP s)
{
    switch (TYPEOF(s)) {
    case NILSXP:
    case LISTSXP:
    case LANGSXP:
	return TRUE;
    default:
	return FALSE;
    }
}

INLINE_FUN Rboolean Rf_isVectorList(SEXP s)
{
    switch (TYPEOF(s)) {
    case VECSXP:
    case EXPRSXP:
	return TRUE;
    default:
	return FALSE;
    }
}

INLINE_FUN Rboolean Rf_isVectorAtomic(SEXP s)
{
    switch (TYPEOF(s)) {
    case LGLSXP:
    case INTSXP:
    case REALSXP:
    case CPLXSXP:
    case STRSXP:
    case RAWSXP:
	return TRUE;
    default: /* including NULL */
	return FALSE;
    }
}

INLINE_FUN Rboolean Rf_isVector(SEXP s)/* === Rf_isVectorList() or Rf_isVectorAtomic() */
{
    switch(TYPEOF(s)) {
    case LGLSXP:
    case INTSXP:
    case REALSXP:
    case CPLXSXP:
    case STRSXP:
    case RAWSXP:

    case VECSXP:
    case EXPRSXP:
	return TRUE;
    default:
	return FALSE;
    }
}

INLINE_FUN Rboolean Rf_isFrame(SEXP s)
{
    SEXP klass;
    int i;
    if (OBJECT(s)) {
	klass = Rf_getAttrib(s, R_ClassSymbol);
	for (i = 0; i < Rf_length(klass); i++)
	    if (!strcmp(CHAR(STRING_ELT(klass, i)), "data.frame")) return TRUE;
    }
    return FALSE;
}

INLINE_FUN Rboolean Rf_isLanguage(SEXP s)
{
    return RBOOL(s == R_NilValue || TYPEOF(s) == LANGSXP);
}

INLINE_FUN Rboolean Rf_isMatrix(SEXP s)
{
    SEXP t;
    if (Rf_isVector(s)) {
	t = Rf_getAttrib(s, R_DimSymbol);
	/* You are not supposed to be able to assign a non-integer dim,
	   although this might be possible by misuse of ATTRIB. */
	if (TYPEOF(t) == INTSXP && LENGTH(t) == 2)
	    return TRUE;
    }
    return FALSE;
}

INLINE_FUN Rboolean Rf_isArray(SEXP s)
{
    SEXP t;
    if (Rf_isVector(s)) {
	t = Rf_getAttrib(s, R_DimSymbol);
	/* You are not supposed to be able to assign a 0-length dim,
	 nor a non-integer dim */
	if (TYPEOF(t) == INTSXP && LENGTH(t) > 0)
	    return TRUE;
    }
    return FALSE;
}

INLINE_FUN Rboolean Rf_isTs(SEXP s)
{
    return RBOOL(Rf_isVector(s) && Rf_getAttrib(s, R_TspSymbol) != R_NilValue);
}

INLINE_FUN Rboolean Rf_isInteger(SEXP s)
{
    return RBOOL(TYPEOF(s) == INTSXP && !Rf_inherits(s, "factor"));
}

INLINE_FUN Rboolean Rf_isFactor(SEXP s)
{
    return RBOOL(TYPEOF(s) == INTSXP  && Rf_inherits(s, "factor"));
}

INLINE_FUN int Rf_nlevels(SEXP f)
{
    if (!Rf_isFactor(f))
	return 0;
    return LENGTH(Rf_getAttrib(f, R_LevelsSymbol));
}

/* Is an object of numeric type. */
/* FIXME:  the LGLSXP case should be excluded here
 * (really? in many places we affirm they are treated like INTs)*/

INLINE_FUN Rboolean Rf_isNumeric(SEXP s)
{
    switch(TYPEOF(s)) {
    case INTSXP:
	if (Rf_inherits(s,"factor")) return FALSE;
    case LGLSXP:
    case REALSXP:
	return TRUE;
    default:
	return FALSE;
    }
}

/* As from R 2.4.0 we check that the value is allowed. */
INLINE_FUN SEXP Rf_ScalarLogical(int x)
{
    SEXP ans = Rf_allocVector(LGLSXP, 1);
    if (x == NA_LOGICAL) LOGICAL(ans)[0] = NA_LOGICAL;
    else LOGICAL(ans)[0] = (x != 0);
    return ans;
}

INLINE_FUN SEXP Rf_ScalarInteger(int x)
{
    SEXP ans = Rf_allocVector(INTSXP, 1);
    INTEGER(ans)[0] = x;
    return ans;
}

INLINE_FUN SEXP Rf_ScalarReal(double x)
{
    SEXP ans = Rf_allocVector(REALSXP, 1);
    REAL(ans)[0] = x;
    return ans;
}


INLINE_FUN SEXP Rf_ScalarComplex(Rcomplex x)
{
    SEXP ans = Rf_allocVector(CPLXSXP, 1);
    COMPLEX(ans)[0] = x;
    return ans;
}

INLINE_FUN SEXP Rf_ScalarString(SEXP x)
{
    SEXP ans;
    PROTECT(x);
    ans = Rf_allocVector(STRSXP, 1);
    SET_STRING_ELT(ans, 0, x);
    UNPROTECT(1);
    return ans;
}

INLINE_FUN SEXP Rf_ScalarRaw(Rbyte x)
{
    SEXP ans = Rf_allocVector(RAWSXP, 1);
    RAW(ans)[0] = x;
    return ans;
}

/* Check to see if a list can be made into a vector. */
/* it must have every element being a vector of length 1. */
/* BUT it does not exclude 0! */

INLINE_FUN Rboolean Rf_isVectorizable(SEXP s)
{
    if (s == R_NilValue) return TRUE;
    else if (Rf_isNewList(s)) {
	int i, n;

	n = LENGTH(s);
	for (i = 0 ; i < n; i++)
	    if (!Rf_isVector(VECTOR_ELT(s, i)) || LENGTH(VECTOR_ELT(s, i)) > 1)
		return FALSE;
	return TRUE;
    }
    else if (Rf_isList(s)) {
	for ( ; s != R_NilValue; s = CDR(s))
	    if (!Rf_isVector(CAR(s)) || LENGTH(CAR(s)) > 1) return FALSE;
	return TRUE;
    }
    else return FALSE;
}


/* from gram.y */

INLINE_FUN SEXP Rf_mkString(const char *s)
{
    SEXP t;

    PROTECT(t = Rf_allocVector(STRSXP, 1));
    SET_STRING_ELT(t, 0, Rf_mkChar(s));
    UNPROTECT(1);
    return t;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* R_INLINES_H_ */
