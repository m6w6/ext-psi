--TEST--
iconv
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
function_exists("psi\\iconv_open") or die("skip - need iconv");
?>
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--FILE--
===TEST===
<?php 

$cd = psi\iconv_open("latin1", "utf8");
$in = "ß";
$rc = psi\iconv($cd, $in, $tr);
var_dump($tr === "\xdf");
var_dump($in === "");
var_dump(psi\iconv_close($cd));

?>
===DONE===
--EXPECT--
===TEST===
bool(true)
bool(true)
int(0)
===DONE===
