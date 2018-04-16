--TEST--
uname
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
PHP_OS === "Linux" or die("skip - only for Linux");
defined("psi\\_UTSNAME_DOMAIN_LENGTH") or die("skip - only for systems with utsname.domainname");
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
