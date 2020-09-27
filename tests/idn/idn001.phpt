--TEST--
libidn
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
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
