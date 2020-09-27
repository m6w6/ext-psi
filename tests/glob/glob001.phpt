--TEST--
glob
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--FILE--
===TEST===
<?php 
chdir(__DIR__);
$cmp = glob(__DIR__."/*.php{,t}", GLOB_BRACE);
var_dump(psi\glob(__DIR__."/*.php{,t}", psi\GLOB_BRACE, $glob));
if ($cmp != $glob["gl_pathv"]) {
	var_dump($cmp, $glob["gl_pathv"]);
}
?>
===DONE===
--EXPECTF--
===TEST===
int(0)
===DONE===