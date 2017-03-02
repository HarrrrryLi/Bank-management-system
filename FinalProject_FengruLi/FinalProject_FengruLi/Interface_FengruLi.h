//Interface class is used to be interface between main function and account class .It's adapter design pattern

#pragma once
//include head file
#include "Account_FengruLi.h"

#ifndef INTERFACE_FENGRULI_H
#define INTERFACE_FENGRULI_H
class Interface   //class interferface class
{
public:
	Interface();   //construction function to initializ some variable
	void interface_function();    //interface function which run in main function
	void Main_menu();  //display main menu to choose which account to be operated
	void Stock_menu();  //stock function menu
	void Bank_menu();  //bank function menu
	void scan();  //scan input choice
	void Main_choice();  //process with user's choice in main menu
	void Stock_choice();  //process with user's choice in stock menu
	void Bank_choice();  //process with user's choice in bank menu
	void menu_display();  //decide display which menu
	void menu_choice();  //decide which choice function should be accessed
	void write_history();  //write bank account history
private:
	int choice;  //user's choice
	int menu;    //menu status  0 is for main menu  1 is for stock menu 2 is for stock menu
	int quit;     //quit flag   0 is for don't quit 1 is for quit
	StockAccount stockaccount;   //stock account
	BankAccount  bankaccount;    //bank account
	
};
#endif // !INTERFACE_FENGRULI_H



