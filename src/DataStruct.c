/* Reference: https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c */

char *strdup(char *);

struct toneDict { /* table entry: */
    struct toneDict *next; /* next entry in linked list */
    char letter; /* defined name */
    float freq; /* replacement text */
};

#define HASHSIZE 16 /* 16 designated frequencies */

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
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if c == np->letter
          return np; /* found */
    return NULL; /* not found */
}


/* install: put (name, defn) in hashtab */
struct toneDict *install(char c, float freq)
{
    struct toneDict *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct toneDict *) malloc(sizeof(*np));
        if (np == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
       return NULL;
    return np;
}

char *strdup(char s) /* make a duplicate of s */
{
    char *p;
    p = (char *) malloc(1); /* +1 for ’\0’ */
    if (p != NULL)
       strcpy(p, s);
    return p;
}