--TEST--
glob
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
chdir(__DIR__);
$cmp = glob("*.php{,t}", GLOB_BRACE);
var_dump(psi\glob("*.php{,t}", psi\GLOB_BRACE, $glob));
var_dump($cmp == $glob["gl_pathv"]);
?>
===DONE===
--EXPECTF--
===TEST===
int(0)
bool(true)
===DONE===