#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

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

    string getID() { return id; }
    string getName() { return name; }
    int getAge() { return age; }
    string getSex() { return sex; }
    string getSpecies() { return species; }
    string getColor() { return color; }
    int getWeight() { return weight; }
    string getOrigin() { return origin; }

    void setName(string newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setColor(string newColor) { color = newColor; }

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

class Hyena : public Animal {
public:
    Hyena(string id, string name, int age, string sex, string color, int weight, string origin)
            : Animal(id, name, age, sex, "hyena", color, weight, origin) {}

    string getHabitat() override {
        return "Hyena Habitat";
    }
};

class Lion : public Animal {
public:
    Lion(string id, string name, int age, string sex, string color, int weight, string origin)
            : Animal(id, name, age, sex, "lion", color, weight, origin) {}

    string getHabitat() override {
        return "Lion Habitat";
    }
};

class Tiger : public Animal {
public:
    Tiger(string id, string name, int age, string sex, string color, int weight, string origin)
            : Animal(id, name, age, sex, "tiger", color, weight, origin) {}

    string getHabitat() override {
        return "Tiger Habitat";
    }
};

class Bear : public Animal {
public:
    Bear(string id, string name, int age, string sex, string color, int weight, string origin)
            : Animal(id, name, age, sex, "bear", color, weight, origin) {}

    string getHabitat() override {
        return "Bear Habitat";
    }
};

// helper based on parseAstr02.cpp idea
vector<string> splitCommaString(string line) {
    vector<string> items;
    int startPosition = 0;
    int commaPosition = 0;
    int size = 0;
    string item = "";

    while (true) {
        commaPosition = line.find(",", startPosition);

        if (commaPosition == string::npos) {
            item = line.substr(startPosition);
            if (!item.empty() && item[0] == ' ') {
                item.erase(0, 1);
            }
            items.push_back(item);
            break;
        }

        size = commaPosition - startPosition;
        item = line.substr(startPosition, size);

        if (!item.empty() && item[0] == ' ') {
            item.erase(0, 1);
        }

        items.push_back(item);
        startPosition = commaPosition + 1;

        if (startPosition < line.size() && line[startPosition] == ' ') {
            startPosition++;
        }
    }

    return items;
}

// helper based on findAndExtractAnimalNames.cpp idea
void loadNamesFromLine(string line, vector<string>& speciesNames) {
    vector<string> parts = splitCommaString(line);

    for (int i = 0; i < parts.size(); i++) {
        speciesNames.push_back(parts[i]);
    }
}

int main() {
    vector<Animal*> animals;

    vector<string> hyenaNames;
    vector<string> lionNames;
    vector<string> tigerNames;
    vector<string> bearNames;

    map<string, int> speciesCount;

    int hyenaCount = 1;
    int lionCount = 1;
    int tigerCount = 1;
    int bearCount = 1;

    string line;

    ifstream nameFile("animalNames.txt");

    if (!nameFile) {
        cout << "Could not open animalNames.txt" << endl;
        return 1;
    }

    while (getline(nameFile, line)) {
        if (line.find("Hyena Names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);
            loadNamesFromLine(line, hyenaNames);
        }
        else if (line.find("Lion Names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);
            loadNamesFromLine(line, lionNames);
        }
        else if (line.find("Bear Names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);
            loadNamesFromLine(line, bearNames);
        }
        else if (line.find("Tiger names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);
            loadNamesFromLine(line, tigerNames);
        }
    }

    nameFile.close();

    ifstream inFile("arrivingAnimals.txt");

    if (!inFile) {
        cout << "Could not open arrivingAnimals.txt" << endl;
        return 1;
    }

    while (getline(inFile, line)) {
        vector<string> parts = splitCommaString(line);

        if (parts.size() < 6) {
            continue;
        }

        int age;
        string yearWord, oldWord, sex, species;

        stringstream firstStream(parts[0]);
        firstStream >> age >> yearWord >> oldWord >> sex >> species;

        string color = parts[2];
        int colorPos = color.find(" color");
        if (colorPos != string::npos) {
            color = color.substr(0, colorPos);
        }

        int weight;
        string poundsWord;
        stringstream weightStream(parts[3]);
        weightStream >> weight >> poundsWord;

        string origin = parts[4] + ", " + parts[5];

        string id;
        string name;

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

    for (int i = 0; i < animals.size(); i++) {
        delete animals[i];
    }

    cout << "Report created successfully in newAnimals.txt" << endl;

    return 0;
}