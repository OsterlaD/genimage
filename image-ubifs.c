/*
 * Copyright (c) 2011 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define _GNU_SOURCE
#include <confuse.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "genimage.h"

static int ubifs_generate(struct image *image)
{
	int lebcount;
	int ret;
	char *extraargs = cfg_getstr(image->imagesec, "extraargs");

	lebcount = image->size / image->flash_type->lebsize;

	ret = systemp(image, "%s -d  %s -e %d -m %d -c %d -o %s %s",
			get_opt("mkfsubifs"),
			mountpath(image),
			image->flash_type->lebsize,
			image->flash_type->minimum_io_unit_size,
			lebcount,
			imageoutfile(image),
			extraargs);

	return ret;
}

static int ubifs_setup(struct image *image, cfg_t *cfg)
{
	return 0;
}

static cfg_opt_t ubifs_opts[] = {
	CFG_STR("extraargs", "", CFGF_NONE),
	CFG_STR("autoresize", "", CFGF_NONE),
	CFG_END()
};

struct image_handler ubifs_handler = {
	.type = "ubifs",
	.generate = ubifs_generate,
	.setup = ubifs_setup,
	.opts = ubifs_opts,
};

