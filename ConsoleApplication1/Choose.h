#pragma once
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
using namespace std;
struct choose
{
	char student_id[10];
	char course_id[7];
	char teacher_id[5];
	char choose_year[5];
	char score[5];
};
struct chnode
{
	struct choose chdata;
	struct chnode *next;
};
struct chnode* create_choose_list()
{
	struct chnode* headnode = new chnode;
	headnode->next = NULL;
	return headnode;
}
struct chnode* createnode(struct choose chdata)
{
	struct chnode* newnode = new chnode;
	newnode->chdata = chdata;
	newnode->next = NULL;
	return newnode;
}
void chinsertnode(struct chnode* headnode, struct choose chdata)
{
	struct chnode* newnode = createnode(chdata);
	newnode->next = headnode->next;
	headnode->next = newnode;
}

void chdeletelist(struct chnode* headnode, char *student_id)
{
	struct chnode* posnode = headnode->next;
	struct chnode* posfront = headnode;
	if (posnode == NULL)
	{
		cout << "空" << endl;
		return;
	}
	while (strcmp(posnode->chdata.student_id, student_id))
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
void clear_choose_list(struct chnode *headnode)
{
	struct chnode *tp = NULL;
	struct chnode *ph = headnode->next;
	while (headnode->next)
	{
		tp = ph;
		ph = ph->next;
		delete tp;
		headnode->next = ph;
	}
}
struct chnode* chsearch(struct chnode* headnode, char *student_id)
{
	struct chnode *pmove = headnode->next;
	if (pmove == NULL)return NULL;
	while (strcmp(pmove->chdata.student_id, student_id))
	{
		pmove = pmove->next;
	}
	return pmove;
}

void chreadfile(struct chnode *headnode,const char *filename)
{
	ifstream inFile;
	struct choose chdata;
	inFile.open(filename, ios::in | ios::app);
	if (!inFile.is_open()) {
		cout << "文件不能打开" << endl;
	}
	while (EOF != inFile.peek())
	{
		inFile >> chdata.student_id >> chdata.course_id >> chdata.teacher_id >> chdata.choose_year >> chdata.score;
		chinsertnode(headnode, chdata);
	}
	inFile.close();
}


void chwritefile(struct chnode *headnode,const char *filename)
{
	ofstream out(filename);
	struct chnode *pmove = headnode->next;
	while (pmove)
	{
		out << pmove->chdata.student_id << "\t" << pmove->chdata.course_id << "\t" << pmove->chdata.teacher_id << "\t" << pmove->chdata.choose_year << "\t" << pmove->chdata.score << endl;
		pmove = pmove->next;
	}
	out.close();
}

void chprintlist(struct chnode* headnode)
{
	struct chnode* pmove = headnode->next;
	cout << "学生id\t课程id\t教师id\t选课年份\t成绩\n";
	while (pmove)
	{
		cout << pmove->chdata.student_id << "\t" << pmove->chdata.course_id << "\t" << pmove->chdata.teacher_id << "\t" << pmove->chdata.choose_year << "\t\t" << pmove->chdata.score  << endl;
		pmove = pmove->next;
	}
	cout << endl;
}