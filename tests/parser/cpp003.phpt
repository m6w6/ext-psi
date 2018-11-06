--TEST--
CPP argument prescan
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
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
