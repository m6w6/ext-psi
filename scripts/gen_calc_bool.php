<?php
include __DIR__."/_include.php";
?>


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

static inline token_t psi_calc_bool_or(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {<?php /*nobr */ ?>
	<?php foreach ($types as $t1 => $v1) : ?>
	<?php if (t_is_special($t1)) :?>
	
#if HAVE_<?=$t1?>
	<?php endif; ?>

	case PSI_T_<?=$t1?>:
		if (v1-><?=$v1?>)
			goto return_true;
		break;<?php /*nobr */ ?>
	<?php if (t_is_special($t1)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}

	switch (t2) {<?php /*nobr */ ?>
	<?php foreach ($types as $t2 => $v2) : ?>
	<?php if (t_is_special($t2)) :?>
	
#if HAVE_<?=$t2?>
	<?php endif; ?>

	case PSI_T_<?=$t2?>:
		if (v2-><?=$v2?>)
			goto return_true;
		break;<?php /*nobr */ ?>
	<?php if (t_is_special($t2)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}
	
	res->u8 = 0;
	return PSI_T_UINT8;
	
return_true:
	res->u8 = 1;
	return PSI_T_UINT8;
}

static inline token_t psi_calc_bool_and(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {<?php /*nobr */ ?>
	<?php foreach ($types as $t1 => $v1) : ?>
	<?php if (t_is_special($t1)) :?>
	
#if HAVE_<?=$t1?>
	<?php endif; ?>

	case PSI_T_<?=$t1?>:
		if (!v1-><?=$v1?>)
			goto return_false;
		break;<?php /*nobr */ ?>
	<?php if (t_is_special($t1)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}

	switch (t2) {<?php /*nobr */ ?>
	<?php foreach ($types as $t2 => $v2) : ?>
	<?php if (t_is_special($t2)) :?>
	
#if HAVE_<?=$t2?>
	<?php endif; ?>

	case PSI_T_<?=$t2?>:
		if (!v2-><?=$v2?>)
			goto return_false;
		break;<?php /*nobr */ ?>
	<?php if (t_is_special($t2)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}
	
	res->u8 = 1;
	return PSI_T_UINT8;
	
return_false:
	res->u8 = 0;
	return PSI_T_UINT8;
}
