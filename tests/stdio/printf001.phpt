--TEST--
printf
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--ENV--
LC_ALL=C
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--FILE--
===TEST===
<?php
psi\printf("%.*s %ld %f\n", 5, "hello world", 123456789, .987654321);
?>
===DONE===
--EXPECT--
===TEST===
hello 123456789 0.987654
===DONE===
