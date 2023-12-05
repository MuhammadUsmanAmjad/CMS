#include <bits/stdc++.h>
using namespace std;
class complaint
{
private:
    string complaint_name;
    int complaint_id;
    string complaint_type;
    string complaint_description;
    char complaint_status;

public:
    complaint()
    {
        complaint_name = "";
        complaint_id = 0;
        complaint_type = "";
        complaint_description = "";
        complaint_status = ' ';
    }
    complaint(string name, int id, string type, string description, char status)
    {
        complaint_name = name;
        complaint_id = id;
        complaint_type = type;
        complaint_description = description;
        complaint_status = status;
    }
    void add_complaint()
    {
        cout << "Enter complaint name: ";
        cin >> complaint_name;
        cout << "Enter complaint id: ";
        cin >> complaint_id;
        cout << "Enter complaint description: ";
        cin >> complaint_description;
        ofstream fout;
        fout.open("complaints.txt", ios::app);
        if (!fout.is_open())
        {
            cout << "Error in opening file..";
            return;
        }
        fout << complaint_id << "," << complaint_name << ","
             << "Null"
             << "," << complaint_description << "," << 'n' << endl;
    }
    int get_id()
    {
        return this->complaint_id;
    }
    char get_status()
    {
        return this->complaint_status;
    }
    void set_status(char ch)
    {
        this->complaint_status = ch;
    }
    void display_complaint()
    {
        cout << "Complaint name: " << complaint_name << endl;
        cout << "Complaint id: " << complaint_id << endl;
        cout << "Complaint type: " << complaint_type << endl;
        cout << "Complaint description: " << complaint_description << endl;
        cout << "Complaint status: " << complaint_status << endl;
    }
};
void loadComplaints(vector<complaint> &c, string filename)
{
    ifstream fin;
    fin.open(filename);
    if (!fin)
    {
        cout << "Error in opening the file" << endl;
        return;
    }
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string name, id, type, description;
        string status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, description, ',');
        getline(ss, status, ',');
        c.push_back(complaint(name, stoi(id), type, description, status[0]));
    }
}
class employee
{
private:
    string employee_name;
    int employee_id;

public:
    vector<complaint> complaints;
    employee()
    {
        employee_name = "";
        employee_id = 0;
    }
    employee(string name, int id)
    {
        employee_name = name;
        employee_id = id;
    }
    void display_employee()
    {
        cout << "Employee name: " << employee_name << endl;
        cout << "Employee id: " << employee_id << endl;
    }
    int get_id()
    {
        return this->employee_id;
    }
    void add_complaint(complaint &c)
    {
        complaints.push_back(c);
    }
};
class teacher
{
private:
    string teacher_name;
    int teacher_id;
    string teacher_department;
    vector<complaint> complaints;

public:
    teacher()
    {
        teacher_name = "";
        teacher_id = 0;
        teacher_department = "";
    }
    teacher(string name, int id, string department)
    {
        teacher_name = name;
        teacher_id = id;
        teacher_department = department;
    }
    void add_teacher()
    {
        cout << "Enter teacher name: ";
        cin >> teacher_name;
        cout << "Enter teacher id: ";
        cin >> teacher_id;
        cout << "Enter teacher department: ";
        cin >> teacher_department;
    }
    void display_teacher()
    {
        cout << "Teacher name: " << teacher_name << endl;
        cout << "Teacher id: " << teacher_id << endl;
        cout << "Teacher department: " << teacher_department << endl;
    }
    void add_Complaint()
    {
        complaint c;
        c.add_complaint();
        complaints.push_back(c);
    }
    void getComplaintsSolved()
    {
        vector<complaint> temp_Complaints;
        loadComplaints(temp_Complaints, "complaints.txt");
        for (int i = 0; i < complaints.size(); i++)
        {
            for (int j = 0; j < temp_Complaints.size(); j++)
            {
                if (complaints[i].get_id() == temp_Complaints[j].get_id())
                {
                    if (temp_Complaints[j].get_status() == 'c')
                        temp_Complaints[j].display_complaint();
                }
            }
        }
    }
};
class manager
{
private:
    vector<complaint> complaints;
    vector<employee> employees;
    vector<teacher> teachers;
    string name;
    int id;

public:
    manager()
    {
        name = "";
        id = 0;
    }
    manager(string name, int id)
    {
        this->name = name;
        this->id = id;
    }
    void add_employee(employee e)
    {
        employees.push_back(e);
    }
    void add_teacher()
    {
        teacher t;
        t.add_teacher();
        teachers.push_back(t);
    }
    void add_complaint(complaint &c)
    {

        complaints.push_back(c);
    }
    void display_employee()
    {
        for (int i = 0; i < employees.size(); i++)
        {
            employees[i].display_employee();
        }
    }
    void display_teacher()
    {
        for (int i = 0; i < teachers.size(); i++)
        {
            teachers[i].display_teacher();
        }
    }
    void display_complaint()
    {
        for (int i = 0; i < complaints.size(); i++)
        {
            complaints[i].display_complaint();
        }
    }
    int get_id()
    {
        return this->id;
    }
    void assignComplaint()
    {
        int iD;
        cout << "Enter the ID if the complaint to be assigned: " << endl;
        cin >> iD;
        for (int i = 0; i < complaints.size(); i++)
        {
            if (complaints[i].get_id() == iD)
            {
                if (complaints[i].get_status() == 'n')
                {
                    cout << "Enter the Employee Id to assign:" << endl;
                    cin >> iD;
                    for (int k = 0; k < employees.size(); k++)
                    {
                        if (employees[k].get_id() == iD)
                        {
                            complaints[i].set_status('a');
                            cout << "Complaint Assigned to the Employee with the ID " << iD << endl;
                            // add the employee for the
                        }
                    }

                    // have to write code to save it to file too.
                }
            }
        }
    }
    void reviewComplaints()
    {
        complaints.clear();
        loadComplaints(complaints, "complaints.txt");
        vector<complaint> pending_Complaints;
        for (int i = 0; i < complaints.size(); i++)
        {
            if (complaints[i].get_status() == 'r')
            {
                pending_Complaints.push_back(complaints[i]);
            }
        }
        cout << "Following are the Present Complaints to Review:" << endl;
        for (int i = 0; i < pending_Complaints.size(); i++)
        {
            pending_Complaints[i].display_complaint();
        }
        cout << endl
             << "Enter 1 to Update a Complaint and Status and 0 to Return to main menu" << endl;
        bool flag;
        if (!flag)
            return;
        int ID;
        cout << "Enter the id of the Complaint to Update:";
        cin >> ID;
        for (int i = 0; i < complaints.size(); i++)
        {
            if (complaints[i].get_id() == ID)
            {
                complaints[i].set_status('c');
            }
        }
    }
    void viewCompletedComplaints()
    {
        cout << "Complaints that are successfully completed:" << endl;
        for (int i = 0; i < complaints.size(); i++)
            if (complaints[i].get_status() == 'c')
                complaints[i].display_complaint();
    }
};
class admin
{
private:
    string admin_name;
    int admin_id;
    vector<employee> employees;
    vector<teacher> teachers;
    vector<manager> managers;

public:
    admin(string filename)
    {
        ifstream fin;
        fin.open(filename);
        if (!fin.is_open())
        {
            cout << "Error in opening file..";
            cout << "Created an admin with the name and id as admin and 1 respectively" << endl;
            admin_name = "admin";
            admin_id = 1;
            return;
        }
        string line;
        while (getline(fin, line))
        {
            stringstream ss(line);
            string name, id;
            getline(ss, id, ',');
            getline(ss, name, ',');
            admin_name = name;
            admin_id = stoi(id);
        }
        fin.close();
    }
    void loadUsers(string filename)
    {
        ifstream fin;
        fin.open(filename);
        if (!fin.is_open())
        {
            cout << "Error in opening file..";
            return;
        }
        string line;
        while (getline(fin, line))
        {
            stringstream ss(line);
            string type, name, id, department;
            getline(ss, type, ',');
            if (type == "e")
            {
                getline(ss, id, ',');
                getline(ss, name, ',');
                employees.push_back(employee(name, stoi(id)));
            }
            else if (type == "t")
            {
                getline(ss, id, ',');
                getline(ss, name, ',');
                getline(ss, department, ',');
                teachers.push_back(teacher(name, stoi(id), department));
            }
            else if (type == "m")
            {
                getline(ss, id, ',');
                getline(ss, name, ',');
                managers.push_back(manager(name, stoi(id)));
            }
        }
        fin.close();
    }
    void loadComplaints(string filename)
    {
        ifstream fin;
        fin.open(filename);
        if (!fin.is_open())
        {
            cout << "Error in opening file..";
            return;
        }
        string line;
        while (getline(fin, line))
        {
            stringstream ss(line);
            string name, id, type, description;
            string status;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, description, ',');
            getline(ss, status, ',');
            for (int i = 0; i < managers.size(); i++)
            {
                if (managers[i].get_id() == stoi(id))
                {
                    complaint *c = new complaint(name, stoi(id), type, description, status[0]);
                    managers[i].add_complaint(*c);
                    if (status[0] == 'a')
                    {
                        int id = atoi(status.substr(1).c_str());
                        for (int j = 0; j < employees.size(); j++)
                        {
                            if (employees[j].get_id() == id)
                            {
                                employees[j].add_complaint(*c);
                            }
                        }
                    }
                }
            }
        }
        fin.close();
    }
    void printAll()
    {
        employees.clear();
        managers.clear();
        teachers.clear();
        this->loadUsers("users.txt");
        this->loadComplaints("complaints.txt");
        cout << "Employees: " << endl;
        for (int i = 0; i < employees.size(); i++)
        {
            employees[i].display_employee();
            for (int j = 0; j < employees[i].complaints.size(); j++)
            {
                employees[i].complaints[j].display_complaint();
            }
        }
        cout << "\n\n_____________________________________\n\n";
        cout << "Teachers: " << endl;
        for (int i = 0; i < teachers.size(); i++)
        {
            teachers[i].display_teacher();
        }
        cout << "\n\n_____________________________________\n\n";
        cout << "Managers: " << endl;
        for (int i = 0; i < managers.size(); i++)
        {
            managers[i].display_complaint();
        }
    }
};

int main()
{
    admin a("admin.txt");
    a.loadUsers("users.txt");
    a.loadComplaints("complaints.txt");
    a.printAll();
    return 0;
}