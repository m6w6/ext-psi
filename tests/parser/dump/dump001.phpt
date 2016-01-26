--TEST--
parse dump
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
echo shell_exec("PSI_DUMP=1 ".PHP_BINARY." -r '' > ".__DIR__."/dump.psi");
var_dump(file_exists(__DIR__."/dump.psi"));
echo shell_exec(PHP_BINARY." -d psi.directory=".__DIR__." -r ''");
?>
===DONE===
--EXPECT--
===TEST===
bool(true)
===DONE===
--CLEAN--
<?php 
@unlink(__DIR__."/dump.psi");
?>