--TEST--
uname
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
PHP_OS === "Linux" or die("skip - only for Linux");
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
array(6) {
  ["sysname"]=>
  string(5) "Linux"
  ["nodename"]=>
  string(%d) "%s"
  ["release"]=>
  string(%d) "%s"
  ["version"]=>
  string(%d) "%s"
  ["machine"]=>
  string(%d) "%s"
  ["domainname"]=>
  string(%d) "%s"
}
===DONE===
