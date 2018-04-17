<?php

include __DIR__."/_include.php";

$ops = [
		"lshift" => "<<",
		"rshift" => ">>",
		"and" => "&",
		"xor" => "^",
		"or" => "|",
];

?>

<?php foreach ($ops as $op_name => $op) : ?>

static inline token_t psi_calc_bin_<?=$op_name?>(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1, i2;
	
	switch (t1) {<?php /*nobr*/ ?>
	<?php foreach ($types as $t1 => $v1) : ?>
	<?php if (t_is_special($t1)) :?>
	
#if HAVE_<?=$t1?>
	<?php endif; ?>

	case PSI_T_<?=$t1?>:
		i1.u64 = v1-><?=$v1?>;
		break;
	<?php if (t_is_special($t1)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}
	
	switch (t2) {<?php /*nobr*/ ?>
	<?php foreach ($types as $t2 => $v2) : ?>
	<?php if (t_is_special($t2)) :?>
	
#if HAVE_<?=$t2?>
	<?php endif; ?>

	case PSI_T_<?=$t2?>:
		i2.u64 = v2-><?=$v2?>;
		break;<?php /*nobr*/ ?>
	<?php if (t_is_special($t2)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}
	
	res->u64 = i1.u64 <?=$op?> i2.u64;
	return PSI_T_UINT64;
}
<?php endforeach; ?>
