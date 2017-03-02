//node consist the double linked list and double linked list consist stock account.It's decorator design pattern

//add matlab libarary
#pragma once
#pragma comment( lib,"libmx.lib")
#pragma comment( lib,"libmex.lib")
#pragma comment( lib,"libeng.lib")

//include head file
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <map>
#include <vector>

//add head file and marco define of matlab
#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h" 
#include <engine.h>


//using namespace
using namespace std;

#ifndef ACCOUNT_FENGRULI_H
#define ACCOUNT_FENGRULI_H


class Node      //the parent class of double linked list
{
	friend class StockAccount;  //declare friend class
public:
	Node();   //constucture function to intialize variable in node
protected:
	string symbol;  // node member stock sysmbol
	double stock_number; // node member stock number
	Node *next;  //pointer point to next node
	Node *pre;   //pointer point to previous node
};

class DoubleLinkedList :public Node   //children  class of node
{
	friend class StockAccount;  //declare friend class
public:
	DoubleLinkedList();   //constructure function to intialize variable in double linked list
protected:
	Node *Head;  //double linked list head pointer
	Node *Tail;  //double linked list tail pointer
};

class Account    //parent class of bank account and stock account
{
public:
	void set_balance(double);  //set balance 
	double get_balance();    //get balance
private:
	static double balance;   //static variable balance because stock account and bank account share the same balance
};

class BankAccount :public Account   //children class of account
{
public:
	BankAccount();   //constructure function to get intialization value of balance if there is a history balance
	bool deposit_money(double money);   //deposit money  if succeed return 1  otherwise return 0
	bool withdraw_money(double money);  //withdraw money if succeed return 1  otherwise return 0
	void print_history();  //print balance history in the file
	void view_balance();   //view balance value
};

class StockAccount:public Account  // children class of account
{
public:
	StockAccount();   //constructure function to get portfolio information.
	~StockAccount();  // destructure function to write total portfolio value to history file  and close matlab engine and delete double linked list and write portfolio information to file
	map<string, double> Random_Readf();  //random read result file to get stock symbol and value return the map which store stock information
	double Display_price(string);   //display price of a stock
	bool sorted(map<string,double>);  //judge whether the double linked list is sorted  if sorted return true otherwise return false
	map<string,double> sort();  // sort the double linked list return the map which store stock information
	void Display_portfolio();  //display portfolio value
	void Buy_shares(BankAccount &);  //buy share
	void Sell_shares(BankAccount &); //sell share
	void view_history();  //view transaction history
	void view_graph();  //use matlab to plot graph
protected:
	DoubleLinkedList stock;  //stock account member double linked list to store stock information
	Engine *ep;  //matlab engine pointer
};
#endif // !ACCOUNT_FENGRULI_H

