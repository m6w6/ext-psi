<?php

include __DIR__."/_include.php";

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

?>


static inline int psi_calc_oper(token_t op1, token_t op2)
{
	if (PSI_T_LPAREN == op2) {
		return -1;
	} else if (PSI_T_LPAREN == op1) {
		return 1;
	} else if (op1 == op2) {
		return 0;
	} else if (!op1) {
		return 1;
	} else if (!op2) {
		return -1;
	}

	switch (op1) {<?php /*nobr*/ ?>
	<?php foreach ($oper as $prec1 => $ops1) : ?>
	<?php foreach ($ops1 as $op1) : ?>

	case PSI_T_<?=$op1?>:
		switch (op2) {<?php /*nobr*/ ?>
		<?php foreach ($oper as $prec2 => $ops2) : ?>
			<?php foreach ($ops2 as $op2) : ?>

		case PSI_T_<?=$op2?>:
			return <?=$prec1==$prec2?0:($prec1>$prec2?1:-1)?>;<?php /*nobr */ ?>
			<?php endforeach; ?>
		<?php endforeach; ?>

		default:
			assert(0);
			break;
		}
		break;
	<?php endforeach; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}
	return 0;
}
