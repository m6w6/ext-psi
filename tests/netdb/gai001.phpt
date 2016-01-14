--TEST--
getaddrinfo
--INI--
psi.directory={PWD}:{PWD}/../../psi.d
--SKIPIF--
<?php
extension_loaded("psi") or die("skip -- need ext/psi");
?>
--FILE--
===TEST===
<?php

$rc = psi\getaddrinfo("m6w6.name", NULL, NULL, $ai);

if ($rc) {
	printf("%s\n", psi\gai_strerror($rc));
	exit;
}

$flags = psi\NI_NUMERICHOST|psi\NI_NUMERICSERV;
do {
	$rc = psi\getnameinfo($ai["ai_addr"], $host, $serv, $flags);
	if ($rc !== 0) var_dump($rc);
	if ($host !== "78.46.223.30") var_dump($host);
	if ($serv !== "0") var_dump($serv);
} while (($ai = $ai["ai_next"]));

?>
===DONE===
--EXPECT--
===TEST===
===DONE===
