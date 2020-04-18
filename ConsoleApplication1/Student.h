#pragma once
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<mysql.h>
using namespace std;


struct student
{
	char id[10];
	char name[20];
	char sex[10];
	char intoschool_age[10];
	char intoschool_year[10];
	char cls[5];
};
struct node
{
	struct student data;
	struct node *next;
};
struct node* createstudentlist()
{
	struct node* headnode = (struct node*)malloc(sizeof(struct node));
	headnode->next = NULL;
	return headnode;
}
struct node* createnode(struct student data)
{
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}
void insertnode(struct node* headnode, struct student data)
{
	struct node* newnode = createnode(data);
	newnode->next = headnode->next;
	headnode->next = newnode;
}

void deletelist(struct node* headnode,char *id)
{
	struct node* posnode = headnode->next;
	struct node* posfront = headnode;
	if (posnode == NULL)
	{
		cout << "��" << endl;
		return;
	}
	while (strcmp(posnode->data.id,id))
	{
		posfront = posnode;
		posnode = posfront->next;
		if (posnode == NULL)
		{
			cout << "δ�ҵ�" << endl;
			return;
		}
	}
	posfront->next = posnode->next;
	free(posnode);
}
void clearstudentlist(struct node *headnode)
{
	struct node *tp = NULL;
	struct node *ph = headnode->next;
	while (headnode->next)
	{
		tp = ph;
		ph = ph->next;
		delete tp;
		headnode->next = ph;
	}
}
struct node* search(struct node* headnode, char *id)
{
	struct node* pmove = headnode->next;
	if (pmove == NULL)return NULL;
	while (strcmp(pmove->data.id,id))
	{
		pmove = pmove->next;
	}
	return pmove;
}

void readfile(struct node *headnode, const char *filename)
{
	ifstream inFile;
	struct student data;
	inFile.open(filename, ios::in |ios::app);
	if (!inFile.is_open()) {
		cout << "�ļ����ܴ�" << endl;
	}
	//cout << "1" << endl;
	//!inFile.eof()
	while (EOF!=inFile.peek())
	{
		//cout << "2" << endl;
		inFile >> data.id >> data.name >> data.sex >> data.intoschool_age >> data.intoschool_year >> data.cls;
		insertnode(headnode, data);
		//cout << "3" << endl;
	}
	inFile.close();
}


void writefile(struct node *headnode, const char *filename)
{
	ofstream out(filename);
	struct node *pmove = headnode->next;
	while (pmove)
	{
		out << pmove->data.id<<"\t" << pmove->data.name << "\t" << pmove->data.sex << "\t" << pmove->data.intoschool_age << "\t" << pmove->data.intoschool_year << "\t" << pmove->data.cls << endl;
		pmove = pmove->next;
	}
	out.close();
}

void printlist(struct node* headnode)
{
	struct node* pmove = headnode->next;
	cout << "ѧ��֤\t����\t�Ա�\t��ѧ����\t��ѧ���\t�༶\n";
	while (pmove)
	{
		cout << pmove->data.id << "\t" << pmove->data.name << "\t" << pmove->data.sex << "\t    " << pmove->data.intoschool_age << "\t\t" << pmove->data.intoschool_year << "\t\t" << pmove->data.cls << endl;
		pmove = pmove->next;
	}
	cout << endl;
}