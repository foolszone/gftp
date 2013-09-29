#!/bin/sh
# Run this to generate all the initial makefiles, etc.
# This was derived from Glib's autogen.sh

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.

ORIGDIR=`pwd`
cd $srcdir

AUTORECONF=`which autoreconf`
if test -z $AUTORECONF; then
	echo "*** No autoreconf found, please install it ***"
	exit 1
fi

autoreconf --force --install --verbose || exit $?

cd $ORIGDIR
test -n "$NOCONFIGURE" || "$srcdir/configure" "$@"
