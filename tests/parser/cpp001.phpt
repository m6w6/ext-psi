--TEST--
CPP defines
--FILE--
===TEST===
<?php 

var_dump(psi_validate_string(<<<PSI
#define FOO
#ifndef FOO
# error FOO is not defined
#endif

#ifdef FOO
# define BAR 1
#else
no error #here, yay!
#endif

#if BAR
#	define BAZ
#endif

#ifndef BAZ
error
#endif

#undef BAZ
#ifdef BAZ
#	error BAZ is defined
#endif

#ifndef _1
# ifndef _2
#  ifndef _3
#  else
    error 3
#  endif
# else
   error 2
# endif
#else
  error 1
#endif


#ifndef _1
# ifdef _2
   error 2
# else

enum a{b};

# endif
#else
 error 1
#endif

enum b{a=b};
PSI
));
?>
===DONE===
--EXPECT--
===TEST===
bool(true)
===DONE===
