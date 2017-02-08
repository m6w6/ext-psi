--TEST--
calc
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip need ext/psi");
?>
--FILE--
===TEST===
<?php
for ($i = 0; $i < 10; ++$i) {
	$func = "test\\calc$i";
	if (function_exists($func)) {
		$res = $func();
		if ($res === ["quot"=>1, "rem"=>0]) {
			echo "yay-";
		} else {
			var_dump($res);
		}
	}
}
?>

===DONE===
--EXPECTREGEX--
===TEST===
(yay-)+
===DONE===
