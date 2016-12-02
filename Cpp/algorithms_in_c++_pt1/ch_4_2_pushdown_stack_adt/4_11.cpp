/*
 * NOTE: this is similar to the recognition of context-free grammar using pushdown automata
 *
 * read from the input sequence onto the stack until the top of the stack is
 * equal to the next character in the permutation. Pop the top of the stack
 * and consume the next character in the permutation. Continue until one stream
 * runs out. If the stack, the input sequence, and the permutation are empty,
 * the permutation can be generated from the input sequence.
 *
 */
