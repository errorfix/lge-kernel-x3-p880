/*
 * arch/arm/mach-tegra/include/mach/clk.h
 *
 * Copyright (C) 2010 Google, Inc.
 *
 * Author:
 *	Erik Gilling <konkers@google.com>
 *
 * Copyright (C) 2010-2012 NVIDIA Corporation
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __MACH_CLK_H
#define __MACH_CLK_H

struct clk;
struct dvfs;
struct notifier_block;

enum tegra_clk_ex_param {
	TEGRA_CLK_VI_INP_SEL,
	TEGRA_CLK_DTV_INVERT,
	TEGRA_CLK_NAND_PAD_DIV2_ENB,
	TEGRA_CLK_PLLD_CSI_OUT_ENB,
	TEGRA_CLK_PLLD_DSI_OUT_ENB,
	TEGRA_CLK_PLLD_MIPI_MUX_SEL,
};

void tegra_periph_reset_deassert(struct clk *c);
void tegra_periph_reset_assert(struct clk *c);

#ifdef CONFIG_TEGRA_SILICON_PLATFORM
int tegra_dvfs_set_rate(struct clk *c, unsigned long rate);
#else
static inline int tegra_dvfs_set_rate(struct clk *c, unsigned long rate)
{ return 0; }
#endif
unsigned long clk_get_rate_all_locked(struct clk *c);
#ifdef CONFIG_ARCH_TEGRA_2x_SOC
void tegra_sdmmc_tap_delay(struct clk *c, int delay);

static inline int tegra_emc_enable_eack(void) {
	return 0;
}

static inline int tegra_emc_disable_eack(void) {
	return 0;
}
#else
#define LGE_RESTRICT_POWER_DURING_SLEEP
void tegra_auto_hotplug_set_min_cpus(int num_cpus);  //sujeong.kwon@l    ge.com.2012-04-20. power: Add set_min_cpus function from NV.
void tegra_auto_hotplug_set_max_cpus(int num_cpus);
static inline void tegra_sdmmc_tap_delay(struct clk *c, int delay)
{
}
int tegra_emc_enable_eack(void);
int tegra_emc_disable_eack(void);
#endif
int tegra_dvfs_rail_disable_by_name(const char *reg_id);
int tegra_clk_cfg_ex(struct clk *c, enum tegra_clk_ex_param p, u32 setting);
int tegra_register_clk_rate_notifier(struct clk *c, struct notifier_block *nb);
void tegra_unregister_clk_rate_notifier(
	struct clk *c, struct notifier_block *nb);

/**
 * tegra_is_clk_enabled - get info if the clk is enabled or not
 * @clk: clock source
 *
 * Returns refcnt.
 */
int tegra_is_clk_enabled(struct clk *clk);

void tegra_cpu_user_cap_set(unsigned int speed_khz);

#endif
