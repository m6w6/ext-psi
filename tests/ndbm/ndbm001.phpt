--TEST--
ndbm
--INI--
psi.directory={PWD}:{PWD}/../../psi.d
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
function_exists("psi\\dbm_open") or die("skip - need nbdm support");
?>
--FILE--
===TEST===
<?php
class db {
	private $db;

	function __construct($file = __DIR__."/ndbm001.db", $o = psi\O_CREAT|psi\O_RDWR, $m = 0640) {
		if (!$this->db = psi\dbm_open($file, $o, $m)) {
			throw new Exception(psi\strerror(psi\errno()));
		}
	}

	function __destruct() {
		psi\dbm_close($this->db);
	}

	function __set($k, $v) {
		return psi\dbm_store($this->db, [
				"dptr" => $k,
				"dsize" => strlen($k)
			], [
				"dptr" => $v,
				"dsize" => strlen($v)
			], psi\DBM_REPLACE);
	}

	function __get($k) {
		$val = psi\dbm_fetch($this->db, [
			"dptr" => $k,
			"dsize" => strlen($k)
		]);
		if ($val) {
			return $val["dptr"];
		}
	}
}

$db = new db();
$db->key = "data";
var_dump($db->key);
?>
===DONE===
--CLEAN--
<?php
array_map("unlink", glob(__DIR__."/ndbm001.db*"));
?>
--EXPECT--
===TEST===
string(4) "data"
===DONE===
