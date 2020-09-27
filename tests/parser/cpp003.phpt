--TEST--
CPP argument prescan
--INI--
psi.directory={PWD}/cpp003
--FILE--
===TEST===
<?php 
var_dump(CPP_TEST1, CPP_TEST2);
?>
===DONE===
--EXPECT--
===TEST===
int(111111)
int(222222)
===DONE===
