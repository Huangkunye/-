
#include "pch.h"
#include <iostream>
#include<string>
#include<stdio.h>
#include<Windows.h>
#include<mysql.h>
#include<stdlib.h>
#include"mysql.h"
#include"Student.h"
#include"Teacher.h"
#include"Course.h"
#include"Choose.h"
using namespace std;
MYSQL mysql;
MYSQL_RES* res;
MYSQL_ROW row;
void student_menu()
{
	cout << "............学生个人信息..............." << endl;
	cout << "\t0.录入信息" << endl;
	cout << "\t1.浏览信息" << endl;
	cout << "\t2.删除信息" << endl;
	cout << "\t3.查找信息" << endl;
	cout << "\t4.修改信息" << endl;
	cout << "\t5.退出" << endl;
	cout<< "..........................." << endl;
}
void teacher_menu()
{
	cout << "............教师个人信息..............." << endl;
	cout << "\t0.录入信息" << endl;
	cout << "\t1.删除信息" << endl;
	cout << "\t2.修改信息" << endl;
	cout << "\t3.查找信息" << endl;
	cout << "\t4.浏览信息" << endl;
	cout << "\t5.查询成绩" << endl;
	cout << "\t6.退出" << endl;
	cout << "..........................." << endl;
}
void course_menu()
{
	cout << "............课程信息................" << endl;
	cout << "\t0.录入信息" << endl;
	cout << "\t1.删除信息" << endl;
	cout << "\t2.修改信息" << endl;
	cout << "\t3.查找信息" << endl;
	cout << "\t4.浏览信息" << endl;
	cout << "\t5.退出" << endl;
	cout << "......................................" << endl;
}
void choose_menu()
{
	cout << "............选课信息................" << endl;
	cout << "\t0.录入信息" << endl;
	cout << "\t1.删除信息" << endl;
	cout << "\t2.修改信息" << endl;
	cout << "\t3.查找信息" << endl;
	cout << "\t4.浏览信息" << endl;
	cout << "\t5.退出" << endl;
	cout << "......................................" << endl;
}
struct node *list = createstudentlist();
struct tnode *tlist = create_teacher_list();
struct cnode *clist = create_course_list();
struct chnode *chlist = create_choose_list();

void checkgrade()
{
	int j;
	cout << "............成绩查询..........." << endl;
	cout << "\t0:查询单个学生成绩" << endl;
	cout << "\t1:查询学生的平均成绩" << endl;
	cout << "\t2:查询同个班级的学生平均成绩" << endl;
	cout << "\t3:查询同个课程学生的平均成绩" << endl;
	cout << "\t4:退出" << endl;
	cout << "请输入操作:" << endl;
	cin >> j;
	switch (j)
	{
	case 0:
	{
		string student_id;
		cout << "请输入要查询的学生id：" << endl;
		cin >> student_id;
		string chastudent = "select course_id,score from choose where student_id = '"+student_id+"'";
		mysql_query(&mysql, chastudent.c_str());
		res = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(res))
		{
			cout << "课程id：" << row[0] << "\t成绩" << row[1] << endl;
		}
		mysql_free_result(res);
		break;
	}
	case 1:
	{
		string cha = "select score from choose";
		mysql_query(&mysql, cha.c_str());
		res = mysql_store_result(&mysql);
		float avg = 0;
		int i = 0;
		while (row = mysql_fetch_row(res))
		{
			avg += atoi(row[0]);
			i++;
		}
		cout << avg / i << endl;
		mysql_free_result(res);
		break;
	}
	case 2:
	{
		string cla;
		cout << "请输入你要查询的班级" << endl;
		cin >> cla;
		string cls = "select score from choose where student_id in(SELECT id FROM student WHERE class = '"+cla+"')";
		mysql_query(&mysql, cls.c_str());
		res = mysql_store_result(&mysql);
		float cla_avg = 0;
		int i = 0;
		while (row = mysql_fetch_row(res))
		{
			cla_avg += atoi(row[0]);
			i++;
		}
		cout << cla_avg/i << endl;
		mysql_free_result(res);
		break;
	}
	case 3:
	{
		string course;
		cout << "请输入你要查询的课程id:" << endl;
		cin >> course;
		string cls = "select score from choose where course_id ='"+course+"'";
		mysql_query(&mysql, cls.c_str());
		res = mysql_store_result(&mysql);
		float course_avg = 0;
		int i = 0;
		while (row = mysql_fetch_row(res))
		{
			course_avg += atoi(row[0]);
			i++;
		}
		cout << course_avg / i << endl;
		mysql_free_result(res);
		break;
	}
	case 4:
		exit(0);
		break;
	default:
		cout << "输入错误，请重新输入" << endl;
		break;
	}
}

void student_keydown()
{
	int choice = 0;
	struct student data;
	cin >> choice;
	switch (choice)
	{
	case 0:
	{
		cout << "......录入信息........" << endl;
		cout << "输入学生证，姓名，性别，入学年龄，入学年份，班级" << endl;
		fflush(stdin);//清除缓冲区
		cin >> data.id >> data.name >> data.sex >> data.intoschool_age >> data.intoschool_year >> data.cls;
		/*if (data.intoschool_age < 10 || data.intoschool_age>50)
		{
			cout << "入学年龄在10-50岁之间，请重新输入" << endl;
			int newintoschool_age;
			cin >> newintoschool_age;
			data.intoschool_age = newintoschool_age;
		}*/
		insertnode(list, data);
		writefile(list, "student.txt");

		string sqltext;
		string sql_id = data.id;
		string sql_name = data.name;
		string sql_sex = data.sex;
		string sql_intoschool_age = data.intoschool_age;
		string sql_intoschool_year = data.intoschool_year;
		string sql_cls = data.cls;
		sqltext = "insert into student(id,sname,sex,intoschool_age,intoschool_year,class) values('" + sql_id + "','" + sql_name + "','" + sql_sex + "','"+sql_intoschool_age+"','"+sql_intoschool_year+"','"+sql_cls+"');";//主键相同，避免重复
		mysql_query(&mysql, sqltext.c_str());//将上面语句转为mysql语句
		cout << "录入成功" << endl;
		break;
	}
	case 1:
	{
		cout << "......浏览信息........" << endl;
		printlist(list);
		/*mysql_query(&mysql, "select * from student");
		res = mysql_store_result(&mysql);
		cout << "学生id\t姓名\t性别\t入学年龄\t入学年份\t班级\n";
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << "\t" << row[5] << endl;
		}
		mysql_free_result(res);*/
		break;
	}
	case 2:
	{
		cout << "......删除信息........" << endl;
		cout << "输入删除的学生id：";
		cin >> data.id;
		deletelist(list, data.id);
		writefile(list, "student.txt");
		string sql_id = data.id;
		string sql_de = "delete from student where id = '" + sql_id + "'";
		mysql_query(&mysql, sql_de.c_str());
		cout << "删除成功" << endl;
		break;
	}
	case 3:
	{
		cout << "......查找信息........" << endl;
		cout << "输入要找的学生id:";
		cin >> data.id;
		if (search(list, data.id) == NULL) {
			cout << "没有相关信息,显示全部学生信息" << endl;
			printlist(list);
		}
		else {
			cout << "学生id\t姓名\t性别\t入学年龄\t入学年份\t班级\n";
			cout << search(list, data.id)->data.id << "\t" << search(list, data.id)->data.name << "\t" << search(list, data.id)->data.sex << "\t    " << search(list, data.id)->data.intoschool_age << "\t\t" << search(list, data.id)->data.intoschool_year << "\t\t" << search(list, data.id)->data.cls << endl;
		}//数据库操作
		/*string sql_id = data.id;
		string sql_serach = "select * from student where id ='" + sql_id+ "'";
		mysql_query(&mysql, sql_serach.c_str());
		res = mysql_store_result(&mysql);
		cout << "学生id\t姓名\t性别\t入学年龄\t入学年份\t班级\n";
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << "\t" << row[5] << endl;
		}
		mysql_free_result(res);*/
		break;
	}
	case 4:
	{
		cout << "......修改信息........" << endl;
		cout << "输入修改的学生id：";
		cin >> data.id;
		deletelist(list, data.id);

		string sql_id = data.id;
		string sql_de = "delete from student where id = '" + sql_id + "'";
		mysql_query(&mysql, sql_de.c_str());

		cout << "请重新输入学生证,姓名，性别，入学年龄，入学年份，班级:" << endl;
		fflush(stdin);/*清空缓冲区*/
		cin >> data.id >> data.name >> data.sex >> data.intoschool_age >> data.intoschool_year >> data.cls;
		insertnode(list, data);
		string sql_newid = data.id;
		string sql_name = data.name;
		string sql_sex = data.sex;
		string sql_intoschool_age = data.intoschool_age;
		string sql_intoschool_year = data.intoschool_year;
		string sql_cls = data.cls;
		string sqltext = "insert into student(id,sname,sex,intoschool_age,intoschool_year,class) values('" + sql_newid + "','" + sql_name + "','" + sql_sex + "','" + sql_intoschool_age + "','" + sql_intoschool_year + "','" + sql_cls + "');";//主键相同，避免重复
		mysql_query(&mysql, sqltext.c_str());
		writefile(list, "student.txt");
		cout << "修改成功" << endl;
		break;
	}
	case 5:
		cout << "退出" << endl;
		exit(0);
		break;
	default:
		cout << "选择错误，重新输入" << endl;
		break;
	}
	clearstudentlist(list);
}
void teacher_keydown()
{
	int tchoice;
	struct teacher tdata;
	cin >> tchoice;
	switch (tchoice)
	{
	case 0:
	{
		cout << ".........录入信息........" << endl;
		cout << "输入教师id，姓名，可教课程" << endl;
		fflush(stdin);//清除缓冲区
		cin >> tdata.id >> tdata.name >> tdata.class_teach;
		tinsertnode(tlist, tdata);
		
		string sql_tid = tdata.id;
		string sql_tname = tdata.name;
		string sql_tclass = tdata.class_teach;
		string sql_ttext = "insert into teacher(id,tname,class_teach)values('" + sql_tid + "','" + sql_tname + "','" + sql_tclass + "');";
		mysql_query(&mysql, sql_ttext.c_str());
		twritefile(tlist, "teacher.txt");
		cout << "录入成功" << endl;
		break;
	}
	case 1:
	{
		cout << "........删除信息.........." << endl;
		cout << "输入删除的教师id：";
		cin >> tdata.id;
		tdeletelist(tlist, tdata.id);
		twritefile(tlist, "teacher.txt");

		string sql_tid = tdata.id;
		string sql_tde = "delete from teacher where id = '" + sql_tid + "'";
		mysql_query(&mysql, sql_tde.c_str());
		cout << "删除成功" << endl;
		break;
	}
	case 2:
	{
		cout << ".........修改信息..........." << endl;
		cout << "输入修改的教师id：";
		cin >> tdata.id;
		tdeletelist(tlist, tdata.id);
		string sql_id = tdata.id;
		string sql_de = "delete from teacher where id = '" + sql_id + "'";
		mysql_query(&mysql, sql_de.c_str());
		
		cout << "请重新输入教师身份证，姓名，可教的课程:" << endl;
		fflush(stdin);/*清空缓冲区*/
		cin >> tdata.id >> tdata.name >> tdata.class_teach;
		tinsertnode(tlist, tdata);
		

        string sqltid = tdata.id;
		string sqltname = tdata.name;
		string sqltclass = tdata.class_teach;
		string sqlttext = "insert into teacher(id,tname,class_teach) values('" + sqltid + "','" + sqltname + "','" + sqltclass + "');";//主键相同，避免重复
		mysql_query(&mysql, sqlttext.c_str());
		twritefile(tlist, "teacher.txt");
		cout << "修改成功" << endl;
		break;
	}
	case 3:
		cout << "..........查找信息............" << endl;
		cout << "输入查找的教师id：";
		cin >> tdata.id;
		if (tsearch(tlist, tdata.id) == NULL) {
			cout << "没有相关信息" << endl;
			system("pause");
		}
		else {
			cout << "教师id\t姓名\t可教课程\n";
			cout << tsearch(tlist, tdata.id)->tdata.id << "\t" << tsearch(tlist, tdata.id)->tdata.name << "\t" << tsearch(tlist, tdata.id)->tdata.class_teach << endl;
		}
		/*string sql_id = tdata.id;
		string sql_serach = "select * from teacher where id ='" + sql_id+ "'";
		mysql_query(&mysql, sql_serach.c_str());
		res = mysql_store_result(&mysql);
		cout << "教师id\t姓名\t可教课程\n";
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << endl;
		}
		mysql_free_result(res);*/
		break;
	case 4:
		cout << "..........浏览信息..........." << endl;
		tprintlist(tlist);
		/*mysql_query(&mysql, "select * from teacher");
		res = mysql_store_result(&mysql);
		cout << "教师id\t姓名\t可教课程\n";
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << "\t" << row[1] << "\t" << row[2] <<  endl;
		}
		mysql_free_result(res);*/
		break;
	case 5:
		checkgrade();
		break;
	case 6:
		cout << "............退出............" << endl;
		exit(0);
		break;
	default:
		cout << "选择错误，重新输入" << endl;
		break;
	}
	clear_teacher_list(tlist);
}
void course_keydown()
{
	int cchoice=0;
	struct course cdata;
	cin >> cchoice;
	switch (cchoice)
	{
	case 0:
	{
		cout << ".........录入信息..........." << endl;
		cout << "输入课程id，课程名称，教师id，学分，可选年级，取消年份" << endl;
		fflush(stdin);
		cin >> cdata.id >> cdata.name >> cdata.teacher_id >> cdata.score >> cdata.grade >> cdata.year_quit;
		cinsertnode(clist, cdata);
		cwritefile(clist, "course.txt");

		
		string sql_id = cdata.id;
		string sql_name = cdata.name;
		string sql_tid = cdata.teacher_id;
		string sql_score = cdata.score;
		string sql_grade = cdata.grade;
		string sql_quit = cdata.year_quit;
		string sqlctext = "insert into course(id,cname,teacher_id,score,grade,year_quit) values('" + sql_id + "','" + sql_name + "','" + sql_tid + "','" + sql_score + "','" + sql_grade + "','" + sql_quit + "');";//主键相同，避免重复
		mysql_query(&mysql, sqlctext.c_str());//将上面语句转为mysql语句
		cout << "录入成功" << endl;
		break;
	}
	case 1:
	{
		cout << ".........删除信息..........." << endl;
		cout << "输入要删除的课程id";
		cin >> cdata.id;
		cdeletelist(clist, cdata.id);
		cwritefile(clist, "course.txt");
		string sql_id = cdata.id;
		string sql_de = "delete from course where id = '" + sql_id + "'";
		mysql_query(&mysql, sql_de.c_str());
		cout << "删除成功" << endl;
		break;
	}
	case 2:
	{
		cout << ".........修改信息..........." << endl;
		cout << "输入要修改的课程id" << endl;
		cin >> cdata.id;
		cdeletelist(clist, cdata.id);

		string sql_id = cdata.id;
		string sql_de = "delete from course where id = '" + sql_id + "'";
		mysql_query(&mysql, sql_de.c_str());

		cout << "请重新输入课程id，名称，教师id，学分，年级,取消年份" << endl;
		fflush(stdin);
		cin >> cdata.id >> cdata.name >> cdata.teacher_id >> cdata.score >> cdata.grade >> cdata.year_quit;
		cinsertnode(clist, cdata);
		cwritefile(clist, "course.txt");

		string sqltext;
		string sqlid = cdata.id;
		string sql_name = cdata.name;
		string sql_tid = cdata.teacher_id;
		string sql_score = cdata.score;
		string sql_grade = cdata.grade;
		string sql_quit = cdata.year_quit;
		sqltext = "insert into course(id,cname,teacher_id,score,grade,year_quit) values('" + sqlid + "','" + sql_name + "','" + sql_tid + "','" + sql_score + "','" + sql_grade + "','" + sql_quit + "');";//主键相同，避免重复
		mysql_query(&mysql, sqltext.c_str());//将上面语句转为mysql语句
		cout << "修改成功" << endl;
		break;
	}
	case 3:
		cout<<".........查找信息..........." << endl;
		cout << "输入要查找的课程id" << endl;
		cin >> cdata.id;
		if (csearch(clist, cdata.id) == NULL)
		{
			cout << "没有相关信息" << endl;
			system("pause");
		}
		else
		{
			cout<<"课程id\t课程名称\t教师id\t学分\t年级\t取消年份\n";
			cout << csearch(clist, cdata.id)->cdata.id << "\t" << csearch(clist, cdata.id)->cdata.name << "\t\t" << csearch(clist, cdata.id)->cdata.teacher_id << "\t" << csearch(clist, cdata.id)->cdata.score << "\t" << csearch(clist, cdata.id)->cdata.grade << "\t" << csearch(clist, cdata.id)->cdata.year_quit << endl;
		}
		/*string sql_id = data.id;
		string sql_serach = "select * from course where id ='" + sql_id+ "'";
		mysql_query(&mysql, sql_serach.c_str());
		res = mysql_store_result(&mysql);
		cout<<"课程id\t课程名称\t教师id\t学分\t年级\t取消年份\n";
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << "\t" << row[5] << endl;
		}
		mysql_free_result(res);*/
		break;
	case 4:
		cout<<".........浏览信息..........." << endl; 
		cprintlist(clist);
		/*mysql_query(&mysql, "select * from course");
		res = mysql_store_result(&mysql);
		cout<<"课程id\t课程名称\t教师id\t学分\t年级\t取消年份\n";
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << "\t" << row[5] << endl;
		}
		mysql_free_result(res);*/
		break;
	case 5:
		cout<<".........退出..........." << endl; 
		exit(0);
		break;
	default:
		cout << "输入错误，请重新输入" << endl;
		break;
	}
	clear_course_list(clist);
}
void choose_keydown()
{
	int ch = 0;
	struct choose chdata;
	cin >> ch;
	switch (ch)
	{
	case 0:
	{
		cout << ".........录入信息..........." << endl;
		cout << "输入学生id，课程id，教师id，所选年份，成绩" << endl;
		fflush(stdin);
		cin >> chdata.student_id >> chdata.course_id >> chdata.teacher_id >> chdata.choose_year >> chdata.score;
		
		string sql_cid = chdata.course_id;
		string chaxun = "select year_quit from course where id = '"+sql_cid+"'";
		mysql_query(&mysql, chaxun.c_str());
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);
		if (atoi(chdata.choose_year) < atoi(row[0]))
		{
			chinsertnode(chlist, chdata);
			chwritefile(chlist, "choose.txt");

			string sql_sid = chdata.student_id;
			string sql_tid = chdata.teacher_id;
			string sql_year = chdata.choose_year;
			string sql_score = chdata.score;
			string sqlchtext = "insert into choose(student_id,course_id,teacher_id,choose_year,score) values('" + sql_sid + "','" + sql_cid + "','" + sql_tid + "','" + sql_year + "','" + sql_score + "');";//主键相同，避免重复
			mysql_query(&mysql, sqlchtext.c_str());//将上面语句转为mysql语句
			cout << "录入成功" << endl;
		}
		else
		{
			cout << "学生选课年份晚于课程取消年份，选课失败" << endl;
		}
		break;
	}
	case 1:
	{
		cout << ".........删除信息..........." << endl;
		cout << "输入要删除选课的学生id: " << endl;
		cin >> chdata.student_id;
		chdeletelist(chlist, chdata.student_id);
		chwritefile(chlist, "choose.txt");
		string sql_id = chdata.student_id;
		string sql_de = "delete from choose where student_id = '" + sql_id + "'";
		mysql_query(&mysql, sql_de.c_str());
		cout << "删除成功" << endl;
		break;
	}
	case 2:
	{
		cout << ".........修改信息..........." << endl;
		cout << "输入要修改的选课信息的学生id: " << endl;
		cin >> chdata.student_id;
		chdeletelist(chlist, chdata.student_id);
		

		string sql_id = chdata.student_id;
		string sql_de = "delete from choose where student_id = '" + sql_id + "'";
		mysql_query(&mysql, sql_de.c_str());
		
		cout << "请重新输入学生id,课程id，教师id，选课年份，成绩:" << endl;
		fflush(stdin);/*清空缓冲区*/
		cin >> chdata.student_id >> chdata.course_id >> chdata.teacher_id >> chdata.choose_year >> chdata.score;
		chinsertnode(chlist, chdata);
		chwritefile(chlist, "choose.txt");

		string sql_sid = chdata.student_id;
		string sql_cid = chdata.course_id;
		string sql_tid = chdata.teacher_id;
		string sql_year = chdata.choose_year;
		string sql_score = chdata.score;
		string sqlchtext = "insert into choose(student_id,course_id,teacher_id,choose_year,score) values('" + sql_sid + "','" + sql_cid + "','" + sql_tid + "','" + sql_year + "','" + sql_score + "');";//主键相同，避免重复
		mysql_query(&mysql, sqlchtext.c_str());//将上面语句转为mysql语句
		cout << "修改成功" << endl;
		break;
	}
	case 3:
	{
		cout << ".........查找信息..........." << endl;
		cout << "输入要查找的选课信息的学生id: " << endl;
		cin >> chdata.student_id;
		if (chsearch(chlist, chdata.student_id) == NULL)
		{
			cout << "没有相关信息" << endl;
			system("pause");
		}
		else
		{
			cout << "学生id\t课程id\t教师id\t选课年份\t分数\n";
			cout << chsearch(chlist, chdata.student_id)->chdata.student_id << "\t" << chsearch(chlist, chdata.student_id)->chdata.course_id << "\t\t" << chsearch(chlist, chdata.student_id)->chdata.teacher_id << "\t" << chsearch(chlist, chdata.student_id)->chdata.choose_year << "\t\t" << chsearch(chlist, chdata.student_id)->chdata.score << endl;
		}
		/*string sql_id = chdata.student_id;
		string sql_serach = "select * from choose where student_id ='" + sql_id+ "'";
		mysql_query(&mysql, sql_serach.c_str());
		res = mysql_store_result(&mysql);
		cout << "学生id\t课程id\t教师id\t选课年份\t分数\n";
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4]  << endl;
		}
		mysql_free_result(res);*/
		break;
	}
	case 4:
		cout << ".........浏览信息..........." << endl;
		chprintlist(chlist);
		/*string sql_serach = "select * from choose ";
		mysql_query(&mysql, sql_serach.c_str());
		res = mysql_store_result(&mysql);
		cout << "学生id\t课程id\t教师id\t选课年份\t分数\n";
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl;
		}
		mysql_free_result(res); */
		break;
	case 5:
		cout << ".........退出..........." << endl;
		exit(0);
		break;
	default:
		cout << "输入错误，请重新输入" << endl;
		break;
	}
	clear_choose_list(chlist);
}

int main()
{
	int n;
	int m;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "localhost", "root", "kunye123", "test", 3306, NULL, 0) == NULL)
		cout << "数据库连接失败，数据保存在txt文件中" << endl;
	else cout << "数据库连接成功" << endl;
	while (true)
	{
		cout << "..........学生教务系统............." << endl;
		cout << "\t0:教师" << endl;
		cout << "\t1:学生" << endl;
		cout << "\t2:管理员" << endl;
		cout << "\t3:退出" << endl;
		cout << "请输入你的身份：" << endl;
		cin >> m;
		switch (m)
		{
		case 0:
			readfile(list, "student.txt");
			student_menu();
			student_keydown();
			break;
		case 1:
			readfile(list, "student.txt");
			struct student data;
			cout << "请输入要查找的学生id：" << endl;
			cin >> data.id;
			if (search(list, data.id) == NULL) {
				cout << "没有相关信息" << endl;
				system("pause");
			}
			else {
				cout << "学生id\t姓名\t性别\t入学年龄\t入学年份\t班级\n";
				cout << search(list, data.id)->data.id << "\t" << search(list, data.id)->data.name << "\t" << search(list, data.id)->data.sex << "\t    " << search(list, data.id)->data.intoschool_age << "\t\t" << search(list, data.id)->data.intoschool_year << "\t\t" << search(list, data.id)->data.cls << endl;
			}
			clearstudentlist(list);
			break;
		case 2:
			cout << "\t0:学生操作" << endl;
			cout << "\t1:教师操作" << endl;
			cout << "\t2:课程信息" << endl;
			cout << "\t3:选课信息" << endl;
			cout << "\t4:查询成绩" << endl;
			cout << "\t5:退出" << endl;
			cout << "输入操作: ";
			cin >> n;
			switch (n)
			{
			case 0:
				readfile(list, "student.txt");
				student_menu();
				student_keydown();
				break;
			case 1:
				treadfile(tlist, "teacher.txt");
				teacher_menu();
				teacher_keydown();
				break;
			case 2:
				creadfile(clist, "course.txt");
				course_menu();
				course_keydown();
				break;
			case 3:
				chreadfile(chlist, "choose.txt");
				choose_menu();
				choose_keydown();
				break;
			case 4:
				checkgrade();
				break;
			case 5:
				cout << "退出" << endl;
				exit(0);
				break;
			default:
				cout << "输入错误，请重新输入" << endl;
				break;
			}
			break;
		case 3:
			cout << "退出" << endl;
			mysql_close(&mysql);
			exit(0);
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	
}

