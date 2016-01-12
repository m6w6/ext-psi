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
	var_dump(psi\getnameinfo($ai["ai_addr"], $host, $serv, $flags), $host, $serv);
} while (($ai = $ai["ai_next"]));

?>
===DONE===
--EXPECT--
===TEST===
int(0)
string(12) "78.46.223.30"
string(1) "0"
int(0)
string(12) "78.46.223.30"
string(1) "0"
int(0)
string(12) "78.46.223.30"
string(1) "0"
===DONE===