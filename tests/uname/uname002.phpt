--TEST--
uname
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
PHP_OS === "Darwin" or die("skip - for OSX");
?>
--FILE--
===TEST===
<?php
var_dump(psi\uname($uname), $uname);
?>
===DONE===
--EXPECTF--
===TEST===
int(0)
array(5) {
  ["sysname"]=>
  string(6) "Darwin"
  ["nodename"]=>
  string(%d) "%s"
  ["release"]=>
  string(%d) "%s"
  ["version"]=>
  string(%d) "%s"
  ["machine"]=>
  string(%d) "%s"
}
===DONE===
