--TEST--
libidn
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
function_exists("idn\\strerror") or die("skip - need libidn");
?>
--FILE--
===TEST===
<?php

$rc = idn\utf8_to_ascii("flöte.de", $result);
printf("%s\n", $result);
printf("%s\n", idn\strerror($rc));
?>
===DONE===
--EXPECT--
===TEST===
xn--flte-6qa.de
Success
===DONE===
