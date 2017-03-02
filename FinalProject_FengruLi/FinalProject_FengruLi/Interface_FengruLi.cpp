//include head file
#include "Interface_FengruLi.h"

Interface::Interface()  //initialize variable
{
	choice = 0;
	menu = 0;
	quit = 0;
}


void Interface::interface_function()
{
	cout << "Welcome to the Account Management System." << endl;  
	while (!quit)   //if quit flag doesn't set  display menu and scan choice then processe the choice
	{
		menu_display();
		scan();
		menu_choice();
	}
	write_history();   //before quit the system bank history will be written
}

void Interface::Main_menu()
{
	cout << "\nPlease Select an account to access:" << endl;
	cout << "1.Stock Portfolio Account" << endl;
	cout << "2.Bank Account" << endl;
	cout << "3.Exit" << endl;
	menu = 0;   //update menu variable  to main menu
}

void Interface::Stock_menu()
{
	cout << "\nPlease Select an option:" << endl;
	cout << "1.Display the Price for a Stock Symbol" << endl;
	cout << "2.Display the Current Portfolio" << endl;
	cout << "3.Buy Shares" << endl;
	cout << "4.Sell Shares" << endl;
	cout << "5.View a Graph for the Portfolio Value" << endl;
	cout << "6.View Transaction History" << endl;
	cout << "7.Return to Previous Menu" << endl;
	menu = 1;  //update menu variable  to stock menu
}

void Interface::Bank_menu()
{
	cout << "\nPlease Select an Option:" << endl;
	cout << "1.View Account Balance" << endl;
	cout << "2.Deposit Money" << endl;
	cout << "3.Withdraw Money" << endl;
	cout << "4.Print Out History" << endl;
	cout << "5.Return to Previous Menu" << endl;
	menu = 2;  //update menu variable  to bank menu
}

void Interface::scan()
{
	switch (menu)  
	{
	case 0:     //if it's main menu there will be 3 choice
		cin >> choice;
		cin.ignore(1024, '\n');
		while (choice <= 0 || choice > 3)
		{
			cout << "You Have Input A Wrong Number.Please Re-Enter:";
			cin >> choice;
			cin.ignore(1024, '\n');
		}
		break;
	case 1:   // if it's stock menu there will be 7 choice
		cin >> choice;
		cin.ignore(1024, '\n');
		while (choice <= 0 || choice > 7)
		{
			cout << "You Have Input A Wrong Number.Please Re-Enter:";
			cin >> choice;
			cin.ignore(1024, '\n');
		}
		break;
	case 2:    //if it's bank menu there will be 5 chocie
		cin >> choice;
		cin.ignore(1024, '\n');
		while (choice <= 0 || choice > 5)
		{
			cout << "You Have Input A Wrong Number.Please Re-Enter:";
			cin >> choice;
			cin.ignore(1024, '\n');
		}
		break;
	default:cout << "System Error"; quit = 1; system("Pause");   //if there is some other mistake system will quit
	}

}

void Interface::Main_choice()  
{
	if (menu == 0)
	{
		switch (choice)
		{
		case 1:Stock_menu(); scan(); Stock_choice(); break;    //if choose stock menu  then display stock menu and choose stock function
		case 2:Bank_menu(); scan(); Bank_choice(); break;      //if choose bank menu  then display bank menu and choose bank function
		case 3:quit = 1; break;  //if choose quit then quit
		default:cout << "System Error." << endl; quit = 1; system("Pause");   //if there is some other mistake system will quit
		}
	}
	else  // if there is some other mistake system will quit
	{
		cout << "System Error" << endl;
		quit = 1; 
		system("Pause");
	}
}

void Interface::Stock_choice()
{
	if (menu == 1)
	{
		switch (choice)
		{
		case 1:
		{
			string s;
			cout << "Please Input The Stock Symbol:";
			cin >> s;
			double price = stockaccount.Display_price(s);  
			if (price>0)    //if find the symbol
				cout << "Price Per Share: " << price << endl;
			else     //if not find the symbol
				cout << "Sorry, The Symbol Cannot Be Found." << endl;
			break;
		}
		case 2:stockaccount.Display_portfolio(); break;   //display portfolio
		case 3:stockaccount.Buy_shares(bankaccount); break;   //buy shares
		case 4:stockaccount.Sell_shares(bankaccount); break;  //sell shares
		case 5:stockaccount.view_graph(); break;    //using matlab to plot the graph
		case 6:stockaccount.view_history(); break;  //read history in file
		case 7:menu = 0; break;  //return to previous menu
		default:cout << "System Error." << endl; quit = 1; system("Pause"); //if system error happens then quit
		}
	}
	else  // if there is some other mistake system will quit
	{
		cout << "System Error" << endl;
		quit = 1;
		system("Pause");
	}
}

void Interface::Bank_choice()
{
	if (menu == 2)
	{
		switch (choice)
		{
		case 1:bankaccount.view_balance(); break;   //view balance in bank account 
		case 2:
		{
			cout << "Please Input the Amount of Money You Want to Deposit: ";
			double dmoney;
			cin >> dmoney;
			cin.ignore(1024, '\n');
			while (dmoney <= 0)
			{
				cout << "Sorry, You have Input a Wrong Number.The Amount Should Be Positive.Please Re-enter the Amount: ";
				cin >> dmoney;
				cin.ignore(1024, '\n');
			}
			if (bankaccount.deposit_money(dmoney))  //if deposit succeed
				cout << "Deposit Succeed." << endl;
			else  //if false it means some system error happens then quit
			{
				cout << "System Error." << endl;
				quit = 1;
				system("Pause");
			}
			break;
		}
		case 3:
		{
			cout << "Please Input the Amount of Money You Want to Withdraw: ";
			double wmoney;
			cin >> wmoney;
			cin.ignore(1024, '\n');
			while (wmoney <= 0)
			{
				cout << "Sorry, You have Input a Wrong Number.The Amount Should Be Positive.Please Re-enter the Amount: ";
				cin >> wmoney;
				cin.ignore(1024, '\n');
			}
			if (bankaccount.withdraw_money(wmoney)==false)   //if withdraw fail
			{
				cout << "You Don't Have Enough Money" << endl;
			}
			else   //if withdraw succeed
			{
				cout << "Withdraw Succeed." << endl;
			}
				break;
		}
		case 4:bankaccount.print_history(); break;    // print history in file
		case 5:menu = 0;break;   //return previous menu
		default:cout << "System Error." << endl; quit = 1; system("Pause");  //if system error happens then quit
		}
	}
	else   // if there is some other mistake system will quit
	{
		cout << "System Error" << endl;
		quit = 1;
		system("Pause");
	}
}

void Interface::menu_display()
{
	switch (menu)
	{
	case 0:Main_menu(); break;   //display main menu
	case 1:Stock_menu(); break;  //display stock menu
	case 2:Bank_menu(); break;   //display bank menu
	default:quit = 1; cout << "System Error." << endl; system("Pause"); break;  //if system error happens then quit
	}
}

void Interface::menu_choice()
{
	switch (menu)
	{
	case 0:Main_choice(); break;    //choose main menu choice
	case 1:Stock_choice(); break;   //choose stock menu choice
	case 2:Bank_choice(); break;    //choose bank menu choice
	default:quit = 1; cout << "System Error." << endl; system("Pause"); break;   //if system error happens then quit
	}
}

void Interface::write_history()   //write history to file
{
	ofstream file;   //define ofstream
	file.open("History.txt", ios::app);  // open file and start at end of file
	file << left << setw(11) << setprecision(2) << fixed << bankaccount.get_balance();  //write data to file
	file.close();  //close file
}
