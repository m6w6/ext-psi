<?php

include __DIR__."/_include.php";

$ops = [
		"add" => "+",
		"sub" => "-",
		"mul" => "*",
		"div" => "/",
];

function t_for_res($t1, $t2) {
	global $types;
	
	$p = array_flip(array_keys($types));
	
	if ($p[$t2] >= 8 || $p[$t1] >= 8) {
		if ($p[$t2] > $p[$t1]) {
			return $t2;
		}
		return $t1;
	}
	
	$u1 = $t1{0} === "U";
	$s1 = substr($t1, $u1 ? 4 : 3);
	$u2 = $t2{0} === "U";
	$s2 = substr($t2, $u2 ? 4 : 3);
	
	if ($u1 && $u2)  {
		return "UINT".min(64,max($s1*2,$s2*2));
	} else {
		return "INT".min(64,max($s1*2,$s2*2));
	}
	
}

function v_for_res($t1, $t2) {
	global $types;
	
	return $types[t_for_res($t1, $t2)];
}

?>


<?php foreach ($ops as $op_name => $op) : ?>
static inline token_t psi_calc_<?=$op_name?>(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
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
			res-><?=v_for_res($t1, $t2)?> = v1-><?=$v1?> <?=$op?> v2-><?=$v2?>;
			return PSI_T_<?=t_for_res($t1, $t2)?>;<?php /*nobr*/ ?>
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
	
	return 0;
}
<?php endforeach; ?>


static inline token_t psi_calc_mod(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1, i2;
	
	switch (t1) {<?php /*nobr*/ ?>
	<?php foreach ($types as $t1 => $v1) : ?>
	<?php if (t_is_special($t1)) :?>
	
#if HAVE_<?=$t1?>
	<?php endif; ?>

	case PSI_T_<?=$t1?>:
		i1.i64 = v1-><?=$v1?>;
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
		i2.i64 = v2-><?=$v2?>;
		break;<?php /*nobr*/ ?>
	<?php if (t_is_special($t2)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}
	
	res->i64 = i1.i64 % i2.i64;
	return PSI_T_INT64;
}
