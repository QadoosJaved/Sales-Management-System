#include <iostream>
#include <iomanip>
using namespace std;

struct User{
	int id = 0;
	string username;
	string password;
	bool hasPermission = 0; //Permission to  accounts related things and some other rights;
	bool isAdmin = 0;       //Permission for Admin rights e.g. user management and everything; 
	User() { username = "", password = ""; }
	User(string username_, string password_, bool hasPermission_ = 0, bool isAdmin_ = 0) {
		username = username_;
		password = password_;
		hasPermission = hasPermission_;
		isAdmin = isAdmin_;
	}
};
class UsersList {
private:
	struct UserNode {
		struct User user;
		UserNode* nextUser;
	};
	UserNode* head, * tail = NULL;
public:
	bool AddUser(User user) {
		if (CheckUserName(user))
		{
			UserNode* newNode = new UserNode;
			newNode->user.username = user.username;
			newNode->user.password = user.password;
			newNode->user.hasPermission = user.hasPermission;
			newNode->user.isAdmin = user.isAdmin;
			newNode->nextUser = NULL;

			if (!head) {
				newNode->user.id = ++user.id;
				head = tail = newNode;
			}
			else {
				newNode->user.id = tail->user.id;
				newNode->user.id++;
				tail->nextUser = newNode;
				tail = newNode;
			}
			return 1;
		}
		return 0;
	}
	bool CheckUserName(User user) {
		UserNode* temp = head;
		while (temp) {
			if (temp->user.username == user.username) {
				return 0;
			}
			temp = temp->nextUser;
		}
		return 1;
	}
	User * SearchUser(int id = 0) {
		UserNode* temp = head;
		while (temp) {
			if (temp->user.id == id) {
				return &temp->user;
			}
			temp = temp->nextUser;
		}
		if (!temp)
			return nullptr;
	}
	void UpdateUser(User * user) {
		UserNode* temp = head;
		while (temp){
			if (temp->user.id == user->id) {
				temp->user.username = user->username;
				temp->user.password = user->password;
				temp->user.isAdmin = user->isAdmin;
				temp->user.hasPermission = user->hasPermission;
			}
			temp = temp->nextUser;
		}
	}
	bool DeleteUser(int id = 0) {
		bool isEnd = 1;
		UserNode* prev, * current;
		prev = NULL; 
		current = head;
		while (current){
			//for deleting by username;
			if (id > 0){
				isEnd = 0;
				if (current->user.id == id) {
					if (prev) {
						prev->nextUser = current->nextUser;
						if (!current->nextUser) {
							tail = prev;
						}
					}
					else {
						head = current->nextUser;
						if (!head) {
							tail = nullptr;
						}
					}
					delete current;
					return 1;
				}
				prev = current;
				current = current->nextUser;
			}
			else {
				prev = current;
				current = current->nextUser;
			}
		}
		if (!isEnd) {
			return 0;
		}
		prev->nextUser = NULL;
		tail = prev;
		delete current;
		return 1;

	}
	bool Verify(User user){
		UserNode* temp = head;
		while (temp){
			if (temp->user.username == user.username && temp->user.password == user.password) {
				return 1;
			}
			temp = temp->nextUser;
		}
		return 0;

	}
	bool CheckRights(string username){
		UserNode* temp = head;
		while (temp) {
			if (temp->user.username == username&& temp->user.hasPermission) {
				return 1;
			}
			temp = temp->nextUser;
		}
		return 0;
	}
	bool CheckIsAdmin(string username) {
		UserNode* temp = head;
		while (temp) {
			if (temp->user.username == username && temp->user.isAdmin) {
				return 1;
			}
			temp = temp->nextUser;
		}
		return 0;
	}
	void DisplayUsers() {
		UserNode* temp = head;
		cout << endl;
		cout << setw(10) << left << "Sr #";
		cout << setw(10) << left << "Id";
		cout << setw(15) << left << "UserName";
		cout << setw(15) << left << "Password";
		cout << setw(15) << left << "Permission";
		cout << setw(10) << left << "isAdmin"<<endl;
		int count = 1;
		while (temp) {
			cout << setw(10) << left << count;
			cout << setw(10) << left << temp->user.id;
			cout << setw(15) << left << temp->user.username;
			cout << setw(15) << left << temp->user.password;
			cout << setw(15) << left << temp->user.hasPermission;
			cout << setw(10) << left << temp->user.isAdmin<<endl;
			temp = temp->nextUser;
			count++;
		}
	}
};
struct Product {
	int Id = 0;
	string Name;
	int Price;
	string Size;
	int Cost = 0;
	int OpeningStock = 0;
	int SoldItem = 0;
	Product() {
		Id = 0;
		Name = "";
		Price=0;
		Size = "";
		Cost=0;
		OpeningStock=0;
		SoldItem=0;
	}
	Product( string name, int price, string size, int cost, int openstock) {
		Id = 0;
		Name = name;
		Price = price;
		Size = size;
		Cost = cost;
		OpeningStock = openstock;
	}
	bool isAvailable() {
		return ((OpeningStock - SoldItem) > 0);
	}
	
};
class Products_LinkedList{
private:
	struct ProductNode {
		struct Product product;
		ProductNode* nextProduct;
	};
	ProductNode* head, * tail;
public:
	Products_LinkedList() {
		head = tail = NULL;
	}
	void Add(Product product, bool isSale = 0) {
		ProductNode* newNode = new ProductNode;
		newNode->product.Id = product.Id;
		newNode->product.Name = product.Name;
		newNode->product.Price = product.Price;
		newNode->product.Size = product.Size;
		newNode->product.Cost = product.Cost;
		newNode->product.OpeningStock = product.OpeningStock;
		newNode->product.SoldItem = product.SoldItem;
		newNode->nextProduct = NULL;
		if (!head) {
			if(!isSale)
				newNode->product.Id++;
			head = tail = newNode;
		}
		else {
			if (!isSale) {
				newNode->product.Id = tail->product.Id;
				newNode->product.Id++;
			}
			tail->nextProduct = newNode;
			tail = newNode;
		}
	}
	bool Delete(int id = 0) {
		bool isEnd = 1;
		ProductNode* prev, * current;
		prev = NULL;
		current = head;
		while (current) {
			//for deleting by id specific position;
			if (id > 0) {
				isEnd = 0;
				if (current->product.Id == id) {
					if (prev) {
						prev->nextProduct = current->nextProduct;
						if (!current->nextProduct) {
							tail = prev;
						}
					}
					else {
						head = current->nextProduct;
						if (!head) {
							tail = nullptr;
						}
					}
					delete current;
					return 1;
				}
				prev = current;
				current = current->nextProduct;
			}
			//for deleting from end;
			else {
				prev = current;
				current = current->nextProduct;
			}
			
		}
		if (!isEnd) {
			return 0;
		}
		prev->nextProduct = NULL;
		tail = prev;
		delete current;
		return 1;
		
	}
	Product Search(int id) {
		Product p;
		ProductNode* temp = head;
		while (temp) {
			if (temp->product.Id == id) {
				p = temp->product;
				return p;
			}
			temp = temp->nextProduct;
		}
		return p;
	}
	void DisplayProducts(bool hasPermission =0, bool isReceipt = 0) {
		ProductNode* temp = head;
		cout << endl;
		cout << setw(10) << left << "Sr #";
		if(!isReceipt)
			cout << setw(10) << left << "Id";
		cout << setw(15) << left << "ProductName";
		cout << setw(10) << left << "Price";
		cout << setw(10) << left << "Size";
		if (hasPermission) {
			cout << setw(10) << left << "Cost";
			cout << setw(15) << left << "OpeningStock";
			cout << setw(15) << left << "SoldItems";
			cout << setw(15) << left << "RemianingStock";
		}
		cout << endl;
		int count = 1;
		while (temp)
		{
			cout << setw(10) << left <<count;
			if (!isReceipt)
				cout << setw(10) << left <<temp->product.Id;
			cout << setw(15) << left <<temp->product.Name;
			cout << setw(10) << left <<temp->product.Price;
			cout << setw(10) << left <<temp->product.Size;
			if (hasPermission) {
				cout << setw(10) << left << temp->product.Cost;
				cout << setw(15) << left << temp->product.OpeningStock;
				cout << setw(15) << left << temp->product.SoldItem;
				cout << setw(15) << left << temp->product.OpeningStock - temp->product.SoldItem;

			}
			cout << endl;
			temp = temp->nextProduct;
			count++;
		}
	}
	string ProductNames() {
		ProductNode* temp = head;
		string name = "";
		while(temp){
			name +=temp->product.Name+",";
			temp = temp->nextProduct;
		}
		return name;
	}
	void UpdateSoldItems(Products_LinkedList& items) {
		ProductNode * item = items.head;
		ProductNode * temp;
		while(item){
			temp = head;
			while (temp) {
				if (temp->product.Id == item->product.Id) {
					temp->product.SoldItem++;
					break;	
				}
				temp = temp->nextProduct;
			}
			item = item->nextProduct;
		}
	}
};
struct Sale {
	int Id =0;
	string date;
	Products_LinkedList item;
	int BillAmount = 0;
};
class SalesRecord {
private:
	struct SaleNode {
		Sale sale;
		SaleNode* nextSale;
	};
	SaleNode* head, * tail = NULL;
public:
	void Add(Sale s) {
		SaleNode* newNode = new SaleNode;
		newNode->sale.date = s.date;
		newNode->sale.item = s.item;
		newNode->sale.BillAmount = s.BillAmount;
		newNode->nextSale = NULL;
		if (!head) {
			newNode->sale.Id = ++s.Id;
			head = tail = newNode;
		}
		else {
			newNode->sale.Id = tail->sale.Id;
			newNode->sale.Id++;
			tail->nextSale = newNode;
			tail = newNode;
		}
	}
	bool Delete(int id = 0) {
		bool isEnd = 1;
		SaleNode* prev = NULL, * current= head;
		while (current)
		{
			if (id > 0) {
				isEnd = 0;
				if (current->sale.Id = id)
				{
					if (prev) {
						prev->nextSale = current->nextSale;
						if (!current->nextSale) {
							tail = prev;
						}
					}
					else {
						head = current->nextSale;
						if (!head) {
							tail = NULL;
						}
					}
					delete current;
					return 1;
				}
				prev = current;
				current = current->nextSale;
			}
			else {
				prev = current;
				current = current->nextSale;
			}
		}
		if (!isEnd) {
			return 0;
		}
		prev->nextSale = NULL;
		tail = prev;
		delete current;
		return 1;
	}
	void DisplaySales() {
		SaleNode* temp = head;
		int count = 1;
		cout << setw(10) << left << "Sr #";
		cout << setw(10) << left << "Id";
		cout << setw(15) << left << "Date";
		cout << setw(35) << left << "Items";
		cout << setw(10) << left << "Amount";
		cout << endl;
		int Totalamount = 0;
		while (temp) {
			cout << setw(10) << left <<count;
			cout << setw(10) << left <<temp->sale.Id;
			cout << setw(15) << left <<temp->sale.date;
			cout << setw(35) << left << temp->sale.item.ProductNames();
			cout << setw(10) << left << temp->sale.BillAmount<<endl;
			Totalamount += temp->sale.BillAmount;
			temp = temp->nextSale;
			count++;
		}
		cout << "\nTotal Sales: " << Totalamount<<endl;
	}
};
class Helper {
private:
	bool isAdmin = 0, hasPermission = 0, isAuthorized = 0;
	UsersList userlist;
	Products_LinkedList products;
	SalesRecord sales;
	User LoggedInUser;
public:
	Helper() 
	{
		//adding default Users;
		User user(ToLower("Admin"), "admin", 1, 1);
		userlist.AddUser(user);
		user.username = ToLower("Abrar"); user.password = "abrar";
		user.isAdmin = 0; user.hasPermission = 0;
		userlist.AddUser(user);

		//adding default product;
		Product product1("Shoes",4000, "44", 2500, 10);
		Product product2("Socks",200, "44", 150, 10);
		Product product3("Shirt",2000, "16'", 1500, 10);
		products.Add(product1);
		products.Add(product2);
		products.Add(product3);

	}

	void Login() {
		system("CLS");
		cout << "---------------------------------------------------\n";
		cout << "---------------Sales Management System-------------\n";
		cout << "---------------------------------------------------\n\n";
		string username, password;
		cout << "Enter UserName: ";
		cin >> username;
		cout << "Enter Password: ";
		cin >> password;
		LoggedInUser.username = ToLower(username);
		LoggedInUser.password = password; //object for vaerification;
		if (Authenticate(LoggedInUser)) {
			cout << "Successfully Authorized!\n";
			if (userlist.CheckRights(LoggedInUser.username)) {
				hasPermission = 1;
				if (userlist.CheckIsAdmin(LoggedInUser.username)) {
					isAdmin = 1;
				}
			}
			isAuthorized = 1;
			Menu();
		}
		else {
			cout << "Login Failed!";
			if (EnterChoice()) {
				Login();
			}
			else {
				exit(0);
			}
		}
	}
	string ToLower(string input) {
		for (int i = 0; i < input.length(); i++) {
			input[i] = tolower(input[i]);
		}
		return input;
	}
	bool Authenticate(User user) {
		return userlist.Verify(user);
	}
	void Menu() {
		bool validOption = 1;
		do {
			system("CLS");
			cout << "\n\nWelcome " << LoggedInUser.username << ".\n";
			cout << "---------------------Main Menu---------------------\n";
			cout << "1-) Product List\n";
			cout << "2-) Add new Product\n";
			cout << "3-) Make a Sale\n";
			if (hasPermission) {
				cout << "4-) Delete Product\n";
				cout << "5-) Sales Report\n";

			}
			if (isAdmin) {
				cout << "6-) Users List\n";
				cout << "7-) Add new User\n";
				cout << "8-) Edit User\n";
				cout << "9-) Delete User\n";
			}
			cout << "0-)Logout\n";
			int choice;
			cin >> choice;
			switch (choice) {
			case 0:
				cout << "\nSuccessfully Logout!\n";
				isAdmin = 0; isAuthorized = 0; hasPermission = 0;
				LoggedInUser.username = "", LoggedInUser.password = "";
				Login();
			case 1:
				products.DisplayProducts(hasPermission);
				if (!EnterChoice(0))
					Menu();
				break;
			case 2:
				AddProductOption();
				break;
			case 3:
				MakeSaleOption();
				break;
			case 4:
				if (hasPermission) {
					DeleteProductOption();
				}
				else {
					cout << "Invalid Option!\n Try again: ";
					validOption = 0;
				}
				break;
			case 5:
				if (hasPermission) {
					sales.DisplaySales();
					if (!EnterChoice(0))
						Menu();
				}
				else {
					cout << "Invalid Option!\n Try again: ";
					validOption = 0;
				}
				break;
			case 6:
				if (isAdmin) {
					userlist.DisplayUsers();
					if (!EnterChoice(0))
						Menu();
				}
				else {
					cout << "Invalid Option!\n Try again: ";
					validOption = 0;
				}
				break;
			case 7:
				if (isAdmin) {
					AddUserOption();
				}
				else {
					cout << "Invalid Option!\n Try again: ";
					validOption = 0;
				}
				break;
			case 8:
				if (isAdmin) {
					EditUserOption();
				}
				else {
					cout << "Invalid Option!\n Try again: ";
					validOption = 0;
				}
				break;
			case 9:
				if (isAdmin) {
					DeleteUserOption();
				}
				else {
					cout << "Invalid Option!\n Try again: ";
					validOption = 0;
				}
				break;
			default:
				cout << "Invalid Option!\n Try again: ";
				validOption = 0;

			}
		} while (!validOption);

	}
	void AddProductOption() {
		Product product;
		cout << "\nEnter Product Name:  ";
		cin >> product.Name;
		cout << "Size: ";
		cin >> product.Size;
		cout << "Cost: ";
		cin >> product.Cost;
		cout << "Price: ";
		cin >> product.Price;
		cout << "Opening Stock: ";
		cin >> product.OpeningStock;
		products.Add(product);
		cout << "Product Added!";
		products.DisplayProducts(hasPermission);
		if (!EnterChoice(0))
			Menu();

	}
	void MakeSaleOption() {
		Sale s;
		products.DisplayProducts();
		cout << "Enter Date: ";
		cin >> s.date;
		int choice;
		do {
			cout << "\nEnter Product Ids to Add Products: 0 For Stop\n";
			cin >> choice;
			if (choice > 0) {
				Product p =  products.Search(choice);
				if (p.Id > 0) {
					if (p.isAvailable()) {
						s.item.Add(p, 1);
						s.BillAmount += p.Price;
					}
					else {
						cout << "\nThis product is out of Stock!";
					}
				}
				else {
					cout << "\nProduct not  Found!\n";
				}
			}
		} while (choice != 0); 
		cout << "\nReceipt\n";
		s.item.DisplayProducts(0,1);
		cout << "Total Amount: " << s.BillAmount;
		bool isValid = 1;
		do {
			cout << "\n\nAre you sure want to proceed: (1,0)\n";
			cin >> choice;
			switch (choice) {
			case 1:
				sales.Add(s);
				products.UpdateSoldItems(s.item);
				cout << "Sales Successfully Added!\n";
				break;
			case 2:
				break;
			default:
				cout << "Invalid Input!\n";
				isValid = 0;
				break;
			}
		} while (!isValid);
		
		if (!EnterChoice(0))
			Menu();
	}
	void DeleteProductOption() {
		products.DisplayProducts(hasPermission);
		cout << "\n\nEnter Id to Delete a Product or Enter 0 to Delete from End: ";
		int DelChoice = 0;
		cin >> DelChoice;
		if (products.Delete(DelChoice)) {
			cout << "Product Deleted!\nUpdated Product List!\n\n";
			products.DisplayProducts(hasPermission);
			if (!EnterChoice(0))
				Menu();
		}
		else {
			cout << "Id not found!";
			if (EnterChoice()) {
				DeleteProductOption();
			}
			else {
				Menu();
			}
		}
	}
	void AddUserOption() {
		User newUser;
		cout << "\nEnter Username: ";
		cin >> newUser.username;
		cout << "Enter Password: ";
		cin >> newUser.password;
		cout << "HasPermission: (0,1): ";
		cin >> newUser.hasPermission;
		cout << "isAdmin: (0,1): ";
		cin >> newUser.isAdmin;
		if (userlist.AddUser(newUser)) {
			cout << "User Added!\nUpdated User List\n\n";
			userlist.DisplayUsers();
			if (!EnterChoice(0))
				Menu();
		}
		else {
			cout << "\nUsername already registered!\n";
			if (EnterChoice()) {
				AddUserOption();
			}
			else {
				Menu();
			}
		}
	}
	void EditUserOption() {
		cout << endl;
		userlist.DisplayUsers();
		cout << "Enter id to Edit User: ";
		int id = 0;
		cin >> id;
		User* edited = userlist.SearchUser(id);
		if (edited) {
			cout << "\nEnter Username: ";
			cin >> edited->username;
			cout << "Enter Password: ";
			cin >> edited->password;
			cout << "HasPermission: (0,1): ";
			cin >> edited->hasPermission;
			cout << "isAdmin: (0,1): ";
			cin >> edited->isAdmin;
			userlist.UpdateUser(edited);
			cout << "Updated Successfull!\n";
			userlist.DisplayUsers();
			if (!EnterChoice(0))
				Menu();
		}
		else {
			cout << "Id not found!\n";
			if (EnterChoice())
				EditUserOption();
			else
				Menu();
		}
	}
	void DeleteUserOption() {
		cout << "\nList of Users\n";
		userlist.DisplayUsers();
		bool validOption = 1;
		cout << "\n\nEnter Id to Delete a User or Enter 0 to Delete from End: ";
		int DelChoice = 0;
		cin >> DelChoice;
		if (userlist.DeleteUser(DelChoice)) {
			cout << "User Deleted\n";
			userlist.DisplayUsers();
			if (!EnterChoice(0))
				Menu();
		}
		else {
			cout << "Id not found!\n";
			if (EnterChoice())
				DeleteUserOption();
			else
				Menu();
		}
	}
	bool EnterChoice(bool isError = 1) {
		bool validOption = 1;
		do {
			cout << "Enter choice: \n\n";
			if (isError)
				cout << "1-) Enter Again\n";

			if (isAuthorized) {
				cout << "0-) Menu\n";
			}
			else {
				cout << "0-) Exit ";
			}
			int choice;
			cin >> choice;
			switch (choice) {
			case 0:
				return 0;
				break;
			case 1:
				if (isError) {
					return 1;
				}
				else {
					cout << "Invalid choice Try again!";
					validOption = 0;
				}
				break;
			default:
				cout << "Invalid choice Try again!";
				validOption = 0;
				break;
			}
		} while (!validOption);
	}
};
//Main Function from where the story Begins!
int main() {
	Helper helper;
	helper.Login();
	return 0;
}
