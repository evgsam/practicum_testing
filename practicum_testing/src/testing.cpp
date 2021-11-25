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
	// Наполните полями эту структуру
};

ostream& operator<<(ostream &os, const BusesForStopResponse &r) {
	// Реализуйте эту функцию
	return os;
}

struct StopsForBusResponse {
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
	Query q_;
	map<string, vector<string>> buses_to_stops, stops_to_buses;
public:
	void AddBus(const string &bus, const vector<string> &stops) {
		buses_to_stops[bus] = stops;
		for (const string &stop : stops) {
			stops_to_buses[stop].push_back(bus);
		}
	}
	BusesForStopResponse GetBusesForStop(const string &stop) const {
		if (stops_to_buses.count(stop) == 0) {
			cout << "No stop"s << endl;
		} else {
			for (const string &bus : stops_to_buses.at(stop)) {
				cout << bus << " "s;
			}
			cout << endl;
		}
	}
	StopsForBusResponse GetStopsForBus(const string &bus) const {
		if (buses_to_stops.count(bus) == 0) {
			cout << "No bus"s << endl;
		} else {
			for (const string &stop : buses_to_stops.at(bus)) {
				cout << "Stop "s << stop << ": "s;
				if (stops_to_buses.at(stop).size() == 1) {
					cout << "no interchange"s;
				} else {
					for (const string &other_bus : stops_to_buses.at(stop)) {
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
		if (buses_to_stops.empty()) {
			cout << "No buses"s << endl;
		} else {
			for (const auto &bus_item : buses_to_stops) {
				cout << "Bus "s << bus_item.first << ": "s;
				for (const string &stop : bus_item.second) {
					cout << stop << " "s;
				}
				cout << endl;
			}
		}
	}
};

void Test() {
	istringstream input;
	input.str("4"s);
	input.str("NEW_BUS 1 4 Syktyvkar Uhta Sosnogorsk Troicko-Pechorsk"s);
	input.str("NEW_BUS 2 4 Syktyvkar Kortkeros Ust-Kulom Uhta"s);
	input.str("NEW_BUS 3 4 Mikun Syktyvkar Vizinga Obyachevo"s);
	input.str("BUSES_FOR_STOP Uhta"s);
}

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
