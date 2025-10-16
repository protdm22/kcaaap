#pragma once

#include <string>
#include <sstream>



class Dog {
private:
    std::string name;
    std::string breed;
    int age = 0;
    std::string photoLink;

public:
    /// Default constructor
    explicit Dog();

    /**
     * Constructor with parameters
     * @param name The name of the dog
     * @param breed The breed of the dog
     * @param age The age of the dog
     * @param photoLink The link to the photo of the dog
     */
    Dog(const std::string &name, const std::string &breed, int age, const std::string &photoLink);

    std::string getName() const { return this->name; };

    std::string getBreed() const { return this->breed; };

    int getAge() const { return this->age; };

    std::string getPhotoLink() const { return this->photoLink; };


    /**
     * Operator overload for equality comparison
     * @param other The other dog object to compare with
     * @return True if the dogs are equal, false otherwise
     */
    bool operator==(const Dog &other) const {
        return breed == other.breed && name == other.name && age == other.age;
    }

    /**
     * Operator overload for <<
     * @param out The output stream
     * @param dog The dog object to output
     * @return The output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const Dog &dog) {
        out << dog.name << "," << dog.breed << "," << dog.age << "," << dog.photoLink;
        return out;
    }

    /**
     * Operator overload for >>
     * @param in The input stream
     * @param dog The dog object to input
     * @return The input stream
     */
    friend std::istream &operator>>(std::istream &in, Dog &dog) {
        std::string line;
        if (std::getline(in, line)) {
            std::stringstream stringStream(line);
            std::getline(stringStream, dog.name, ',');
            std::getline(stringStream, dog.breed, ',');
            stringStream >> dog.age;
            stringStream.ignore(1);
            std::getline(stringStream, dog.photoLink);
        }
        return in;
    }
};

class DogValidator {
public:
    /**
     * Validates the dog object
     * @param dog The dog object to validate
     * @throws DomainException if the dog object is invalid
     */
    static void validate(const Dog &dog);

    /**
     * Validates the URL of the dog
     * @param url The URL to validate
     * @return true if the URL is valid, false otherwise
     */
    static bool isValidURL(const std::string &url);
};
