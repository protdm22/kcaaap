#pragma once
#include "../service/AdminService.h"

class GeneratorUtils {
public:
    /// Initializes the repository with 10 entries.
    static void initializeEntries(AdminService *service);
};
