#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

// Base class for all animals
class Animal {
protected:
    string id;
    string name;
    int age;
    string sex;
    string species;
    string color;
    int weight;
    string origin;

public:
    // Constructor
    Animal(string id, string name, int age, string sex,
           string species, string color, int weight, string origin) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->sex = sex;
        this->species = species;
        this->color = color;
        this->weight = weight;
        this->origin = origin;
    }

    // Getters
    string getID() { return id; }
    string getName() { return name; }
    int getAge() { return age; }
    string getSex() { return sex; }
    string getSpecies() { return species; }
    string getColor() { return color; }
    int getWeight() { return weight; }
    string getOrigin() { return origin; }

    // Setters
    void setName(string newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setColor(string newColor) { color = newColor; }

    // Virtual methods for polymorphism
    virtual string getHabitat() {
        return "Animal Habitat";
    }

    virtual void printInfo(ofstream& outFile) {
        outFile << id << "; "
                << name << "; "
                << age << " years old; "
                << color << " color; "
                << sex << "; "
                << weight << " pounds; "
                << origin << endl;
    }
};

// Hyena subclass
class Hyena : public Animal {
public:
    Hyena(string id, string name, int age, string sex, string color, int weight, string origin)
            : Animal(id, name, age, sex, "hyena", color, weight, origin) {
    }

    string getHabitat() override {
        return "Hyena Habitat";
    }
};

// Lion subclass
class Lion : public Animal {
public:
    Lion(string id, string name, int age, string sex, string color, int weight, string origin)
            : Animal(id, name, age, sex, "lion", color, weight, origin) {
    }

    string getHabitat() override {
        return "Lion Habitat";
    }
};

// Tiger subclass
class Tiger : public Animal {
public:
    Tiger(string id, string name, int age, string sex, string color, int weight, string origin)
            : Animal(id, name, age, sex, "tiger", color, weight, origin) {
    }

    string getHabitat() override {
        return "Tiger Habitat";
    }
};

// Bear subclass
class Bear : public Animal {
public:
    Bear(string id, string name, int age, string sex, string color, int weight, string origin)
            : Animal(id, name, age, sex, "bear", color, weight, origin) {
    }

    string getHabitat() override {
        return "Bear Habitat";
    }
};

int main() {
    // Vector stores animal objects
    vector<Animal*> animals;

    // Name lists for each species
    vector<string> hyenaNames;
    vector<string> lionNames;
    vector<string> tigerNames;
    vector<string> bearNames;

    // Counters for IDs
    int hyenaCount = 1;
    int lionCount = 1;
    int tigerCount = 1;
    int bearCount = 1;

    // Map to count how many of each species were added
    map<string, int> speciesCount;

    string line;

    // Open animal names file
    ifstream nameFile("animalNames.txt");

    if (!nameFile) {
        cout << "Could not open animalNames.txt" << endl;
        return 1;
    }

    // Read names and store them in the correct vector
    while (getline(nameFile, line)) {
        if (line.find("Hyena Names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);

            string name;
            stringstream ss(line);

            while (getline(ss, name, ',')) {
                if (!name.empty() && name[0] == ' ') {
                    name.erase(0, 1);
                }
                hyenaNames.push_back(name);
            }
        }
        else if (line.find("Lion Names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);

            string name;
            stringstream ss(line);

            while (getline(ss, name, ',')) {
                if (!name.empty() && name[0] == ' ') {
                    name.erase(0, 1);
                }
                lionNames.push_back(name);
            }
        }
        else if (line.find("Bear Names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);

            string name;
            stringstream ss(line);

            while (getline(ss, name, ',')) {
                if (!name.empty() && name[0] == ' ') {
                    name.erase(0, 1);
                }
                bearNames.push_back(name);
            }
        }
        else if (line.find("Tiger names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);

            string name;
            stringstream ss(line);

            while (getline(ss, name, ',')) {
                if (!name.empty() && name[0] == ' ') {
                    name.erase(0, 1);
                }
                tigerNames.push_back(name);
            }
        }
    }

    nameFile.close();

    // Open arriving animals file
    ifstream inFile("arrivingAnimals.txt");

    if (!inFile) {
        cout << "Could not open arrivingAnimals.txt" << endl;
        return 1;
    }

    // Read each arriving animal and parse the data
    while (getline(inFile, line)) {
        string part1, part2, part3, part4, part5, part6;
        stringstream lineStream(line);

        getline(lineStream, part1, ',');
        getline(lineStream, part2, ',');
        getline(lineStream, part3, ',');
        getline(lineStream, part4, ',');
        getline(lineStream, part5, ',');
        getline(lineStream, part6, ',');

        if (!part2.empty() && part2[0] == ' ') part2.erase(0, 1);
        if (!part3.empty() && part3[0] == ' ') part3.erase(0, 1);
        if (!part4.empty() && part4[0] == ' ') part4.erase(0, 1);
        if (!part5.empty() && part5[0] == ' ') part5.erase(0, 1);
        if (!part6.empty() && part6[0] == ' ') part6.erase(0, 1);

        int age;
        string yearWord, oldWord, sex, species;

        stringstream firstStream(part1);
        firstStream >> age >> yearWord >> oldWord >> sex >> species;

        string color = part3;
        int colorPos = color.find(" color");
        if (colorPos != string::npos) {
            color = color.substr(0, colorPos);
        }

        int weight;
        string poundsWord;
        stringstream weightStream(part4);
        weightStream >> weight >> poundsWord;

        string origin = part5 + ", " + part6;

        string id;
        string name;

        // Create the correct subclass object and count the species
        if (species == "hyena") {
            id = "Hy" + to_string(hyenaCount);
            name = hyenaNames[hyenaCount - 1];
            animals.push_back(new Hyena(id, name, age, sex, color, weight, origin));
            hyenaCount++;
            speciesCount["hyena"]++;
        }
        else if (species == "lion") {
            id = "Li" + to_string(lionCount);
            name = lionNames[lionCount - 1];
            animals.push_back(new Lion(id, name, age, sex, color, weight, origin));
            lionCount++;
            speciesCount["lion"]++;
        }
        else if (species == "tiger") {
            id = "Ti" + to_string(tigerCount);
            name = tigerNames[tigerCount - 1];
            animals.push_back(new Tiger(id, name, age, sex, color, weight, origin));
            tigerCount++;
            speciesCount["tiger"]++;
        }
        else if (species == "bear") {
            id = "Be" + to_string(bearCount);
            name = bearNames[bearCount - 1];
            animals.push_back(new Bear(id, name, age, sex, color, weight, origin));
            bearCount++;
            speciesCount["bear"]++;
        }
    }

    inFile.close();

    // Create output report file
    ofstream outFile("newAnimals.txt");

    if (!outFile) {
        cout << "Could not create newAnimals.txt" << endl;
        return 1;
    }

    outFile << "Zoo New Animal Report\n\n";

    outFile << "Hyena Habitat:\n";
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->getSpecies() == "hyena") {
            animals[i]->printInfo(outFile);
        }
    }
    outFile << "Total hyenas: " << speciesCount["hyena"] << "\n\n";

    outFile << "Lion Habitat:\n";
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->getSpecies() == "lion") {
            animals[i]->printInfo(outFile);
        }
    }
    outFile << "Total lions: " << speciesCount["lion"] << "\n\n";

    outFile << "Tiger Habitat:\n";
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->getSpecies() == "tiger") {
            animals[i]->printInfo(outFile);
        }
    }
    outFile << "Total tigers: " << speciesCount["tiger"] << "\n\n";

    outFile << "Bear Habitat:\n";
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->getSpecies() == "bear") {
            animals[i]->printInfo(outFile);
        }
    }
    outFile << "Total bears: " << speciesCount["bear"] << "\n\n";

    outFile.close();

    // Free memory
    for (int i = 0; i < animals.size(); i++) {
        delete animals[i];
    }

    cout << "Report created successfully in newAnimals.txt" << endl;

    return 0;
}