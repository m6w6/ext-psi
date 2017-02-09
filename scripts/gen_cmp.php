<?php

$types = [
		"FLOAT" => "fval", 
		"DOUBLE" => "dval",
		"LONG_DOUBLE" => "ldval",
		"INT8" => "i8",
		"UINT8" => "u8",
		"INT16" => "i16", 
		"UINT16" => "u16",
		"INT32" => "i32", 
		"UINT32" => "u32",
		"INT64" => "i64", 
		"UINT64" => "u64",
];

printf("\tswitch (t1) { \\\n");
foreach ($types as $t1 => $f1) {
	printf("\tcase PSI_T_%s: \\\n", $t1);
	printf("\t\tswitch (t2) { \\\n");
	foreach ($types as $t2 => $f2) {
		printf("\t\tcase PSI_T_%s:\tPSI_CALC_OP2(u8, %s, %s);\tbreak; \\\n",
				$t2, $f1, $f2);
	}
	printf("\t\tEMPTY_SWITCH_DEFAULT_CASE(); \\\n\t\t} \\\n\t\tbreak; \\\n");
}
printf("\tEMPTY_SWITCH_DEFAULT_CASE(); \\\n\t} \\\n");