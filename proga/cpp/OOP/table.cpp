#include <iostream>

class Table { 
private:
    float price;
    static inline unsigned count{};
protected:
    float length;
    float width;  
    float height;
public:

    Table(float t_length, float t_width, float t_height, float t_price);
    Table(const Table &t);
    ~Table() {
        count--;
        std::cout << "Table wrecked!" << std::endl;
    }
    void print() const;

    void setHeight(float new_height) {
        height = new_height;
    }
    float getHeight() const {
        return height;
    }

    Table& up(float height) {
        this->height += height;
        return *this;
    }

    friend void setPrice(Table& t, float new_price) {
        t.price = new_price;
    }

    friend float getPrice(Table& t) {
        return t.price;
    }

    static void print_count() {
        std::cout << count << " tables currently exist" << std::endl;
    }
};

Table::Table(float t_length, float t_width, float t_height, float t_price) {
    count++;
    length = t_length;
    width = t_width;
    height = t_height;
    price = t_price;
}
Table::Table(const Table &t) {
    count++;
    length = t.length;
    width = t.width;
    height = t.height + 0.1;
    price = t.price;
}

void Table::print() const {      
        //std::cout << "I'm a print function and I print length, width and height" << std::endl;
        std::cout << "Length: " << length << ", Width: " << width << ", Height: " << height << std::endl;
        std::cout << "Price: " << price << std::endl;
}   

class Monitor {
private:
    int number_of_devices;
public:
    Monitor(int n_devices) {
        number_of_devices = n_devices;
    }
    void print() const {
        std::cout << "Number of devices: " << number_of_devices << std::endl;
    }
};

class DeskTable: public Table, public Monitor {
private:
    float square;
public:

    DeskTable(float t_length, float t_width, float t_height, float t_price, int n_devices): Table(t_length, t_width, t_height, t_price), Monitor(n_devices) {
        square = width*length;
    }
    void print_square() const { 
        std::cout << "Square: " << square << std::endl;
    }   
    void print_length() const {
        std::cout << "Length: " << length << std::endl;
    }
    void print() const {
        Table::print();
        Monitor::print();
        print_square();
    }
};

int main() {

    Table table{1.5, 2, 0.75, 1000};
    //table.print_count();

    //Table* ptr = &table;

    //ptr->length = 1.5;
    //ptr->width = 2.0;
    //ptr->height = 0.75;
    table.print();
    table.setHeight(1.2);
    std::cout << table.getHeight() << std::endl;

    //std::cout << "Length: " << ptr->length << std::endl;
    
    Table desk_table{table};
    //desk_table.print_count();
    desk_table.print();
    std::cout << desk_table.getHeight() << std::endl;

    {
    const Table sTable{1.5, 2, 0.75, 1000};  
    //sTable.print_count();
    sTable.print();
    sTable.print_count();
    }

    table.print_count();
    table.up(0.1).up(0.2).up(0.3);
    table.print();

    setPrice(table, 3000);
    std::cout << "Price: " << getPrice(table) << std::endl;     

    DeskTable deskTable{1.5, 2, 0.75, 1000, 3};
    deskTable.print_square();
    deskTable.print_length();
    deskTable.print();

    return 0;
}   