#pragma once
#include "AdoptionList.h"
#include <fstream>

class FileAdoptionList : public AdoptionList{
protected:
    std::string filename;

public:
    /// Constructor
    explicit FileAdoptionList(std::string filename);

    /// Destructor
    virtual ~FileAdoptionList() = default;

    /// Write the adoption list to a file
    virtual void writeToFile() = 0;

    /// Open the adoption list file
    virtual void displayAdoptionList() = 0;
};

class CSVAdoptionList final : public FileAdoptionList {
public:
    /**
     * Constructor for CSVAdoptionList
     * @param filename The name of the file to write to
     */
    explicit CSVAdoptionList(const std::string &filename): FileAdoptionList(filename) {
    };

    /// Write the adoption list to a file
    void writeToFile() override;

    /// Open the adoption list file
    void displayAdoptionList() override;
};

class HTMLAdoptionList final : public FileAdoptionList {
public:
    /**
     * Constructor for HTMLAdoptionList
     * @param filename The name of the file to write to
     */
    explicit HTMLAdoptionList(const std::string &filename): FileAdoptionList(filename) {
    };

    /// Write the adoption list to a file
    void writeToFile() override;

    /// Open the adoption list file
    void displayAdoptionList() override;
};
