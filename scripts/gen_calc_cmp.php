<?php

include __DIR__."/_include.php";

$ops = [
		"eq" => "==",
		"ne" => "!=",
		"lt" => "<",
		"gt" => ">",
		"le" => "<=",
		"ge" => ">="
];

?>

<?php foreach ($ops as $op_name => $op) : ?>

static inline token_t psi_calc_cmp_<?=$op_name?>(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {<?php /*nobr*/ ?>
	<?php foreach ($types as $t1 => $v1) : ?>
	<?php if (t_is_special($t1)) : ?>

#if HAVE_<?=$t1?>
	<?php endif; ?>

	case PSI_T_<?=$t1?>:
		switch (t2) {<?php /*nobr*/ ?>
		<?php foreach ($types as $t2 => $v2) : ?>
		<?php if (t_is_special($t2)) :?>
	
#	if HAVE_<?=$t2?>
		<?php endif; ?>
		
		case PSI_T_<?=$t2?>:
			res->u8 = v1-><?=$v1?> <?=$op?> v2-><?=$v2?>;
			break;<?php /*nobr*/ ?>
		<?php if (t_is_special($t2)) : ?>

#	endif
		<?php endif; ?>
		<?php endforeach; ?>

		default:
			assert(0);
			break;
		}
		break;<?php /*nobr*/ ?>
	<?php if (t_is_special($t1)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}
	return PSI_T_UINT8;
}
<?php endforeach; ?>
