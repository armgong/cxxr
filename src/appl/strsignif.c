/*
 *  Copyright (C) Martin Maechler, 1994, 1998
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
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  I want you to preserve the copyright of the original author(s),
 *  and encourage you to send me any improvements by e-mail. (MM).
 *
 *  Originally from Bill Dunlap
 *  bill@stat.washington.edu
 *  Wed Feb 21, 1990
 *
 *  Much improved by Martin Maechler, including the "fg" format.
 *
 *  Patched by Friedrich.Leisch@ci.tuwien.ac.at
 *  Fri Nov 22, 1996
 *
 *  Some fixes by Ross Ihaka
 *  ihaka@stat.auckland.ac.nz
 *  Sat Dec 21, 1996
 *  Integer arguments changed from "long" to "int"
 *  Bus error due to non-writable strings fixed
 *
 *	type	"double" or "integer" (R - numeric `mode').
 *
 *	width	The total field width; width < 0 means to left justify
 *		the number in this field (equivalent to flag = "-").
 *		It is possible that the result will be longer than this,
 *		but that should only happen in reasonable cases.
 *
 *	digits	The desired number of digits after the decimal point.
 *		digits < 0 uses the default for C, namely 6 digits.
 *
 *	format	"d" (for integers) or "f", "e","E", "g", "G" (for 'real')
 *		"f" gives numbers in the usual "xxx.xxx" format;
 *		"e" and "E" give n.ddde<nn> or n.dddE<nn> (scientific format);
 *		"g" and "G" puts them into scientific format if it saves
 *		space to do so.
 *	    NEW: "fg" gives numbers in "xxx.xxx" format as "f",
 *		  ~~  however, digits are *significant* digits and no
 *		      trailing zeros are produced, as in "g".
 *
 *	flag	Format modifier as in K&R "C", 2nd ed., p.243;
 *		e.g., "0" pads leading zeros; "-" does left adjustment
 *		the other possible flags are  "+", " ", and "#".
 *	  New (Feb.98): if flag has more than one character, all are passed..
 */

#ifdef HAVE_CONFIG_H
#include <Rconfig.h>
#endif

#include <stdio.h>
#include <string.h>
#include <math.h>

void str_signif(char *x, int *n, char **type, int *width, int *digits,
	char **format, char **flag, char **result)
{
	int wid = *width;
	int dig = *digits;
	int i, nn = *n;
	int short do_fg = !strcmp("fg",*format);/* == 1	 iff  format == "fg" */
	double xx;
	int iex, j, jL;


	void error(char*);
	char f0[12], form[12]; /* ---- Really, instead :
	  char *form;
	  form = Calloc(strlen(*flag)+strlen(*format)+ 4+1, char);
	*/

	if (wid == 0) error("Width cannot be zero");

	if (strcmp("d", *format) == 0) {
		if (strlen(*flag) == 0) strcpy(form, "%*d");
		else {
			strcpy(form, "%");
			strcat(form, *flag);
			strcat(form, "*d");
		}
		if (strcmp("integer", *type) == 0)
		  for (i=0; i < nn; i++)
			sprintf(result[i], form, wid, (int)((long *)x)[i]);
		else
			error("`type' must be \"integer\" for  \"d\"-format");
	}
	else { /* --- floating point --- */
		if (strlen(*flag) == 0) {
			strcpy(form, "%*.*");
		} else {
			strcpy(form, "%");
			strcat(form, *flag);
			strcat(form, "*.*");
		}

		if(do_fg) {
			strcpy(f0, "%");
			strcat(f0, *flag);
			strcat(f0, ".*f");
			strcat(form, "g");
		}
		else	strcat(form, *format);
#ifdef DEBUG
		fprintf(stderr, "strsignif.c: form=�%s�, wid=%d, dig=%d\n",
			form, wid, dig);
		if(do_fg) fprintf(stderr, "\t\"fg\": f0=�%s�.", f0);
#endif
		if (strcmp("double", *type) == 0) {
		  if(do_fg) /* do smart "f" : */
		    for (i=0; i < nn; i++) {
		      xx = ((double *)x)[i];
		      if(xx == 0.) strcpy(result[i], "0");
		      else {
			iex= (int)floor(log10(fabs(xx)));
			if(iex == -4 && fabs(xx)< 1e-4) {/* VERY rare case */
			  iex = -5;
			}
			if(iex < -4) {
			  /* "g" would result in 'e-' representation:*/
			  sprintf(result[i], f0, dig-1 + -iex, xx);
#ifdef DEBUG
			  fprintf(stderr, " x[%d]=%g, iex%d\n", i, xx, iex);
			  fprintf(stderr, "\tres. = '%s'; ", result[i]);
#endif
			  /* Remove trailing  "0"s : */
			  jL = j = strlen(result[i])-1;
			  while(result[i][j] == '0') j--;
			  result[i][j+1] = '\0';
#ifdef DEBUG
			  fprintf(stderr, "\t>>> jL=%d, j=%d; new res= '%s'\n",
				  jL, j, result[i]);
#endif
			} else { /* iex >= -4:	NOT "e-" */
			  /* if iex >= dig, would have "e+" representation */
#ifdef DEBUG
			  fprintf(stderr, "\t  iex >= -4; using %d for 'dig'\n",
				  (iex >= dig) ? (iex+1) : dig);
#endif
			  sprintf(result[i], form, wid,
				  (iex >= dig) ? (iex+1) : dig, xx);
			}
		      } /* xx != 0 */
		    } /* if(do_fg) for(i..) */
		  else
		    for (i=0; i < nn; i++)
			sprintf(result[i], form, wid, dig, ((double *)x)[i]);
		} else
			error("`type' must be \"real\" for this format");
	}
}
