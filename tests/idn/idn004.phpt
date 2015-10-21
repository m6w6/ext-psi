--TEST--
libidn
--INI--
psi.directory={PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 

$result = "buecher.de";
$rc = idn\utf8_to_ascii("bücher.de", $result, IDNA_USE_STD3_ASCII_RULES);
printf("%s\n", $result);
printf("%s\n", idn\strerror($rc));

$rc = idn\utf8_to_ascii("bücher2.de", $result, IDNA_USE_STD3_ASCII_RULES);
printf("%s\n", $result);
printf("%s\n", idn\strerror($rc));

?>
===DONE===
--EXPECT--
===TEST===
xn--bcher-kva.de
Success
xn--bcher2-3ya.de
Success
===DONE===