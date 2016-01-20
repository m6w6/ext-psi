--TEST--
fopen
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
?>
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--FILE--
===TEST===
<?php
$stream = psi\fopen(__FILE__, "r");
var_dump(filesize(__FILE__) === psi\fread($stream, $data));
var_dump(file_get_contents(__FILE__) === $data);
var_dump(psi\fclose($stream));
?>
===DONE===
--EXPECTF--
===TEST===
bool(true)
bool(true)
int(0)
===DONE===
