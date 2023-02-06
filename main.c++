#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Client
{
    int id;
    string name;
};

struct Product
{
    int id;
    string name;
    double price;
    int stock;
};

struct Sale
{
    int id;
    int productId;
    int clientId;
    int quantity;
};

vector<Client> clients;
vector<Product> products;
vector<Sale> sales;

void writeClientsToFile()
{
    ofstream file("clients.txt");
    for (Client c : clients)
    {
        file << c.id << "," << c.name << endl;
    }
    file.close();
}

void readClientsFromFile()
{
    ifstream file("clients.txt");
    string line;
    while (getline(file, line))
    {
        int id;
        string name;
        int pos = line.find(",");
        id = stoi(line.substr(0, pos));
        name = line.substr(pos + 1);
        clients.push_back({id, name});
    }
    file.close();
}

void writeProductsToFile()
{
    ofstream file("products.txt");
    for (Product p : products)
    {
        file << p.id << "," << p.name << "," << p.price << "," << p.stock << endl;
    }
    file.close();
}

void readProductsFromFile()
{
    ifstream file("products.txt");
    string line;
    while (getline(file, line))
    {
        int id, stock;
        string name;
        double price;
        int firstComma = line.find(",");
        int secondComma = line.find(",", firstComma + 1);
        int thirdComma = line.find(",", secondComma + 1);
        id = stoi(line.substr(0, firstComma));
        name = line.substr(firstComma + 1, secondComma - firstComma - 1);
        price = stod(line.substr(secondComma + 1, thirdComma - secondComma - 1));
        stock = stoi(line.substr(thirdComma + 1));
        products.push_back({id, name, price, stock});
    }
    file.close();
}

void writeSalesToFile()
{
    ofstream file("sales.txt");
    for (Sale s : sales)
    {
        file << s.id << "," << s.productId << "," << s.clientId << "," << s.quantity << endl;
    }
    file.close();
}

void readSalesFromFile()
{
    ifstream file("sales.txt");
    string line;
    while (getline(file, line))
    {
        int id, productId, clientId, quantity;
        int firstComma = line.find(",");
        int secondComma = line.find(",", firstComma + 1);
        int thirdComma = line.find(",", secondComma + 1);
        id = stoi(line.substr(0, firstComma));
        productId = stoi(line.substr(firstComma + 1, secondComma - firstComma - 1));
        clientId = stoi(line.substr(secondComma + 1, thirdComma - secondComma - 1));
        quantity = stoi(line.substr(thirdComma + 1));
        sales.push_back({id, productId, clientId, quantity});
    }
    file.close();
}

void registerClient()
{
    int id;
    string name;
    cout << "Enter the client ID: ";
    cin >> id;
    cout << "Enter the client name: ";
    cin >> name;
    clients.push_back({id, name});
    writeClientsToFile();
}

void listClients()
{
    cout << "List of clients: " << endl;
    for (Client c : clients)
    {
        cout << c.id << " - " << c.name << endl;
    }
}

void deleteClient()
{
    int id;
    cout << "Enter the client ID to delete: ";
    cin >> id;
    int index = -1;
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].id == id)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        clients.erase(clients.begin() + index);
        writeClientsToFile();
    }
    else
    {
        cout << "Client not found." << endl;
    }
}

void registerProduct()
{
    int id;
    string name;
    double price;
    int stock;
    cout << "Enter the product ID: ";
    cin >> id;
    cout << "Enter the product name: ";
    cin >> name;
    cout << "Enter the product price: ";
    cin >> price;
    cout << "Enter the product stock: ";
    cin >> stock;
    products.push_back({id, name, price, stock});
    writeProductsToFile();
}

void listProducts()
{
    cout << "List of products: " << endl;
    for (Product p : products)
    {
        cout << p.id << " - " << p.name << " - " << p.price << " - " << p.stock << endl;
    }
}

void deleteProduct()
{
    int id;
    cout << "Enter the product ID to delete: ";
    cin >> id;
    int index = -1;
    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        products.erase(products.begin() + index);
        writeProductsToFile();
    }
    else
    {
        cout << "Product not found." << endl;
    }
}

void sellProduct()
{
    int productId, clientId, quantity;
    cout << "Enter the product ID: ";
    cin >> productId;
    cout << "Enter the client ID: ";
    cin >> clientId;
    cout << "Enter the quantity: ";
    cin >> quantity;
    int productIndex = -1, clientIndex = -1;
    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].id == productId)
        {
            productIndex = i;
            break;
        }
    }
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].id == clientId)
        {
            clientIndex = i;
            break;
        }
    }
    if (productIndex == -1)
    {
        cout << "Product not found." << endl;
        return;
    }
    if (clientIndex == -1)
    {
        cout << "Client not found." << endl;
        return;
    }
    if (products[productIndex].stock < quantity)
    {
        cout << "Not enough stock." << endl;
        return;
    }
    products[productIndex].stock -= quantity;
    sales.push_back({(int)sales.size() + 1, productId, clientId, quantity});
    writeProductsToFile();
    writeSalesToFile();
}

int main()
{
    readClientsFromFile();
    readProductsFromFile();
    readSalesFromFile();
    while (true)
    {
        cout << "1 - Register client" << endl;
        cout << "2 - List clients" << endl;
        cout << "3 - Delete client" << endl;
        cout << "4 - Register product" << endl;
        cout << "5 - List products" << endl;
        cout << "6 - Delete product" << endl;
        cout << "7 - Sell product" << endl;
        cout << "0 - Exit" << endl;
        int option;
        cout << "Enter your option: ";
        cin >> option;
        if (option == 1)
        {
            registerClient();
        }
        else if (option == 2)
        {
            listClients();
        }
        else if (option == 3)
        {
            deleteClient();
        }
        else if (option == 4)
        {
            registerProduct();
        }
        else if (option == 5)
        {
            listProducts();
        }
        else if (option == 6)
        {
            deleteProduct();
        }
        else if (option == 7)
        {
            sellProduct();
        }
        else if (option == 0)
        {
            break;
        }
    }
    return 0;
}
