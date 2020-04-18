#pragma once
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<mysql.h>
using namespace std;
struct teacher {
	char id[5];
	char name[20];
	char class_teach[20];
};
struct tnode {
	struct teacher tdata;
	struct tnode *next;
};
struct tnode *create_teacher_list()
{
	 struct tnode* headnode = new tnode;
	 headnode->next = NULL;
	 return headnode;
}
struct tnode* create_teacher_node(struct teacher tdata)
{
	struct tnode* newtnode = new tnode;
	newtnode->tdata = tdata;
	newtnode->next = NULL;
	return newtnode;
}
void tinsertnode(struct tnode* headnode, struct teacher tdata)
{
	struct tnode* newtnode = create_teacher_node(tdata);
	newtnode->next = headnode->next;
	headnode->next = newtnode;
}
void tdeletelist(struct tnode* headnode, char *id)
{
	struct tnode* posnode = headnode->next;
	struct tnode* posfront = headnode;
	if (posnode == NULL)
	{
		cout << "空" << endl;
		return;
	}
	while (strcmp(posnode->tdata.id, id))
	{
		posfront = posnode;
		posnode = posfront->next;
		if (posnode == NULL)
		{
			cout << "未找到" << endl;
			return;
		}
	}
	posfront->next = posnode->next;
	free(posnode);
}
void clear_teacher_list(struct tnode *headnode)
{
	struct tnode *tp = NULL;
	struct tnode *ph = headnode->next;
	while (headnode->next)
	{
		tp = ph;
		ph = ph->next;
		delete tp;
		headnode->next = ph;
	}
}
struct tnode* tsearch(struct tnode* headnode, char *id)
{
	struct tnode* pmove = headnode->next;
	if (pmove == NULL)return NULL;
	while (strcmp(pmove->tdata.id, id))
	{
		pmove = pmove->next;
	}
	return pmove;
}

void tprintlist(struct tnode* headnode)
{
	struct tnode* pmove = headnode->next;
	cout << "教师id\t教师姓名\t可教课程\n";
	while (pmove)
	{
		cout << pmove->tdata.id << "\t" << pmove->tdata.name << "\t\t  " << pmove->tdata.class_teach << endl;
		pmove = pmove->next;
	}
	cout << endl;
}

void treadfile(struct tnode *headnode,const char *filename)
{
	ifstream inFile;
	struct teacher tdata;
	inFile.open(filename, ios::in | ios::app);
	if (!inFile.is_open()) {
		cout << "文件不能打开" << endl;
	}
	while (EOF != inFile.peek())
	{
		inFile >> tdata.id>>tdata.name>>tdata.class_teach;
		tinsertnode(headnode, tdata);
	}
	inFile.close();
}


void twritefile(struct tnode *headnode, const char *filename)
{
	ofstream out(filename);
	struct tnode *pmove = headnode->next;
	while (pmove)
	{
		out << pmove->tdata.id << "\t" << pmove->tdata.name << "\t" << pmove->tdata.class_teach << endl;
		pmove = pmove->next;
	}
	out.close();
}