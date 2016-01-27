--TEST--
parse dump
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
$fn = __DIR__."/dump.psi";
$fd = fopen($fn, "w");
psi_dump($fd);
fclose($fd);

var_dump(file_exists($fn));
var_dump(psi_validate($fn));

?>
===DONE===
--EXPECT--
===TEST===
bool(true)
bool(true)
===DONE===
--CLEAN--
<?php 
@unlink(__DIR__."/dump.psi");
?>