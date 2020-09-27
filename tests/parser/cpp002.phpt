--TEST--
CPP defines
--FILE--
===TEST===
<?php 

var_dump(psi_validate_string(<<<PSI
#define FOO 1
#define FOO 1
#define FOO 2
#define FOO 2
PSI
));
?>
===DONE===
--EXPECT--
===TEST===

Warning: 'FOO' redefined in <stdin> on line 3

Warning: 'FOO' previously defined in <stdin> on line 2
bool(true)
===DONE===
