//git@github.com:evgsam/practicum_testing.git

#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <sstream>

using namespace std;

enum class QueryType {
	NewBus, BusesForStop, StopsForBus, AllBuses,
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator>>(istream &is, Query &q) {
	string command;
	is >> command;
	if (command == "NEW_BUS") {
		int bus_count = 0;
		q.type = QueryType::NewBus;
		is >> q.bus;
		is >> bus_count;
		for (int i = 0; i < bus_count; ++i) {
			string temp;
			is >> temp;
			q.stops.push_back(temp);
		}
	} else if (command == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	} else if (command == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	} else if (command == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	} else {
		cout << "ERROR";
	}
	return is;
}

struct BusesForStopResponse {
	map<string, vector<string>> buses_to_stops;
};

ostream& operator<<(ostream &os, const BusesForStopResponse &r) {
	// Реализуйте эту функцию
	return os;
}

struct StopsForBusResponse {
	map<string, vector<string>> stops_to_buses;
	// Наполните полями эту структуру
};

ostream& operator<<(ostream &os, const StopsForBusResponse &r) {
	// Реализуйте эту функцию
	return os;
}

struct AllBusesResponse {
	// Наполните полями эту структуру
};

ostream& operator<<(ostream &os, const AllBusesResponse &r) {
	// Реализуйте эту функцию
	return os;
}

class BusManager {
private:
	map<string, vector<string>> buses_to_stops_, stops_to_buses_;
public:
	void AddBus(const string &bus, const vector<string> &stops) {
		buses_to_stops_[bus] = stops;
		for (const string &stop : stops) {
			stops_to_buses_[stop].push_back(bus);
		}
	}
	BusesForStopResponse GetBusesForStop(const string &stop) const {
		if (stops_to_buses_.count(stop) == 0) {
			cout << "No stop"s << endl;
		} else {
			for (const string &bus : stops_to_buses_.at(stop)) {
				cout << bus << " "s;
			}
			cout << endl;
		}
	}
	StopsForBusResponse GetStopsForBus(const string &bus) const {
		if (buses_to_stops_.count(bus) == 0) {
			cout << "No bus"s << endl;
		} else {
			for (const string &stop : buses_to_stops_.at(bus)) {
				cout << "Stop "s << stop << ": "s;
				if (stops_to_buses_.at(stop).size() == 1) {
					cout << "no interchange"s;
				} else {
					for (const string &other_bus : stops_to_buses_.at(stop)) {
						if (bus != other_bus) {
							cout << other_bus << " "s;
						}
					}
				}
				cout << endl;
			}
		}
	}

	AllBusesResponse GetAllBuses() const {
		if (buses_to_stops_.empty()) {
			cout << "No buses"s << endl;
		} else {
			for (const auto &bus_item : buses_to_stops_) {
				cout << "Bus "s << bus_item.first << ": "s;
				for (const string &stop : bus_item.second) {
					cout << stop << " "s;
				}
				cout << endl;
			}
		}
	}
};


// Не меняя тела функции main, реализуйте функции и классы выше

void EraseQuery(Query &q) {
	q.bus = ""s;
	q.stop = ""s;
	q.stops.clear();
}


int main() {
	int query_count;
	Query q;
	cin >> query_count;
	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
		EraseQuery(q);
	}
}
/*
 6
 NEW_BUS 1 4 Syktyvkar Uhta Sosnogorsk Troicko-Pechorsk
 NEW_BUS 2 4 Syktyvkar Kortkeros Ust-Kulom Uhta
 NEW_BUS 3 4 Mikun Syktyvkar Vizinga Obyachevo
 BUSES_FOR_STOP Uhta
 STOPS_FOR_BUS 3
 ALL_BUSES
 */
