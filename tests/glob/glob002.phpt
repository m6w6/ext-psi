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
$glob = ["gl_offs" => 3]; 
var_dump(psi\glob("*.php{,t}", psi\GLOB_BRACE|psi\GLOB_DOOFFS, $glob));
var_dump($glob);
?>
===DONE===
--EXPECTF--
===TEST===
int(0)
===DONE===