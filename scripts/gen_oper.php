/*******************************************************************************
 Copyright (c) 2016, Michael Wallner <mike@php.net>.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

static inline int psi_token_oper_cmp(token_t op1, token_t op2) {
	switch (op1) {
<?php

$oper = [
		["NOT", "TILDE"],
		["ASTERISK", "SLASH", "MODULO"],
		["PLUS", "MINUS"],
		["LSHIFT", "RSHIFT"],
		["LCHEVR", "CMP_LE", "RCHEVR", "CMP_GE"],
		["AMPERSAND"],
		["CMP_EQ", "CMP_NE"],
		["CARET"],
		["PIPE"],
		["AND"],
		["OR"]
];


foreach ($oper as $prec1 => $ops1) {
	foreach ($ops1 as $op1) {
		printf("\tcase PSI_T_%s:\n", $op1);
		printf("\t\tswitch (op2) {\n");
		foreach ($oper as $prec2 => $ops2) {
			foreach ($ops2 as $op2) {
				printf("\t\t\tcase PSI_T_%s: %sreturn %2d;\n", $op2,
						str_repeat(" ", 10 - strlen($op2)),
						$prec1==$prec2?0:($prec1>$prec2?1:-1));
			}
		}
		printf("\t\t}\n\t\tassert(0);\n\t\tbreak;\n");
	}
}
?>
	}
	assert(0);
	return 0;
}
