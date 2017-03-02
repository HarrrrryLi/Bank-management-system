//include head file
#include "Account_FengruLi.h"

double Account::balance = 1000;  //intialized static variable balance

void Account::set_balance(double money)  //set balance
{
	balance = money;
}

double Account::get_balance()  //get balance value
{
	return balance;
}

BankAccount::BankAccount()   //construction function
{
	ifstream file;  //define ifstream variable
	file.open("History.txt");  //open history file
	if(file.is_open())
	{
	string s;  //define variable to store string in history file
    while (!file.eof())  //if not the end of the file
	{
		file >> s;  //read file
		file.ignore(1024,'\n');  //ignore data after the balance in the line
	}
	if(s!="Balance")   //if the string is not equal to balance means that there are balance history
		set_balance(stod(s));//change string to double and set balance 
	file.close();  //close file
	}
}

bool BankAccount::deposit_money(double money)  //deposit money
{
	set_balance(get_balance() + money);  //set balance with balance now and the entered money
	time_t now = time(NULL);  //set parameter of time 
	tm *lt = localtime(&now);  //get local time
	ofstream file;  //define ofstream variable
	file.open("bank_transaction_history.txt",ios::app);  //open file and start at the end of file
	if (file.is_open())
	{
		//write data into file	
		file << left << setw(10) << "Deposit" << "$" << setw(9) << setprecision(2) << fixed << money << lt->tm_mon + 1 << "/" << lt->tm_mday << "/" << setw(7) << lt->tm_year + 1900 << "$" << setw(9) << get_balance() << endl;
		file.close();//close file
	}
		return true;
}

bool BankAccount::withdraw_money(double money)  //withdraw money
{
	if (get_balance() >= money)   //if the present balance is enough 
	{
		set_balance(get_balance() - money);  //set balance
		time_t now = time(NULL); //set parameter of time 
		tm *lt = localtime(&now); //get local time
		ofstream file;  //define ofstream variable
		file.open("bank_transaction_history.txt", ios::app); //open file and start at the end of file
		if (file.is_open())
		{
	    //write data into file	
		file << left << setw(10) << "WithDraw" << "$" << setw(9) << setprecision(2) << fixed << money << lt->tm_mon + 1 << "/" << lt->tm_mday << "/" << setw(7) << lt->tm_year + 1900 << "$" << setw(9) << get_balance() << endl;
		file.close();//close file
		}
		return true;
	}
	else  //otherwise return false
	  return false;
}

void BankAccount::print_history()
{
	ifstream file;  //define ifstream
	file.open("bank_transaction_history.txt",ios::in); //open file with read
	if (file.is_open())
	{
		while (!file.eof()) //if it's not the end of file
		{
			string s;
			getline(file, s);   //get line in file
			cout << s << endl;  //print out
		}
		file.close();//close file
	}
}

void BankAccount::view_balance()
{
	cout << "You Have $ " << get_balance() << " in your bank account." << endl; //output balance
}

Node::Node()   //node constructor function to initialize the variable
{
	symbol = '\0';
	stock_number = 0;
}

DoubleLinkedList::DoubleLinkedList()   //double linked list constructor function to initialize the variable
{
	Head = Tail = NULL;
}

StockAccount::StockAccount()  //read portfolio file to get information
{
	ifstream file;
	file.open("Portfolio.txt");  //open file
	if (file.is_open())  //if file is open
	{
		if (!file.eof())  //if it's not the end of file
		{
			file.ignore(1024, '\n');  //ignore title
			while (!file.eof())  //if it's not the end of file add the new node into double likned list
			{
				Node *temp = new Node;
				string s;
				double num;
				file >> s;
				file >> num;
				file.ignore(1024, '\n');
				if (s != "\0"&&num > 0)
				{
					temp->symbol = s;
					temp->stock_number = num;
					if (stock.Head == NULL)  //if double linked list is empty
					{
						stock.Head = stock.Tail = temp;
					}
					else  //if it's not empty
					{
						temp->pre = stock.Tail;
						stock.Tail->next = temp;
						stock.Tail = temp;
					}
				}
			}
			sort();  //sort
		}
		file.close();  //file close
	}

}

StockAccount::~StockAccount()   //close matlab engine write data to history file delete double linked list
{
	if(ep!=NULL)// if the matlab engine is open 
	 engClose(ep);  //close matlab engine 
	map<string, double> stockprice = Random_Readf();  //read stock value
	map<string, double>::iterator it;  //define iterator
	double sum=0;  //define sum value to store total value of portfolio
	if (stock.Head !=NULL && stock.Tail!=NULL)   //if there are more than two node in double linked list
	{
		ofstream file;
		file.open("Portfolio.txt");
		if (file.is_open())
		{
			file << left << setw(8) << "Symbol" << setw(8) << "Number" << endl;  //write title
			Node *temp = stock.Head;  //define a temperate pointer point to each node in double linked list start at head
			for (; temp != stock.Tail; temp = temp->next)  //go through every node except tail
			{
				it = stockprice.find(temp->symbol);  //find symbol in map
				file << left << setw(8) << temp->symbol << setw(8) << setprecision(2) << fixed << temp->stock_number << endl; //write portfolio information to file
				if (it != stockprice.end())   //if it can be found in map
					sum += temp->stock_number*it->second;   //add the value of this stock with total value
			}
			it = stockprice.find(stock.Tail->symbol);  //find tail node symbol
			sum += stock.Tail->stock_number*it->second; //add it to total value
			file << left << setw(8) << stock.Tail->symbol << setw(8) << setprecision(2) << fixed << stock.Tail->stock_number; //write portfolio information to file
			file.close();
		}
		for (Node *temp = stock.Head; temp != stock.Tail; temp = temp->next, delete temp->pre);
		delete stock.Tail;
	}
	ofstream file;  //define ofstream variable
	file.open("History.txt", ios::app);   //open file and start at the end of file
	if(file.is_open())
	{
		time_t now = time(NULL);   //set parameter of time
		tm *lt = localtime(&now);  //get local time
		//write data into file
		file << left << setw(23)<<setprecision(2)<< fixed << sum << setw(5) << asctime(lt);
		file.close(); //close the file
	}
}

map<string, double> StockAccount::Random_Readf()  //random read file and the data are stored in a map return this map
{
	map<string, double> stockprice;  //define map
	string symbol, price;  //define string variable to scan the string in file
	srand(time(NULL));  //set random function always change seed
	int file_num;  //define variable to decide which file to access
	file_num= rand() % 2;  //get random value
	ifstream file; //define ifstream variable
	if (!file_num)  //if file_num equal to 1 open result 2
		file.open("Result_2.txt");
	else   //otherwise open result1
		file.open("Result_1.txt");
	if(file.is_open())
	{
		while (!file.eof())  // if it's not the end of file
		{
			getline(file,symbol,'\t');  //before first \t is the symbol
			getline(file, price, '\t');  //after first \t but before second \t is the price
			file.ignore(1024, '\n');  //ignore other part in the line
			stockprice.insert(pair<string, double>(symbol, stod(price)));  //add symbol and price to the map
		}
		file.close();  //close file
	}
	return stockprice;  //return the map
}

double StockAccount::Display_price(string s)   //display price of a stock
{
	map<string,double> stockprice;  //define a map
	stockprice = Random_Readf();  //get map from random_readf function
		map<string, double>::iterator it;  //define map iterator
		it = stockprice.find(s);  //find the symbol
		if (it != stockprice.end())  //if the symbol is found
			return it->second;   //return price
		else    //else return 0
			return 0;
}

bool StockAccount::sorted(map<string, double> m)  //judge whether the double linked list is sorted
{
	Node *temp = stock.Head;    //define temperate pointer to node 
	while (temp != stock.Tail)   //if temp don't equal to tail
	{
		map<string, double>::iterator it1;   //define map iterator
		map<string, double>::iterator it2;   //define map iterator
		it1 = m.find(temp->symbol);  //find the temp price
		it2 = m.find(temp->next->symbol);  //find the next pric
		if ((temp->stock_number*it1->second) <= (temp->next->stock_number*it2->second))  //if the total value of former node is less than that of latter node then break
			break;
		else   //otherwise go to next node
		{
			temp = temp->next;
		}
	}
	if (temp != stock.Tail)  //if it's not equal to tail means it has some nodes whose total value is less than next one  than return flase
		return false;   
	else  //otherwise return true
		return true;
}

map<string,double> StockAccount::sort()   //sort double linked list
{
	map<string, double> stockprice;  //define a map
	stockprice = Random_Readf();  //get map after read file
	while (!sorted(stockprice))   //if the double linked list isn't sorted than sort it
	{
		Node *temp = stock.Head;  //define variable pointer point to node 
		while (temp != stock.Tail)  //if it's not the tail
		{
			Node *temp_next = temp->next;  //define variable pointer point to next node 
			map<string, double>::iterator it1;  //define map iterator
			map<string, double>::iterator it2;  //define map iterator
			it1 = stockprice.find(temp->symbol);  //find the price of this node stock
			it2 = stockprice.find(temp_next->symbol);  //find the price of next node stock
			if ((temp->stock_number*it1->second) <= (temp_next->stock_number*it2->second))  //if the total value of next node is lager than this node then swap these node
			{
				if (temp == stock.Head && temp_next==stock.Tail)  //if there are two nodes in double linked list
				{
					stock.Head = temp_next;
					temp_next->pre = temp->pre;
					temp->pre = temp_next;
					stock.Tail = temp;
					temp->next = temp_next->next;
					temp_next->next = temp;
				}
				else if (temp == stock.Head)  //if it's the head of double linked list
				{
					stock.Head = temp_next;
					temp_next->pre = temp->pre;
					temp->pre = temp_next;
					temp_next->next->pre = temp;
					temp->next = temp_next->next;
					temp_next->next = temp;
				}
				else if (temp_next == stock.Tail)  // if the next node if the tail of double linked list
				{
					temp->pre->next = temp_next;
					temp_next->pre = temp->pre;
					temp->pre = temp_next;
					stock.Tail = temp;
					temp->next = temp_next->next;
					temp_next->next = temp;
				}
				else if (temp != stock.Head)  //if it's the middle node in double linked list
				{
					temp->pre->next = temp_next;
					temp_next->pre = temp->pre;
					temp->pre = temp_next;
					temp_next->next->pre = temp;
					temp->next = temp_next->next;
					temp_next->next = temp;
				}
			}
			else  //if the total value of this node is larger than move to next node
			 temp = temp->next;
		}
	}
	return stockprice;  //return the map
}

void StockAccount::Display_portfolio()    //display portfolio
{
	map<string,double> stockprice=sort();  //get map with sort function
	double sum = 0;  //variable to store total value of portfolio
	cout << "Cash Balance=$ " << setprecision(2) << fixed << get_balance() << endl;  //output cash balance
	if (stock.Head != stock.Tail)  //if there are more than one node in double linked list
	{
		cout << left << setw(14) << "CompanySymbol" << setw(7) << "Number" << setw(14) << "PricePerShare" << setw(10) << "TotalValue" << endl;  //out put title
		for (Node *temp = stock.Head; temp != stock.Tail; temp = temp->next)  //go through every node except tail
		{
			map<string, double>::iterator it;    //define map iterator
			it = stockprice.find(temp->symbol);  //find the price of each stock
			sum += it->second*temp->stock_number;  //caculate total value of portfolio except tail
			//output data
			cout << left << setw(14) << temp->symbol << setw(7) << temp->stock_number << setw(14) << setprecision(2) << fixed << it->second << setw(10) << (it->second*temp->stock_number) << endl;
		}
		map<string, double>::iterator it;  //define map iterator
		it = stockprice.find(stock.Tail->symbol); //find the price
		sum+=it->second*stock.Tail->stock_number;  //calculate total value
		//output data
		cout << left << setw(14) << stock.Tail->symbol << setw(7) << stock.Tail->stock_number << setw(14) << setprecision(2) << fixed << it->second << setw(10) << (it->second*stock.Tail->stock_number) << endl;
		cout << "Total Portfolio value: $" << sum << endl;
	}
	else if (stock.Head != NULL)  //if there is a node in double linked list
	{
		cout << left << setw(14) << "CompanySymbol" << setw(7) << "Number" << setw(14) << "PricePerShare" << setw(10) << "TotalValue" << endl;  //output title
		map<string, double>::iterator it; //define map iterator
		it = stockprice.find(stock.Head->symbol);  //find price 
		sum += it->second*stock.Head->stock_number;  //calculate total value
		//output data
		cout << left << setw(14) << stock.Head->symbol << setw(7) << stock.Head->stock_number << setw(14) << setprecision(2) << fixed << it->second << setw(10) << (it->second*stock.Head->stock_number) << endl;
		cout << "Total Portfolio value: $" << sum << endl;
	}
	else  //don't have any stock
		cout << "You Don't Have Any Stock." << endl;  

}

void StockAccount::Buy_shares(BankAccount &bankaccount)  //buy shares
{
	map<string, double> stockprice;  //define map 
	stockprice = Random_Readf();  //get map from file
	string symbol;  //user input symbol
	double price;  // user input the price
	double number; //user input number
	cout << "Please Input the Stock You Want to Buy: ";
	cin >> symbol;
	cin.ignore(1024, '\n');
	map<string, double>::iterator it; //define map iterator
	it = stockprice.find(symbol);  //find price
	while (it == stockprice.end())  //don't find the symbol
	{
		cout << "Don't Have the Stock You Input.Please Re-enter:";
		cin >> symbol;
		cin.ignore(1024, '\n');
		it = stockprice.find(symbol); 
	}

	cout << "Please Input the Amount You Want to Buy:";
	cin >> number;
	cin.ignore(1024, '\n');
	while (number < 0)  // if input negative number
	{
		cout << "The Amount Cannot Be Negative.Please Re-enter: ";
		cin >> number;
		cin.ignore(1024, '\n');
	}

	cout << "Please Input the Maximum Cost of Each Share:";
	cin >> price;
	cin.ignore(1024, '\n');
	while (price < 0)  //if input negative price
	{
		cout << "The Cost Cannot Be Negetive.Please Re-enter:";
		cin >> price;
		cin.ignore(1024, '\n');
	}

	if (price > it->second)  //if the price is smaller than the maximum cost
	{
		if (it->second*number <= bankaccount.get_balance())  //if the total cost is less than balance
		{
			
			Node *temp;
			if (stock.Head == NULL && stock.Tail == NULL)  //if there is no node
			{
				temp = new Node;
				temp->stock_number = number;
				temp->symbol = symbol;
				stock.Head = stock.Tail = temp;
			}
			else if (stock.Head == stock.Tail)  // if there is one node 
			{
				if (stock.Tail->symbol != symbol)  //if there is no same stock than creat a new node add it into double linked list
				{
					temp = new Node;
					temp->stock_number = number;
					temp->symbol = symbol;
					temp->pre = stock.Tail;
					stock.Tail->next = temp;
					stock.Tail = temp;
				}
				else if (stock.Tail->symbol == symbol)  //otherwise
					stock.Tail->stock_number += number;
			}
			else   //otherwise
			{
				for (temp = stock.Head; temp != stock.Tail; temp = temp->next)  //go through the double linked list to find whether there is a same stock
					if (temp->symbol == symbol)
						break;
				if (temp == stock.Tail && stock.Tail->symbol != symbol)  //if there is no same stock than creat a new node and add it into double linked list
				{
					temp = new Node;
					temp->stock_number = number;
					temp->symbol = symbol;
					temp->pre = stock.Tail;
					stock.Tail->next = temp;
					stock.Tail = temp;
				}
				else if (temp != stock.Tail)  // if there is a same not in tail
					temp->stock_number += number;
				else if (stock.Tail->symbol == symbol)  //if there is a same in tail
					stock.Tail->stock_number += number;
			}

			sort();  //sort double linked list
			bankaccount.withdraw_money(number*it->second); //withdraw money
			time_t now = time(NULL);  //set parameter of time
			tm *lt = localtime(&now);  //get local time
			ofstream file;  //define ofstream variable
			file.open("stock_transaction_history.txt", ios::app);	  //open file and start at the end of file		
			if(file.is_open())
			{
			//write data into file	
			file << left << setw(8) << "Buy" << setw(12) << symbol << setw(8) << number << "$" << setprecision(2) << fixed << setw(14) << it->second << "$" << fixed << setw(11) << number*it->second << setfill('0') << lt->tm_hour << ":" << lt->tm_min << ":" <<  setw(2) << lt->tm_sec << endl;
			file.close();  //close the file
			}
			//output data
			cout << "Transaction Succeed.You Have Purchased " << number << " Shares of " << symbol << " at $ " << setprecision(2) << fixed << it->second << " Each for a Total of $ " << setw(2) << it->second*number << endl;
		}
		else   //don't have enough money
			cout << "Sorry, You Don't Have Enough Money." << endl;
	}
	else    //maximum cost is less
		cout << "The Cost Per Stock Is Higher Than Your Maximum Cost." << endl;
}

void StockAccount::Sell_shares(BankAccount &bankaccount)  //sell shares
{
	map<string, double> stockprice;  //define map
	stockprice = Random_Readf();  //get map from file
	string symbol;  //user input symbol
	double number;  //user input number
	double price;   //user input price
	if (stock.Head == NULL&&stock.Tail == NULL)   //if there is no stock
	{
		cout << "Sorry,You Don't Have Any Stock." << endl;
	}
	else  //otherwise
	{
		cout << "Please Input the Stock You Want to Sell:"; //input symbol
		cin >> symbol;
		cin.ignore(1024, '\n');
		Node *temp = stock.Head;
		for (; temp != stock.Tail; temp = temp->next)  //go through every node in double linked list except tail
			if (temp->symbol == symbol)
				break;
		if (temp == stock.Tail&&stock.Tail->symbol != symbol)  //if don't have the stock
			cout << "Sorry,You Don't Have This Stock In Your Portfolio." << endl;
		else  //otherwise
		{
			if (stock.Tail->symbol == symbol) //if the symbol in tail is same with input
				temp = stock.Tail;  
			cout << "Please Input the Amount You Want to Sell: ";
			cin >> number;
			cin.ignore(1024, '\n');
			while (number < 0)  //if input negative number
			{
				cout << "The Amount Cannot Be Negative.Please Re-enter:";
				cin >> number;
				cin.ignore(1024, '\n');
			}
			if (number > temp->stock_number)  //if there is no enough number of stock
				cout << "Sorry, You don't Have Enough Amount of Stock." << endl;
			else //otherwise
			{
				cout << "Please Input The Minimum Price of Each Stock£º";
				cin >> price;
				cin.ignore(1024, '\n');
				while (price < 0)  //input negative price
				{
					cout << "The Price of Each Stock Cannot Be Negative.Please Re-enter:";
					cin >> price;
					cin.ignore(1024, '\n');
				}
				map<string, double>::iterator it;  //define map iterator
				it = stockprice.find(symbol);  //find the price
				if (it->second < price)  //if the price is lower than minimum price
					cout << "The Price is Lower Than Your Minimum Price." << endl;
				else  //otherwise
				{
					bankaccount.deposit_money(it->second*number);  //deposit money
					temp->stock_number -= number;  //minues number of stock
					if (temp->stock_number == 0)  //if the number becomes zero
					{
						if (temp != stock.Tail&&temp != stock.Head)  //if it's not  head or tail 
						{
							temp->next->pre = temp->pre;
							temp->pre->next = temp->next;
							delete temp;
						}
						else if (temp == stock.Tail)  //if it's tail
						{
							temp->pre->next = NULL;
							stock.Tail = temp->pre;
							delete temp;
						}
						else if (temp == stock.Head) //if it's head
						{
							stock.Head = temp->next;
							temp->next->pre = NULL;
							delete temp;
						}
					}
					sort();   //sort double linked list
					time_t now = time(NULL);  //set time parameter
					tm *lt = localtime(&now);  //get local time
					ofstream file;  //define ofstream variable
					file.open("stock_transaction_history.txt", ios::app);  //open file and start at the end of file
					if(file.is_open())
					{
				    //write data to file
					file << left << setw(8) << "Sell" << setw(12) << symbol << setw(8) << number << "$" << setprecision(2) << fixed << setw(14) << it->second << "$" << fixed << setw(11) << number*it->second << setfill('0') << lt->tm_hour << ":" << lt->tm_min << ":" << setw(2) << lt->tm_sec << endl;
					file.close();  //close file
					}
					//output data
					cout << "Transaction Succeed.You Have Sold " << number << " Shares of " << symbol << " at $ " << setprecision(2) << fixed << it->second << " Each for a Total of $ " << setfill('0') << setw(2) << it->second*number << endl;
				}
			}


		}

	}
}

void StockAccount::view_history()   //view transaction history
{
	ifstream file;  //define ifstream variable
	file.open("stock_transaction_history.txt");   // open file
	if (file.is_open())
	{
		while (!file.eof()) //if it's not the end of file
		{
			string s;
			getline(file, s);  //get data in file
			cout << s << endl;  //output data
		}
		file.close();  //close file
	}
}

void StockAccount::view_graph()   //use matlab to plot a graph of history
{
	ep = engOpen(NULL);  //open matlab engine
	if (ep == NULL)  //if open engine failed
	{
		cout << "Error: Not Found" << endl;
		exit(1);
	}
	vector<double> b, p;  //define to vector to get history
	double buffer;  //define file scan buffer
	mxArray *b_history, *p_history;  //define matlab matrix to pass data
	ifstream file;  //define ifstream variable
	file.open("History.txt"); //open file
	if(file.is_open())
	{
	file.ignore(1024, '\n'); //ignore file line which is title
	while (!file.eof())  //if it's not the end of file
	{
		file >> buffer;  //read first data in a line
		b.push_back(buffer);  //push back in balance vector
		file >> buffer;  //read second data in a line
		p.push_back(buffer);  //push back in portfolio vector
		file.ignore(1024, '\n');
	}
	file.close();  //close file
	} 
	double *b_array = new double[b.size()]; //define a pointer point to array to store balance data
	double *p_array = new double[p.size()];  //define a pointer point to array to store portfolio data
	for (int cnt = 0; cnt < b.size(); cnt++)  //store data from vector to array
		b_array[cnt] = b[cnt];
	for (int cnt = 0; cnt < p.size(); cnt++)  //store data from vector to array
		p_array[cnt] = p[cnt];

	//pass balance data
	b_history = mxCreateDoubleMatrix(1,b.size(), mxREAL);  
	memcpy((void *)mxGetPr(b_history), (void *)b_array, sizeof(double)*b.size());
	engPutVariable(ep, "balance", b_history);
	//pass portifolio data
	p_history = mxCreateDoubleMatrix(1,p.size() , mxREAL);
	memcpy((void *)mxGetPr(p_history), (void *)p_array, sizeof(double)*p.size());
	engPutVariable(ep, "Portfolio", p_history);
	//plot command
	engEvalString(ep, "figure(1);title('Account History');xlabel('Transcation Number');ylabel('Amount($)');hold('all');plot(balance,'r');hold('all');plot(Portfolio,'b');legend('Balance','Portfolio Total Value');");
	mxDestroyArray(b_history);  //destory matlab array
	mxDestroyArray(p_history);  //destory matlab array
	delete[] p_array;  //delete array 
	delete[] b_array;  //delete array 


}
