/*
 *----------------------------------------------------------------------
 *
 * tclTomMathInterface.c --
 *
 *	This file contains procedures that are used as a 'glue' layer between
 *	Tcl and libtommath.
 *
 * Copyright (c) 2005 by Kevin B. Kenny.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution of
 * this file, and for a DISCLAIMER OF ALL WARRANTIES.
 */

#include "tclInt.h"
#include "tommath.h"

MODULE_SCOPE const TclTomMathStubs tclTomMathStubs;

/*
 *----------------------------------------------------------------------
 *
 * TclTommath_Init --
 *
 *	Initializes the TclTomMath 'package', which exists as a
 *	placeholder so that the package data can be used to hold
 *	a stub table pointer.
 *
 * Results:
 *	Returns a standard Tcl result.
 *
 * Side effects:
 *	Installs the stub table for tommath.
 *
 *----------------------------------------------------------------------
 */

int
TclTommath_Init(
    Tcl_Interp *interp)		/* Tcl interpreter */
{
    /* TIP #268: Full patchlevel instead of just major.minor */

    if (Tcl_PkgProvideEx(interp, "tcl::tommath", TCL_PATCH_LEVEL,
	    &tclTomMathStubs) != TCL_OK) {
	return TCL_ERROR;
    }
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * TclBN_epoch --
 *
 *	Return the epoch number of the TclTomMath stubs table
 *
 * Results:
 *	Returns an arbitrary integer that does not decrease with
 *	release.  Stubs tables with different epochs are incompatible.
 *
 *----------------------------------------------------------------------
 */

int
TclBN_epoch(void)
{
    return TCLTOMMATH_EPOCH;
}

/*
 *----------------------------------------------------------------------
 *
 * TclBN_revision --
 *
 *	Returns the revision level of the TclTomMath stubs table
 *
 * Results:
 *	Returns an arbitrary integer that increases with revisions.
 *	If a client requires a given epoch and revision, any Stubs table
 *	with the same epoch and an equal or higher revision satisfies
 *	the request.
 *
 *----------------------------------------------------------------------
 */

int
TclBN_revision(void)
{
    return TCLTOMMATH_REVISION;
}

/*
 *----------------------------------------------------------------------
 *
 * TclInitBignumFromLong --
 *
 *	Allocate and initialize a 'bignum' from a native 'long'.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The 'bignum' is constructed.
 *
 *----------------------------------------------------------------------
 */

void
TclInitBignumFromLong(
    mp_int *a,
    long v)
{
    if (mp_init_size(a, (CHAR_BIT * sizeof(long) + DIGIT_BIT - 1) / DIGIT_BIT) != MP_OKAY) {
	Tcl_Panic("initialization failure in TclInitBignumFromLong");
    }
    if (v < (long)0) {
	mp_set_long_long(a, (Tcl_WideUInt)(-(Tcl_WideInt)v));
	mp_neg(a, a);
    } else {
	mp_set_long_long(a, (Tcl_WideUInt)v);
    }
}

/*
 *----------------------------------------------------------------------
 *
 * TclBNInitBignumFromWideInt --
 *
 *	Allocate and initialize a 'bignum' from a Tcl_WideInt
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The 'bignum' is constructed.
 *
 *----------------------------------------------------------------------
 */

void
TclInitBignumFromWideInt(
    mp_int *a,			/* Bignum to initialize */
    Tcl_WideInt v)		/* Initial value */
{
	if (mp_init_size(a, (CHAR_BIT * sizeof(Tcl_WideUInt) + DIGIT_BIT - 1) / DIGIT_BIT) != MP_OKAY) {
		Tcl_Panic("initialization failure in TclInitBignumFromWideInt");
	}
    if (v < (Tcl_WideInt)0) {
	mp_set_long_long(a, (Tcl_WideUInt)(-v));
	mp_neg(a, a);
    } else {
	mp_set_long_long(a, (Tcl_WideUInt)v);
    }
}

/*
 *----------------------------------------------------------------------
 *
 * TclBNInitBignumFromWideUInt --
 *
 *	Allocate and initialize a 'bignum' from a Tcl_WideUInt
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The 'bignum' is constructed.
 *
 *----------------------------------------------------------------------
 */

void
TclInitBignumFromWideUInt(
    mp_int *a,			/* Bignum to initialize */
    Tcl_WideUInt v)		/* Initial value */
{
	if (mp_init_size(a, (CHAR_BIT * sizeof(Tcl_WideUInt) + DIGIT_BIT - 1) / DIGIT_BIT) != MP_OKAY) {
	    Tcl_Panic("initialization failure in TclInitBignumFromWideUInt");
	}
	mp_set_long_long(a, v);
}

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 4
 * fill-column: 78
 * End:
 */
