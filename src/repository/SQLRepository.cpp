#include "SQLRepository.h"

#include "../exceptions/RepositoryException.h"

void SQLRepository::executeSQL(const std::string &sql) const {
    char *errorMessage = nullptr;
    const int returnCode = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (returnCode != SQLITE_OK) {
        const std::string error = "SQL error: " + std::string(errorMessage);
        sqlite3_free(errorMessage);
        throw RepositoryException(error);
    }
}

SQLRepository::SQLRepository(const std::string &dbPath) {
    const int returnCode = sqlite3_open(dbPath.c_str(), &db);
    if (returnCode) {
        throw RepositoryException("Cannot open database: " + std::string(sqlite3_errmsg(db)));
    }
    const std::string createTableSQL =
            "CREATE TABLE IF NOT EXISTS dogs ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT NOT NULL, "
            "breed TEXT NOT NULL, "
            "age INTEGER NOT NULL,"
            "photoLink TEXT NOT NULL);";
    executeSQL(createTableSQL);
}

SQLRepository::~SQLRepository() {
    if (db) {
        sqlite3_close(db);
    }
}

void SQLRepository::add(const Dog &dog) {
    const std::string insertSQL = "INSERT INTO dogs (name, breed, age, photoLink) VALUES ('" +
                                  dog.getName() + "', '" +
                                  dog.getBreed() + "', " +
                                  std::to_string(dog.getAge()) + ", '" +
                                  dog.getPhotoLink() + "');";
    executeSQL(insertSQL);
}

void SQLRepository::update(const int index, const Dog &newDog) {
    const std::string updateSQL = "UPDATE dogs SET name = '" + newDog.getName() +
                                  "', breed = '" + newDog.getBreed() +
                                  "', age = " + std::to_string(newDog.getAge()) +
                                  ", photoLink = '" + newDog.getPhotoLink() +
                                  "' WHERE id = " + std::to_string(index) + ";";
    executeSQL(updateSQL);
}

void SQLRepository::remove(const int index) {
    const std::string deleteSQL = "DELETE FROM dogs WHERE id = " + std::to_string(index) + ";";
    executeSQL(deleteSQL);
}

std::vector<Dog> SQLRepository::getAllDogs() {
    std::vector<Dog> allDogs;
    const std::string selectSQL = "SELECT * FROM dogs;";
    sqlite3_stmt *statement;
    const int returnCode = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &statement, nullptr);
    if (returnCode != SQLITE_OK) {
        throw RepositoryException("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
    }
    while (sqlite3_step(statement) == SQLITE_ROW) {
        const std::string name = reinterpret_cast<const char *>(sqlite3_column_text(statement, 1));
        const std::string breed = reinterpret_cast<const char *>(sqlite3_column_text(statement, 2));
        const int age = sqlite3_column_int(statement, 3);
        const std::string photoLink = reinterpret_cast<const char *>(sqlite3_column_text(statement, 4));
        allDogs.emplace_back(name, breed, age, photoLink);
    }
    sqlite3_finalize(statement);
    return allDogs;
}

int SQLRepository::find(const Dog &dogToFind) {
    const std::string selectSQL = "SELECT id FROM dogs WHERE name = '" + dogToFind.getName() +
                                  "' AND breed = '" + dogToFind.getBreed() +
                                  "' AND age = " + std::to_string(dogToFind.getAge()) + ";";
    sqlite3_stmt *statement;
    int result = -1;
    const int returnCode = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &statement, nullptr);
    if (returnCode != SQLITE_OK) {
        throw RepositoryException("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
    }
    if (sqlite3_step(statement) == SQLITE_ROW) {
        result = sqlite3_column_int(statement, 0);
    }
    sqlite3_finalize(statement);
    return result;
}

Dog SQLRepository::findByID(const int index) {
    const std::string selectSQL = "SELECT * FROM dogs WHERE id = " + std::to_string(index) + ";";
    sqlite3_stmt *statement;
    Dog dog;
    const int returnCode = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &statement, nullptr);
    if (returnCode != SQLITE_OK) {
        throw RepositoryException("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
    }
    if (sqlite3_step(statement) == SQLITE_ROW) {
        const std::string name = reinterpret_cast<const char *>(sqlite3_column_text(statement, 1));
        const std::string breed = reinterpret_cast<const char *>(sqlite3_column_text(statement, 2));
        const int age = sqlite3_column_int(statement, 3);
        const std::string photoLink = reinterpret_cast<const char *>(sqlite3_column_text(statement, 4));
        dog = Dog(name, breed, age, photoLink);
    }
    sqlite3_finalize(statement);
    return dog;
}


size_t SQLRepository::size() const {
    const std::string countSQL = "SELECT COUNT(*) FROM dogs;";
    sqlite3_stmt *statement;
    const int returnCode = sqlite3_prepare_v2(db, countSQL.c_str(), -1, &statement, nullptr);
    if (returnCode != SQLITE_OK) {
        throw RepositoryException("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
    }
    size_t count = 0;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        count = sqlite3_column_int(statement, 0);
    }
    sqlite3_finalize(statement);
    return count;
}
