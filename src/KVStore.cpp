#include "KVStore.h"
#include "Database.h"

int KVStore::get(int key) { return map[key]; }

void KVStore::put(int key, int val) { map.insert_or_assign(key, val); }

Database KVStore::createEmptyDB(const std::string &dbname) {
  return Database::createEmptyDB(dbname);
}
