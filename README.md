# Speller — Fast Spell Checker (C)

Implements a dictionary-backed spell checker that loads words into memory and flags misspellings in a text file. Built for CS50x.

## What it does
- Loads a word list into memory (hash table or trie)
- Checks each token in an input text
- Reports misspelled words and performance stats (time, memory)

## Approach & Data Structure
- **Structure:** [Hash table / Trie] (choose what you implemented)
- **Rationale:** O(1) average lookup for hash; O(L) for trie (L = word length)
- **Collisions (if hash):** [Chaining / Open addressing] with a tuned table size
- **Memory:** ~[your estimate] MB for `large` dictionary

## Build & Run
```bash
make speller
./speller texts/lorem.txt
