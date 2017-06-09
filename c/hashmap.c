#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_COUNT 4

typedef struct hash_entry hash_entry;
typedef struct hash_bucket hash_bucket;
typedef struct hash hash;

struct hash_entry {
  hash_entry* next;
  char* key;
  int value;
};

struct hash_bucket {
  hash_entry* first;
  hash_entry* last;
};

struct hash {
  hash_bucket buckets[BUCKET_COUNT];
};

/*
 * Create a new hash entry for a given key and value
 * */
hash_entry* hash_entry_create(char* key, int value) {
  hash_entry* entry = malloc(sizeof(hash_entry));
  entry->next = NULL;
  entry->key = key;
  entry->value = value;

  return entry;
}

void hash_bucket_init(hash_bucket* bucket) {
  bucket->first = NULL;
  bucket->last = NULL;
}

/*
 * Create a new hash with a given bucket count
 * */
hash* hash_create() {
  hash* myhash = malloc(sizeof(hash));

  // Initialize all buckets
  for (int i = 0; i < BUCKET_COUNT; i++) {
    hash_bucket_init(myhash->buckets + i);
  }

  return myhash;
}

/*
 * Return the hash value for a given key
 * */
int hash_generate_hash(char* key) {
  int length = strlen(key);
  int sum = 0;

  for (int i = 0; i < length; i++) {
    sum += key[i];
  }

  return sum % BUCKET_COUNT;
}

/*
 * Searches for a given entry in a bucket
 * */
hash_entry* hash_search_entry(hash_bucket* bucket, char* key) {
  hash_entry* entry = bucket->first;

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      return entry;
    }

    entry = entry->next;
  }

  return NULL;
}

/*
 * Write a given value to a given key
 * */
void hash_write(hash* hash, char* key, int value) {
  int bucket_index = hash_generate_hash(key);
  hash_bucket* bucket = hash->buckets + bucket_index;

  // We first check if the entry already exists
  hash_entry* found_entry = hash_search_entry(bucket, key);

  if (found_entry) {
    found_entry->value = value;
    return;
  }

  // No entry was found so we need to create a new one and append it to the bucket
  if (bucket->first) {

    // Get the last entry in the bucket
    hash_entry* last_entry = bucket->last;

    // Create a new entry for the key
    hash_entry* new_entry = hash_entry_create(key, value);

    // Append the new entry to the last item
    last_entry->next = new_entry;
    bucket->last = new_entry;
  } else {

    // Create a new entry for the key
    hash_entry* new_entry = hash_entry_create(key, value);
    bucket->first = new_entry;
    bucket->last = new_entry;
  }
}

/*
 * Tries to read a value from the hash
 * Saves the result in out
 *
 * Returns 1 if the key was found
 * Returns 0 if the key wasn't found
 * */
int hash_read(hash* hash, char* key, int* out) {
  int bucket_index = hash_generate_hash(key);
  hash_bucket* bucket = hash->buckets + bucket_index;

  hash_entry* found_entry = hash_search_entry(bucket, key);

  if (found_entry) {
    *out = found_entry->value;
    return 1;
  }

  return 0;
}

int main() {

  hash* myhash = hash_create();

  hash_write(myhash, "peter", 25);
  hash_write(myhash, "markus", 50);
  hash_write(myhash, "pascal", 75);
  hash_write(myhash, "leonard", 25);
  hash_write(myhash, "igor", 50);
  hash_write(myhash, "fabrice", 75);
  hash_write(myhash, "fabian", 75);

  for (int i = 0; i < BUCKET_COUNT; i++) {
    printf("bucket %02d: %p\n", i, myhash->buckets[i].first);

    hash_entry* entry = myhash->buckets[i].first;
    while (entry) {
      printf(" - %s = %d\n", entry->key, entry->value);

      entry = entry->next;
    }
  }

  int a = 0, b = 0, c = 0, d = 0;

  hash_read(myhash, "peter", &a);
  hash_read(myhash, "markus", &b);
  hash_read(myhash, "pascal", &c);
  hash_read(myhash, "leonard", &d);

  printf("peter = %d\n", a);
  printf("markus = %d\n", b);
  printf("pascal = %d\n", c);
  printf("leonard = %d\n", d);

  return 0;
}
