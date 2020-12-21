#ifndef MYFUN_H_INCLUDED
#define MYFUN_H_INCLUDED
 
#include<vector>
#include<map>
#include<fstream>

 
/*----------------成员声明-------------------*/
 
std::multimap<std::string, COMMON *> sear;
 
std::vector<TESTER*> tester;
std::vector<TEACHER*> teacher;
std::vector<ADMINISTRATOR*> administrator;
std::vector<TEAADMI*> teaadmi;
 
/*----------------函数声明-------------------*/
 
void Information_load();        //信息加载
void room_delete();             //释放空间
void login();                   //登入函数
void Add_information();         //添加信息
bool Query_information();       //显示查询信息
void Browse_information();      //浏览信息
void Edit_information();        //修改信息
void Delete_information();      //删除信息
void count_information();       //统计信息
 
/*----------------函数定义-------------------*/
 
void Information_load() //信息加载
{
    std::ifstream in;
    in.open("实验员.txt", std::ios::in);
    std::string name, id;
    int age;
    bool sex;
    while(in >> name)
    {
        std::string laboratory, title;
        in >> sex >> age >> id >> laboratory >> title;
        TESTER *t = new TESTER(name,sex,age,id,laboratory,title);
        tester.push_back(t);
        sear.insert(make_pair(name, t));
        sear.insert(make_pair(id, t));
    }
    in.close();
 
    in.open("教师.txt", std::ios::in);
    while(in >> name)
    {
        std::string department, profession, title;
        in >> sex >> age >> id >> department >> profession >> title;
        TEACHER *t = new TEACHER(name,sex,age,id,department,profession,title);
        teacher.push_back(t);
        sear.insert(make_pair(name, t));
        sear.insert(make_pair(id, t));
    }
    in.close();
 
    in.open("行政人员.txt", std::ios::in);
    while(in >> name)
    {
        std::string politics, position;
        in >> sex >> age >> id >> politics >> position;
        ADMINISTRATOR *t = new ADMINISTRATOR(name,sex,age,id,politics,position);
        administrator.push_back(t);
        sear.insert(make_pair(name, t));
        sear.insert(make_pair(id, t));
    }
    in.close();
 
    in.open("教师&行政人员.txt", std::ios::in);
    while(in >> name)
    {
        std::string department, profession, title, politics, position;
        in >> sex >> age >> id >> department >> profession >> title >> politics >> position;
        TEAADMI *t = new TEAADMI(name,sex,age,id,department,profession,title,politics,position);
        teaadmi.push_back(t);
        sear.insert(make_pair(name, t));
        sear.insert(make_pair(id, t));
    }
}
 
void room_delete() //释放空间
{
    for(auto iter:tester) delete iter;
    for(auto iter:teacher) delete iter;
    for(auto iter:administrator) delete iter;
    for(auto iter:teaadmi) delete iter;
}
 
void login() //登入函数
{
    std::string com;
    system("cls");
    std::cout << "请输入密码\n";
    getchar();
    std::getline(std::cin,com);
    if(com == "bokuwasinnsekainokamitonaru") interface_Manager();
    else
    {
        std::cout << "密码错误，输入任意键返回上一级\n";
        getch();
    }
}
 
void Add_information()//添加信息
{
    system("cls");
    std::cout << "请输入添加类型\n1：实验员\t2：教师\t\t3：行政人员\t4：教师及行政人员\n";
    int flag; std::cin >> flag;
    std::string name, se, id;
    int age;
    bool sex = 0;
    std::cout << "ID：\t\t"; std::cin >> id;
    for(unsigned int i = 0; i < id.length(); i++)
    {
        if(id[i] < '0' || id[i] > '9')
        {
            std::cout << "输入非法，输入任意键返回\n";
            getch();
            return;
        }
    }
 
    std::multimap<std::string, COMMON *>::iterator beg, en;
    beg = sear.lower_bound(id);
    en = sear.upper_bound(id);
    if(beg != en)
    {
        std::cout << "此ID已存在，输入任意键返回\n";
        getch();
        return;
    }
 
    std::cout << "姓名：\t\t"; std::cin >> name;
    for(unsigned int i = 0; i < name.length(); i++)
    {
        if(name[i] >= '0' && name[i] <= '9')
        {
            std::cout << "输入非法，输入任意键返回\n";
            getch();
            return;
        }
    }
 
    std::cout << "性别：\t\t"; std::cin >> se; if(se == "男") sex = 1;
    std::cout << "年龄：\t\t"; std::cin >> age;
    if(flag == 1)
    {
        std::string laboratory, title;
        std::cout << "实验室名称：\t"; std::cin >> laboratory;
        std::cout << "职务：\t\t"; std::cin >> title;
        TESTER *t = new TESTER(name,sex,age,id,laboratory,title);
        tester.push_back(t);
        sear.insert(make_pair(name, t));
        sear.insert(make_pair(id, t));
        std::ofstream out;
        out.open("实验员.txt", std::ios::app);
        out << name << " " << sex << " " << age << " " << id << " ";
        out << laboratory << " " << title << std::endl;
        out.close();
    }
    if(flag == 2)
    {
        std::string department, profession, title;
        std::cout << "院系：\t\t"; std::cin >> department;
        std::cout << "专业：\t\t"; std::cin >> profession;
        std::cout << "职务：\t\t"; std::cin >> title;
        TEACHER *t = new TEACHER(name,sex,age,id,department,profession,title);
        teacher.push_back(t);
        sear.insert(make_pair(name, t));
        sear.insert(make_pair(id, t));
        std::ofstream out;
        out.open("教师.txt", std::ios::app);
        out << name << " " << sex << " " << age << " " << id << " ";
        out << department << " " << profession << " " << title << std::endl;
        out.close();
    }
    if(flag == 3)
    {
        std::string politics, position;
        std::cout << "政治面貌：\t"; std::cin >> politics;
        std::cout << "职称：\t\t"; std::cin >> position;
        ADMINISTRATOR *t = new ADMINISTRATOR(name,sex,age,id,politics,position);
        administrator.push_back(t);
        sear.insert(make_pair(name, t));
        sear.insert(make_pair(id, t));
        std::ofstream out;
        out.open("行政人员.txt", std::ios::app);
        out << name << " " << sex << " " << age << " " << id << " ";
        out << politics << " " << position << std::endl;
        out.close();
    }
    if(flag == 4)
    {
        std::string department, profession, title, politics, position;
        std::cout << "院系：\t\t"; std::cin >> department;
        std::cout << "专业：\t\t"; std::cin >> profession;
        std::cout << "职务：\t\t"; std::cin >> title;
        std::cout << "政治面貌：\t"; std::cin >> politics;
        std::cout << "职称：\t\t"; std::cin >> position;
        TEAADMI *t = new TEAADMI(name,sex,age,id,department,profession,title,politics,position);
        teaadmi.push_back(t);
        sear.insert(make_pair(name, t));
        sear.insert(make_pair(id, t));
        std::ofstream out;
        out.open("教师&行政人员.txt", std::ios::app);
        out << name << " " << sex << " " << age << " " << id << " ";
        out << department << " " << profession << " " << title << " ";
        out << politics << " " << position << std::endl;
        out.close();
    }
    std::cout << "注册成功，输入任意键返回\n";
    getch();
}
 
void Delete_information() //删除信息
{
    std::cout << "输入目标ID以确认\n";
    std::string aid;
    std::cin >> aid;
 
    for(unsigned int i = 0; i < aid.length(); i++)
    {
        if(aid[i] < '0' || aid[i] > '9')
        {
            std::cout << "输入非法，输入任意键返回\n";
            getch();
            return;
        }
    }
 
    std::multimap<std::string, COMMON *>::iterator beg, en, iter;
    beg = sear.lower_bound(aid);
    en = sear.upper_bound(aid);
    if(beg == en)
    {
        std::cout << "目标不存在，输入任意键返回\n";
        getch();
        return;
    }
    std::string aid_name = beg -> second -> get_name();
    sear.erase(beg);
    beg = sear.lower_bound(aid_name);
    en = sear.upper_bound(aid_name);
    for(iter = beg; iter != en; ++iter) if(iter -> second -> get_id() == aid) {sear.erase(iter); break;}
 
    bool flag = 0;
    std::ofstream out;
    out.open("实验员.txt", std::ios::out);
    for(std::vector<TESTER*>::iterator it = tester.begin(); it != tester.end();)
    {
        if((*it) -> get_id() == aid){flag = 1; delete (*it); it = tester.erase(it); continue;}
        out << (*it) -> get_name() << " " << (*it) -> get_sex() << " ";
        out << (*it) -> get_age() << " " << (*it) -> get_id() << " ";
        out << (*it) -> get_laboratory() << " " << (*it) -> get_title() << std::endl;
        ++it;
    }
    out.close();
    if(flag) {std::cout << "删除成功,输入任意键返回\n"; getch(); return;}
    out.open("教师.txt", std::ios::out);
    for(std::vector<TEACHER*>::iterator it = teacher.begin(); it != teacher.end();)
    {
        if((*it) -> get_id() == aid){flag = 1; delete (*it); it = teacher.erase(it); continue;}
        out << (*it) -> get_name() << " " << (*it) -> get_sex() << " ";
        out << (*it) -> get_age() << " " << (*it) -> get_id() << " ";
        out << (*it) -> get_department() << " " << (*it) -> get_profession() << " " << (*it) -> get_title() << std::endl;
        it++;
    }
    out.close();
    if(flag) {std::cout << "删除成功,输入任意键返回\n"; getch(); return;}
    out.open("行政人员.txt", std::ios::out);
    for(std::vector<ADMINISTRATOR*>::iterator it = administrator.begin(); it != administrator.end();)
    {
        if((*it) -> get_id() == aid){flag = 1; delete (*it); it = administrator.erase(it); continue;}
        out << (*it) -> get_name() << " " << (*it) -> get_sex() << " ";
        out << (*it) -> get_age() << " " << (*it) -> get_id() << " ";
        out << (*it) -> get_politics() << " " << (*it) -> get_position() << std::endl;
        it++;
    }
    out.close();
    if(flag) {std::cout << "删除成功,输入任意键返回\n"; getch(); return;}
    out.open("教师&行政人员.txt", std::ios::out);
    for(std::vector<TEAADMI*>::iterator it = teaadmi.begin(); it != teaadmi.end();)
    {
        if((*it) -> get_id() == aid){flag = 1; delete (*it); it = teaadmi.erase(it); continue;}
        out << (*it) -> get_name() << " " << (*it) -> get_sex() << " ";
        out << (*it) -> get_age() << " " << (*it) -> get_id() << " ";
        out << (*it) -> get_department() << " " << (*it) -> get_profession() << " " << (*it) -> get_title() << " ";
        out << (*it) -> get_politics() << " " << (*it) -> get_position() << std::endl;
        ++it;
    }
    out.close();
    std::cout << "删除成功,输入任意键返回\n";
    getch();
}
 
void Edit_information() //修改信息
{
    std::cout << "输入目标ID以确认\n";
    std::string aid;
    std::cin >> aid;
    for(unsigned int i = 0; i < aid.length(); i++)
    {
        if(aid[i] < '0' || aid[i] > '9')
        {
            std::cout << "输入非法，输入任意键返回\n";
            getch();
            return;
        }
    }
 
    std::multimap<std::string, COMMON *>::iterator beg, en, iter;
    beg = sear.lower_bound(aid);
    en = sear.upper_bound(aid);
 
    if(beg == en)
    {
        std::cout << "目标不存在，输入任意键返回\n";
        getch();
        return;
    }
    system("cls");
    bool flag = 0;
    std::ofstream out;
    out.open("实验员.txt", std::ios::out);
    for(auto iter:tester)
    {
        if(iter -> get_id() == aid)
        {
            iter -> show(), std::cout << "\n\n根据提示输入修改信息\n\n";
            while(iter -> change())
            {
                system("cls");
                iter -> show();
                std::cout << "输入非法，请重新输入\n";
            }
            flag = 1;
        }
        out << iter -> get_name() << " " << iter -> get_sex() << " ";
        out << iter -> get_age() << " " << iter -> get_id() << " ";
        out << iter -> get_laboratory() << " " << iter -> get_title() << std::endl;
    }
    out.close();
    if(flag) {std::cout << "修改成功,输入任意键返回\n"; getch(); return;}
    out.open("教师.txt", std::ios::out);
    for(auto iter:teacher)
    {
        if(iter -> get_id() == aid)
        {
            iter -> show(), std::cout << "\n\n根据提示输入修改信息\n\n";
            while(iter -> change())
            {
                system("cls");
                iter -> show();
                std::cout << "输入非法，请重新输入\n";
            }
            flag = 1;
        }
        out << iter -> get_name() << " " << iter -> get_sex() << " ";
        out << iter -> get_age() << " " << iter -> get_id() << " ";
        out << iter -> get_department() << " " << iter -> get_profession() << " " << iter -> get_title() << std::endl;
    }
    out.close();
    if(flag) {std::cout << "修改成功,输入任意键返回\n"; getch(); return;}
    out.open("行政人员.txt", std::ios::out);
    for(auto iter:administrator)
    {
        if(iter -> get_id() == aid)
        {
            iter -> show(), std::cout << "\n\n根据提示输入修改信息\n\n";
            while(iter -> change())
            {
                system("cls");
                iter -> show();
                std::cout << "输入非法，请重新输入\n";
            }
            flag = 1;
        }
        out << iter -> get_name() << " " << iter -> get_sex() << " ";
        out << iter -> get_age() << " " << iter -> get_id() << " ";
        out << iter -> get_politics() << " " << iter -> get_position() << std::endl;
    }
    out.close();
    if(flag) {std::cout << "修改成功,输入任意键返回\n"; getch(); return;}
    out.open("教师&行政人员.txt", std::ios::out);
    for(auto iter:teaadmi)
    {
        if(iter -> get_id() == aid)
        {
            iter -> show(), std::cout << "\n\n根据提示输入修改信息\n\n";
            while(iter -> change())
            {
                system("cls");
                iter -> show();
                std::cout << "输入非法，请重新输入\n";
            }
            flag = 1;
        }
        out << iter -> get_name() << " " << iter -> get_sex() << " ";
        out << iter -> get_age() << " " << iter -> get_id() << " ";
        out << iter -> get_department() << " " << iter -> get_profession() << " " << iter -> get_title() << " ";
        out << iter -> get_politics() << " " << iter -> get_position() << std::endl;
    }
    out.close();
    std::cout << "修改成功,输入任意键返回\n";
    getch();
}
 
bool Query_information() //查询函数
{
    system("cls");
    std::cout << "输入目标姓名或ID以查询\n";
    std::string aid;
    std::cin >> aid;
    std::multimap<std::string, COMMON *>::iterator beg, en, iter;
    beg = sear.lower_bound(aid);
    en = sear.upper_bound(aid);
 
    if(beg == en)
    {
        std::cout << "查询结果为空，输入任意键返回\n";
        getch();
        return 0;
    }
    for(iter = beg; iter != en; ++iter)
    {
        iter -> second -> show();
        std::cout << std::endl;
    }
    return 1;
}
 
void Browse_information() //浏览函数
{
    system("cls");
    std::cout << "-------------------实验员-------------------\n";
    std::cout << "姓名\t" << "性别\t" << "年龄\t" << "ID\t\t" << "实验室名称\t" << "职务\n";
    for(auto iter:tester) iter -> show_row();
 
 
    std::cout << "\n------------------行政人员------------------\n";
    std::cout << "姓名\t" << "性别\t" << "年龄\t" << "ID\t\t" << "政治面貌\t" << "职称\n";
    for(auto iter:administrator) iter -> show_row();
 
 
    std::cout << "\n--------------------教师--------------------\n";
    std::cout << "姓名\t" << "性别\t" << "年龄\t" << "ID\t\t" << "院系\t\t" << "专业\t\t" << "职务\n";
    for(auto iter:teacher) iter -> show_row();
 
 
    std::cout << "\n-----------------行政人员&教师--------------\n";
    std::cout << "姓名\t" << "性别\t" << "年龄\t" << "ID\t\t" << "政治面貌\t" << "职称\t\t" << "院系\t\t" << "专业\t\t" << "职务\n";
    for(auto iter:teaadmi) iter -> show_row();
}
 
void count_information() //统计信息
{
    system("cls");
    std::cout << "员工总人数:\t\t" << COMMON::get_person_sum() << std::endl;
    std::cout << "男性人数:\t\t" << COMMON::get_man_sum() << std::endl;
    std::cout << "女性人数:\t\t" << COMMON::get_woman_sum() << std::endl;
    std::cout << "教师人数:\t\t" << TEACHER::get_teacher_sum() << std::endl;
    std::cout << "实验员人数:\t\t" << TESTER::get_tester_sum() << std::endl;
    std::cout << "行政管理人员人数:\t" << ADMINISTRATOR::get_administrator_sum() << std::endl;
    std::cout << "行政管理人员&教师人数:\t" << TEAADMI::get_teaadmi_sum() << std::endl;
    std::cout << "\n\n输入任意键返回上一级\n";
    getch();
}
 
#endif // MYFUN_H_INCLUDED