#pragma once

/** Trick from https://www.youtube.com/watch?v=nXaxk27zwlk
 * to avoid dead code elimination
 */
static void escape(void* p)
{
    asm volatile("" : : "g"(p) : "memory");
}

static void clobber()
{
    asm volatile("" : : : "memory");
}
