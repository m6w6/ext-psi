<?php
include __DIR__."/_include.php"
?>

static inline token_t psi_calc_minus(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	(void) t2;
	(void) v2;
	
	switch (t1) {<?php /*nobr */ ?>
	<?php foreach ($types as $t1 => $v1) : ?>
	<?php if (t_is_special($t1)) :?>
	
#if HAVE_<?=$t1?>
	<?php endif; ?>

	case PSI_T_<?=$t1?>:
		res-><?=$v1?> = -v1-><?=$v1?>;
		break;<?php /*nobr */ ?>
	<?php if (t_is_special($t1)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}
	return t1;
}


static inline token_t psi_calc_bool_not(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	(void) t2;
	(void) v2;
	
	switch (t1) {<?php /*nobr */ ?>
	<?php foreach ($types as $t1 => $v1) : ?>
	<?php if (t_is_special($t1)) :?>
	
#if HAVE_<?=$t1?>
	<?php endif; ?>

	case PSI_T_<?=$t1?>:
		res->u8 = !v1-><?=$v1?>;
		break;<?php /*nobr */ ?>
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


static inline token_t psi_calc_bin_not(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1;

	(void) t2;
	(void) v2;
	
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

	res->u64 = ~i1.u64;
	return PSI_T_UINT64;
}