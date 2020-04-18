#pragma once
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
struct course {
	char id[7];
	char name[10];
	char teacher_id[5];
	char score[5];
	char grade[10];
	char year_quit[10];
};
struct cnode {
	struct course cdata;
	struct cnode *next;
};
struct cnode *create_course_list()
{
	struct cnode *headnode = new cnode;
	headnode->next = NULL;
	return headnode;
}
struct cnode *create_course_node(struct course cdata)
{
	struct cnode *newcnode = new cnode;
	newcnode->cdata = cdata;
	newcnode->next = NULL;
	return newcnode;
}
void cinsertnode(struct cnode *headnode, struct course cdata)
{
	struct cnode *newcnode = create_course_node(cdata);
	newcnode->next = headnode->next;
	headnode->next = newcnode;
}
void cdeletelist(struct cnode *headnode, char *id)
{
	struct cnode *posnode = headnode->next;
	struct cnode *posfront = headnode;
	if (posnode == NULL)
	{
		cout << "空" << endl;
		return;
	}
	while (strcmp(posnode->cdata.id, id))
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
void clear_course_list(struct cnode *headnode)
{
	struct cnode *tp = NULL;
	struct cnode *ph = headnode->next;
	while (headnode->next)
	{
		tp = ph;
		ph = ph->next;
		delete tp;
		headnode->next = ph;
	}
}
struct cnode *csearch(struct cnode *headnode, char *id)
{
	struct cnode* pmove = headnode->next;
	if (pmove == NULL)return NULL;
	while (strcmp(pmove->cdata.id,id))
	{
		pmove = pmove->next;
	}
	return pmove;
}

void cprintlist(struct cnode *headnode)
{
	struct cnode* pmove = headnode->next;
	cout << "课程id\t课程名称\t教师id\t学分\t年级\t取消年份\n";
	while (pmove)
	{
		cout << pmove->cdata.id << "\t" << pmove->cdata.name << "\t\t" << pmove->cdata.teacher_id << "\t" << pmove->cdata.score << "\t" << pmove->cdata.grade<<"\t"<<pmove->cdata.year_quit << endl;
		pmove = pmove->next;
	}
	cout << endl;
}
void creadfile(struct cnode *headnode,const char *filename)
{
	ifstream infile;
	struct course cdata;
	infile.open(filename, ios::in | ios::app);
	if (!infile.is_open())
	{
		cout << "不能打开文件" << endl;
	}
	while (EOF != infile.peek())
	{
		infile >> cdata.id >> cdata.name >> cdata.teacher_id >> cdata.score >> cdata.grade>>cdata.year_quit;
		cinsertnode(headnode, cdata);
	}
	infile.close();
}
void cwritefile(struct cnode *headnode, const char *filename)
{
	ofstream out(filename);
	struct cnode *pmove = headnode->next;
	while (pmove)
	{
		out << pmove->cdata.id << "\t" << pmove->cdata.name << "\t" << pmove->cdata.teacher_id << "\t" << pmove->cdata.score << "\t" << pmove->cdata.grade <<"\t"<< pmove->cdata.year_quit << endl;
		pmove = pmove->next;
	}
	out.close();
}