#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <deque>

class Vehicle {
public:
    std::string manufacturer;
    std::string model;
    int year;
    int price;

    Vehicle(std::string manufacturer, std::string model, int year, int price) {
        this->manufacturer = manufacturer;
        this->model = model;
        this->year = year;
        this->price = price;
    }
    virtual ~Vehicle(){};
    std::string operator[](unsigned index) {
        switch (index)
        {
        case 0: return manufacturer;
        case 1: return model;
        case 2: return std::to_string(year);
        case 3: return std::to_string(price);
        default: return "kys";
        }
    }
    void print() {
        std::cout << model << " manufactured by " << manufacturer << " in " << year << ". Price: " << price << std::endl;
    }
};

class Car: public Vehicle {
public:
    int num_doors;
    std::string body_style;

    Car(std::string manufacturer, std::string model, int year, int price, int num_doors, std::string body_style):
        Vehicle{manufacturer, model, year, price}, num_doors{num_doors}, body_style{body_style} {}
};

class Truck: public Vehicle {
public:
    std::string bed_length;
    std::string towing_capacity;

    Truck(std::string manufacturer, std::string model, int year, int price, std::string bed_length, std::string towing_capacity ):
        Vehicle{manufacturer, model, year, price}, bed_length{bed_length}, towing_capacity{towing_capacity} {}
};

class Garage {
public:
    std::deque<Vehicle> vehicles;

    void add(Vehicle vehicle) {     
        vehicles.push_back(vehicle);
        std::cout << "Added "; vehicle.print();
    }
    void print() {
        throw "Garage cannot be printed!";
        for (Vehicle vehicle: vehicles) {vehicle.print();}
    }
    template<typename T> int find(T prop) {
        int i = 1;
        for (Vehicle vehicle: vehicles) {
            for (int j = 0; j<4; j++) {
                std::ostringstream str1;
                std::ostringstream str2;
                str2 << vehicle[j];
                str1 << prop;
                if (str1.str() == str2.str()) {return i;}
            }
            i++;
        }
        return -1;
    }
};

int main() {

    Car car{"Toyota", "Camry", 2022, 2900000, 4, "Sedan"};
    Truck truck{"Ford", "F-MAX", 2023, 6000000, "6162", "13t"};
    truck.print();
    Vehicle vehicle{truck};
    vehicle.print();
    
    Vehicle* pVehicle = &car;
    Car* car2{dynamic_cast<Car*>(pVehicle)};
    car2->print();

    Vehicle* vehicles[]{&car, &truck};
    for(const auto& vehicle: vehicles){
        vehicle->print();
    }

    std::cout << car[0] << "\n" << car[1] << "\n" << car[2] << "\n" << car[3]<< std::endl;
    
    auto g = Garage();
    g.add(car);
    g.add(truck);
    try {g.print();}
    catch (const char* error_message) {std::cout << error_message << std::endl;}

    std::cout << g.find("F-MAX") << std::endl;
    std::cout << g.find("Ferrari") << std::endl;
    std::cout << g.find(2023) << std::endl;
    std::cout << g.find (2024) << std::endl;

    return 0;
}