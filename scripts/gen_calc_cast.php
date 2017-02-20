<?php
include __DIR__."/_include.php";
?>


static inline void psi_calc_cast(token_t in_type, impl_val *in_val, token_t out_type, impl_val *out_val)
{
	switch (out_type) {<?php /*nobr*/ ?>
	<?php foreach ($types as $t => $v) : ?>
	<?php if (t_is_special($t)) : ?>

#if HAVE_<?=$t?>
	<?php endif; ?>

	case PSI_T_<?=$t?>:
		switch (in_type) {<?php /*nobr*/ ?>
		<?php foreach ($types as $t_in => $v_in) : ?>
		<?php if (t_is_special($t_in)) :?>
	
#	if HAVE_<?=$t_in?>
		<?php endif; ?>
		
		case PSI_T_<?=$t_in?>:
			out_val-><?=$v?> = in_val-><?=$v_in?>;
			break;<?php /*nobr*/ ?>
		<?php if (t_is_special($t_in)) : ?>

#	endif
		<?php endif; ?>
		<?php endforeach; ?>

		default:
			assert(0);
			break;
		}
		break;<?php /*nobr*/ ?>
	<?php if (t_is_special($t)) : ?>

#endif
	<?php endif; ?>
	<?php endforeach; ?>

	default:
		assert(0);
		break;
	}
}

