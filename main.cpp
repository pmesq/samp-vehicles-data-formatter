#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

struct Vehicle {
	int vehicleModelId;
	string vehicleName;
	string category;
	string modifications;
	string modelName;
};

const int vehicleModelIdStartIndex = 28;
const int vehicleNameStartIndex = 21;
const int categoryStartIndex = 17;
const int modificationsStartIndex = 22;
const int modelNameStartIndex = 19;

string removeQuotes(const string str) {
	string resultedStr;
	for (const char c : str) {
		if (c != '\"') resultedStr.push_back(c);
	}
	return resultedStr;
}

Vehicle readVehicle() {
	Vehicle vehicle;

	string vehicleModelIdParagraph;
	string vehicleNameParagraph;
	string categoryParagraph;
	string modificationsParagraph;
	string modelNameParagraph;

	getline(cin, vehicleModelIdParagraph);
	getline(cin, vehicleNameParagraph);
	getline(cin, categoryParagraph);
	getline(cin, modificationsParagraph);
	getline(cin, modelNameParagraph);

	vehicle.vehicleModelId = stoi(vehicleModelIdParagraph.substr(
			vehicleModelIdStartIndex,
			3));
	vehicle.vehicleName = vehicleNameParagraph.substr(
			vehicleNameStartIndex,
			vehicleNameParagraph.size() - (vehicleNameStartIndex + 6));
	vehicle.category = categoryParagraph.substr(
			categoryStartIndex,
			categoryParagraph.size() - (categoryStartIndex + 6));
	vehicle.modifications = modificationsParagraph.substr(
			modificationsStartIndex,
			modificationsParagraph.size() - (modificationsStartIndex + 6));
	vehicle.modelName = modelNameParagraph.substr(
			modelNameStartIndex,
			modelNameParagraph.size() - (modelNameStartIndex + 6));

	return vehicle;
}

void printVehicleListAsJSON(const list<Vehicle> vehicleList) {
	fstream fs;
	fs.open("output/vehicles.json", fstream::out);
	bool first = true;
	fs << "[";
	for (const Vehicle vehicle : vehicleList) {
		if (first) first = false;
		else fs << ',';
		fs << "\n\t{\n\t\t\"vehicleModelId\": " << vehicle.vehicleModelId << ",\n"
				<< "\t\t\"vehicleName\": \"" << removeQuotes(vehicle.vehicleName) << "\",\n"
				<< "\t\t\"category\": \"" << vehicle.category << "\",\n"
				<< "\t\t\"modifications\": \"" << vehicle.modifications << "\",\n"
				<< "\t\t\"modelName\": \"" << vehicle.modelName << "\"\n\t}";
	}
	fs << "]\n";
	fs.close();
}

void printVehicleListAsYML(const list<Vehicle> vehicleList) {
	fstream fs;
	fs.open("output/vehicles.yml", fstream::out);
	for (const Vehicle vehicle : vehicleList) {
		fs << "-\n\tvehicleModelId: " << vehicle.vehicleModelId << "\n"
				<< "\tvehicleName: " << removeQuotes(vehicle.vehicleName) << "\n"
				<< "\tcategory: " << vehicle.category << "\n"
				<< "\tmodifications: " << vehicle.modifications << "\n"
				<< "\tmodelName: " << vehicle.modelName << "\n";
	}
	fs.close();
}

void printVehicleListAsXML(const list<Vehicle> vehicleList) {
	fstream fs;
	fs.open("output/vehicles.xml", fstream::out);
	fs << "<vehicles>\n";
	for (const Vehicle vehicle : vehicleList) {
		fs << "\t<vehicle>\n"
				<< "\t\t<vehicle-model-id>" << vehicle.vehicleModelId << "</vehicle-model-id>\n"
				<< "\t\t<vehicle-name>" << removeQuotes(vehicle.vehicleName) << "</vehicle-name>\n"
				<< "\t\t<category>" << vehicle.category << "</category>\n"
				<< "\t\t<modifications>" << vehicle.modifications << "</modifications>\n"
				<< "\t\t<model-name>" << vehicle.modelName << "</model-name>\n"
				<< "\t</vehicle>\n";
	}
	fs << "</vehicles>\n";
	fs.close();
}

void printVehicleListAsCSV(const list<Vehicle> vehicleList) {
	fstream fs;
	fs.open("output/vehicles.csv", fstream::out);
	for (const Vehicle vehicle : vehicleList) {
		fs << vehicle.vehicleModelId << ','
				<< removeQuotes(vehicle.vehicleName) << ','
				<< vehicle.category << ','
				<< vehicle.modifications << ','
				<< vehicle.modelName << endl;
	}
	fs.close();
}

int main() {
	list<Vehicle> vehicleList;
	string line;
	while (getline(cin, line)) {
		if (line == "<div style=\"float: left; width: 300px; padding-left: 10px;\">") {
			Vehicle vehicle = readVehicle();
			vehicleList.push_back(vehicle);
		}
	}
	printVehicleListAsJSON(vehicleList);
	printVehicleListAsYML(vehicleList);
	printVehicleListAsXML(vehicleList);
	printVehicleListAsCSV(vehicleList);
	return 0;
}
