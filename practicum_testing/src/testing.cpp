#include <string>
#include <iostream>

using namespace std;

enum class AnimalType {
	Cat, Dog, Mouse,
};

ostream& operator<<(ostream &os, const AnimalType &at) {
	if (at==AnimalType::Cat){
		os<<"cat";
	}
	else if (at==AnimalType::Dog) {
		os<<"dog";
	}
	else if (at==AnimalType::Mouse){
		os<<"mouse";
	}
/*	if (r.buses.empty()) {
		os << "No stop"s << endl;
	} else {
		for (const string &bus : r.buses) {
			os << bus << " "s;
		}
		os << endl;
	}
	*/
	return os;
}



class Animal {
public:
	Animal() = default;

	Animal(AnimalType type, string name, string owner_name) {
		type_ = type;
		name_ = name;
		owner_name_ = owner_name;
	}

	AnimalType GetType() const {
		return type_;
	}

	const string& GetName() const {
		return name_;
	}

	const string& GetOwnerName() const {
		return owner_name_;
	}

private:
	AnimalType type_;
	string name_;
	string owner_name_;
};

int main() {
	const Animal animal_date(AnimalType::Dog, "Charley"s, "Ivan"s);
	cout << "animal: " << animal_date.GetType() << " animal_name: "s
			<< animal_date.GetName() << " animal onwer name:" << animal_date.GetOwnerName()<< endl;
}
