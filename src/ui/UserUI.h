#pragma once

#include "../service/UserService.h"

class UserUI {
private:
    UserService &service;

    /**
     * Displays dogs one by one in a user-friendly format.
     * @param dogs The vector of dogs to display.
     */
    void showDogsOneByOne(const std::vector<Dog> &dogs) const;

    /**
     * Opens the given URL in the default web browser.
     * @param url The URL to open.
     */
    static void openInBrowser(const std::string &url) {
        const std::string command = "start " + url;
        system(command.c_str());
    }

public:
    /// Constructor for UserUI.
    explicit UserUI(UserService &service) : service(service) {
    }

    /// Runs the user interface for the user mode.
    void runUI() const;
};
