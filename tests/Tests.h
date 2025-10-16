#pragma once

class Tests {
private:
    static void testMemoryRepository();

    static void testFileRepository();

    static void testSQLRepository();

    static void testAdminService();

    static void testUserService();

    static void testDomain();

    static void testAdoptionList();

    static void testComparator();

public:
    static void testAll();
};
