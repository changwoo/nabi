AC_INIT(nabi, 0.15, http://kldp.net/tracker/?func=add&group_id=275&atid=100275)

AM_INIT_AUTOMAKE(nabi, 0.15)
AM_CONFIG_HEADER(config.h)

dnl Checks for programs
AC_PROG_CC
AC_OBJEXT
AC_PROG_RANLIB
AC_PROG_INSTALL

dnl Checks for header files.
AC_PATH_X
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([langinfo.h libintl.h locale.h stddef.h stdint.h stdlib.h string.h sys/param.h wchar.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

dnl Checks for library functions.
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([gethostname memmove memset mkdir putenv setlocale strchr strdup strtol])

dnl Checks for X window system
AC_PATH_XTRA
case $X_PRE_LIBS in
*"-lSM"*)
    AC_DEFINE_UNQUOTED(HAVE_LIBSM, 1, Define to 1 if you have the libSM library.)
esac

dnl Checks for GTK+ libraries.
AC_PATH_PROG(PKG_CONFIG, pkg-config,
	     AC_MSG_ERROR([nabi needs pkg-config]))
PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.2.0,,
		  AC_MSG_ERROR([nabi needs GTK+ 2.2.0 or higher]))

# checks for libhangul
PKG_CHECK_MODULES(LIBHANGUL, libhangul >= 0.0.3,,
		  AC_MSG_ERROR([nabi needs libhangul 0.0.3 or higher]))

dnl gettext stuff
ALL_LINGUAS="ko de"
AM_GLIB_GNU_GETTEXT

GETTEXT_PACKAGE="$PACKAGE"
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", gettext package name)

dnl data dir
NABI_DATA_DIR="${datadir}/$PACKAGE"
NABI_THEMES_DIR="${NABI_DATA_DIR}/themes"
AC_SUBST(NABI_DATA_DIR)
AC_SUBST(NABI_THEMES_DIR)

# configure options
AC_ARG_ENABLE(debug,
	      [  --enable-debug          include debug code],
              enable_debug=yes, enable_debug=no)

dnl default keyboard
AC_ARG_WITH(default-keyboard, [  --with-default-keyboard=2/39/3f   default hangul keyboard])
case "$with_default_keyboard" in
    2)
	AC_DEFINE_UNQUOTED(DEFAULT_KEYBOARD, "두벌식",
			   [Define default hangul keyboard])
	;;
    39)
	AC_DEFINE_UNQUOTED(DEFAULT_KEYBOARD, "세벌식 390",
			   [Define default hangul keyboard])
	;;
    3f)
	AC_DEFINE_UNQUOTED(DEFAULT_KEYBOARD, "세벌식 최종",
			   [Define default hangul keyboard])
	;;
    *)
	AC_DEFINE_UNQUOTED(DEFAULT_KEYBOARD, "두벌식",
			   [Define default hangul keyboard])
	;;
esac

if test "$enable_debug" = "yes"; then
    AC_DEFINE(NABI_DEBUG, 1, [Define to 1 if you want to use debug code])
    CFLAGS="$CFLAGS -g"
    CXXFLAGS="$CXXFLAGS -g"
fi

AC_OUTPUT([
Makefile
IMdkit/Makefile
src/Makefile
tables/Makefile
themes/Makefile
themes/SimplyRed/Makefile
themes/MSWindows/Makefile
themes/Mac/Makefile
themes/Onion/Makefile
themes/KingSejong/Makefile
themes/keyboard/Makefile
themes/MSWindowsXP/Makefile
themes/Tux/Makefile
themes/Jini/Makefile
po/Makefile.in 
])