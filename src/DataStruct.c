/* Reference: https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c */

struct toneDict { /* table entry: */
    struct toneDict *next; /* next entry in linked list */
    char letter; /* defined name */
    float freq; /* replacement text */
};

#define HASHSIZE 26

static struct toneDict *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char c)
{
    unsigned hashval = c + 31;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct toneDict *lookup(char c)
{
    struct toneDict *np;
    for (np = hashtab[hash(c)]; np != NULL; np = np->next)
        if (c == np->letter)
          return np; /* found */
    return NULL; /* not found */
}


/* install: put (name, defn) in hashtab */
struct toneDict *install(char c, float freq)
{
    struct toneDict *np;
    unsigned hashval;
    if ((np = lookup(c)) == NULL) { /* not found */
        np = (struct toneDict *) malloc(sizeof(*np));
        if (np == NULL)
          return NULL;
        np->letter = c;
        hashval = hash(c);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    np->freq = freq;
    return np;
}