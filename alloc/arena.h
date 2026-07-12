#ifndef CTYPEDEFS_ALLOC_ARENA_H
#define CTYPEDEFS_ALLOC_ARENA_H

/*
 * Bump  allocator (linear).
 *
 * Allocates by advancing an offset into large mmap'd blocks - O(1),
 * no per-object free. Reclaim memory in bulk via arena_reset(), or
 * roll back to an earlier point via arena_mark()/arena_reset_to().
 * Growth adds new blocks rather than reallocating, so pointers handed
 * out earlier always stay valid until the arena is reset or destroyed.
 */

#include "../types.h"

typedef struct ArenaBlock ArenaBlock;

typedef struct Arena {
    ArenaBlock *current;
    ArenaBlock *base_block;
    usize default_block_size;
} Arena;

typedef struct ArenaMark {
    ArenaBlock *block;
    usize offset;
} ArenaMark;

/* initial_capacity is a hint (rounded up to a page); pass 0 for a sane default. */
Arena arena_create(usize initial_capacity);
void arena_destroy(Arena *a);

void *arena_alloc(Arena *a, usize size);
/* align must be a power of two <= 64 (block headers only guarantee 64-byte base alignment). */
void *arena_alloc_aligned(Arena *a, usize size, usize align);

ArenaMark arena_mark(const Arena *a);
void arena_reset_to(Arena *a, ArenaMark mark);
void arena_reset(Arena *a);

usize arena_bytes_used(const Arena *a);
usize arena_bytes_reserved(const Arena *a);

#endif /* CTYPEDEFS_ALLOC_ARENA_H */
