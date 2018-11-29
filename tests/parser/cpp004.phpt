--TEST--
CPP argument prescan
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--INI--
psi.directory={PWD}/cpp004
--FILE--
===TEST===
<?php 
var_dump(CPP_TEST0, CPP_TEST1, CPP_TEST2, CPP_TEST3, CPP_TEST4, CPP_TEST5);
?>
===DONE===
--EXPECT--
===TEST===
int(0)
int(1)
int(2)
int(3003)
int(4004)
int(5005)
===DONE===
