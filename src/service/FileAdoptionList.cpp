#include "FileAdoptionList.h"

#include <utility>
#include <Windows.h>
#include <shellapi.h>

FileAdoptionList::FileAdoptionList(std::string filename) : filename(std::move(filename)) {
}

void CSVAdoptionList::writeToFile() {
    std::ofstream out{filename};
    for (const auto &dog: adoptedDogs) {
        out << dog << "\n";
    }
    out.close();
}

void CSVAdoptionList::displayAdoptionList() {
    ShellExecuteA(nullptr, nullptr, "excel.exe", filename.c_str(), nullptr, SW_SHOWMAXIMIZED);
}

void HTMLAdoptionList::writeToFile() {
    std::ofstream out{filename};
    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "<head>\n";
    out << "\t<title>Adoption list</title>\n";
    out << "</head>\n";
    out << "<style>\n";
    out << R"(  body { font-family: sans-serif; background: #f9f9f9; padding: 20px; text-align: center; }
                h2 { margin-bottom: 30px; }
                table { border-collapse: collapse; width: 80%; margin: auto; background: #fff; box-shadow: 0 0 8px #ccc; }
                td { padding: 10px; }
                tr:first-child { background: #4CAF50; color: white; font-weight: bold; }
                tr:nth-child(even):not(:first-child) { background: #f2f2f2; }
                a { color: #1a73e8; text-decoration: none; position: relative; }
                a:hover { text-decoration: underline; }
                a .preview {
                    display: none;
                    position: absolute;
                    top: 20px;
                    left: 0;
                    z-index: 10;
                    border: 1px solid #ccc;
                    background: #fff;
                    padding: 5px;
                    box-shadow: 0 0 5px rgba(0,0,0,0.2);
                }
                a:hover .preview {
                    display: block;
                }
                .preview img {
                    max-width: 200px;
                    height: auto;
                }
    )";
    out << "</style>\n";

    out << "<body>\n";
    out << "<table border=\"1\">\n";

    out << "\t<tr>\n";
    out << "\t\t<td>Name</td>\n";
    out << "\t\t<td>Breed</td>\n";
    out << "\t\t<td>Age</td>\n";
    out << "\t\t<td>Photo Link</td>\n";
    out << "\t</tr>\n";

    for (const auto &dog: this->adoptedDogs) {
        out << "\t<tr>\n";
        out << "\t\t<td>" << dog.getName() << "</td>\n";
        out << "\t\t<td>" << dog.getBreed() << "</td>\n";
        out << "\t\t<td>" << dog.getAge() << "</td>\n";
        out << "\t\t<td>\n";
        out << "\t\t\t<a href=\"" << dog.getPhotoLink() << "\" target=\"_blank\">\n";
        out << "                Link\n";
        out << "\t\t\t\t<span class=\"preview\"><img src=\"" << dog.getPhotoLink() << "\" alt=\"Preview\"></span>\n";
        out << "\t\t\t</a>\n";
        out << "\t\t</td>\n";
        out << "\t</tr>\n";
    }

    out << "</table>\n";
    out << "</body>\n";
    out << "</html>\n";
}

void HTMLAdoptionList::displayAdoptionList() {
    ShellExecuteA(nullptr, "open", filename.c_str(), nullptr, nullptr, SW_SHOWMAXIMIZED);
}
