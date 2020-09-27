--TEST--
getaddrinfo
--INI--
psi.directory={PWD}:{PWD}/../../psi.d
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
	if ($host !== "88.198.203.24" && $host !== "2a01:4f8:1c0c:6995::2") var_dump($host);
	if ($serv !== "0") var_dump($serv);
} while (($ai = $ai["ai_next"]));

?>
===DONE===
--EXPECT--
===TEST===
===DONE===
