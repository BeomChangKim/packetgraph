/* Copyright 2014 Nodalink EURL
 *
 * This file is part of Butterfly.
 *
 * Butterfly is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as published
 * by the Free Software Foundation.
 *
 * Butterfly is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Butterfly.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _BRICKS_BRICK_H_
#define _BRICKS_BRICK_H_

#include "bricks/brick_int.h"

inline enum side flip_side(enum side side);

void brick_set_max_edges(struct brick *brick,
			   uint16_t west_edges, uint16_t east_edges);

 /* lifecycle */
struct brick *brick_new(const char *name, struct brick_config *config);
void brick_incref(struct brick *brick);
struct brick *brick_decref(struct brick *brick);

/* testing */
int64_t brick_refcount(struct brick *brick);
uint32_t brick_links_count_get(struct brick *brick, struct brick *target);

/* relationship between bricks */
int brick_west_link(struct brick *target, struct brick *brick);
int brick_east_link(struct brick *target, struct brick *brick);
void brick_unlink(struct brick *brick);

/* generic functions used to factorize code */

/* these are generic brick_ops callbacks */
int brick_generic_west_link(struct brick *target, struct brick *brick);
int brick_generic_east_link(struct brick *target, struct brick *brick);
void brick_generic_unlink(struct brick *brick);

/* data flow */
void brick_burst(struct brick *brick, enum side side,
		 struct rte_mbuf **pkts, uint16_t nb, uint64_t pkts_mask);

/* data flow commodity functions */
void brick_burst_to_east(struct brick *brick,
		      struct rte_mbuf **pkts, uint16_t nb, uint64_t pkts_mask);

void brick_burst_to_west(struct brick *brick,
		      struct rte_mbuf **pkts, uint16_t nb, uint64_t pkts_mask);

/* used for testing */
struct rte_mbuf **brick_west_burst_get(struct brick *brick,
				       uint64_t *pkts_mask);
struct rte_mbuf **brick_east_burst_get(struct brick *brick,
				       uint64_t *pkts_mask);

#endif