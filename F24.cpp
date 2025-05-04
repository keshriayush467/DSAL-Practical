#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class EMP_CLASS {
    struct EMPLOYEE {
        char name[10];
        int emp_id;
        int salary;
    } Records;

    struct INDEX {
        int emp_id;
        int position;
    } Ind_Records;

public:
    EMP_CLASS() {
        strcpy(Records.name, "");
        Records.emp_id = 0;
        Records.salary = 0;
    }

    void Create();
    void Display();
    void Update();
    void Delete();
    void Append();
    void Search();
};

void EMP_CLASS::Create() {
    int i = 0;
    char ch = 'y';
    fstream seqfile("EMP.DAT", ios::out | ios::binary);
    fstream indexfile("IND.DAT", ios::out | ios::binary);

    do {
        cout << "\nEnter Name : ";
        cin >> Records.name;
        cout << "Enter Emp_ID: ";
        cin >> Records.emp_id;
        cout << "Enter Salary: ";
        cin >> Records.salary;

        seqfile.write((char*)&Records, sizeof(Records));

        Ind_Records.emp_id = Records.emp_id;
        Ind_Records.position = i;

        indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));
        i++;

        cout << "Add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    seqfile.close();
    indexfile.close();
    cout << "Records created.\n";
}

void EMP_CLASS::Display() 
{
    fstream seqfile("EMP.DAT", ios::in | ios::binary);
    fstream indexfile("IND.DAT", ios::in | ios::binary);

    cout << "\n--- Employee Records ---\n";

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records))) 
    {
        int offset = Ind_Records.position * sizeof(Records);
        seqfile.seekg(offset, ios::beg);
        seqfile.read((char*)&Records, sizeof(Records));

        if (Records.emp_id != -1) {
            cout << "Name: " << Records.name << "\n";
            cout << "Emp_ID: " << Records.emp_id << "\n";
            cout << "Salary: " << Records.salary << "\n";
            cout << "---------------------------\n";
        }
    }

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Update() {
    int id, pos = -1;
    char new_name[10];
    int new_salary;

    cout << "\nEnter Emp_ID to update: ";
    cin >> id;

    fstream seqfile("EMP.DAT", ios::in | ios::out | ios::binary);
    fstream indexfile("IND.DAT", ios::in | ios::out | ios::binary);

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records))) {
        if (id == Ind_Records.emp_id) {
            pos = Ind_Records.position;
            break;
        }
    }

    if (pos == -1) {
        cout << "Record not found.\n";
        return;
    }

    cout << "Enter new Name (max 9 chars): ";
    cin >> new_name;
    cout << "Enter new Salary: ";
    cin >> new_salary;

    int offset = pos * sizeof(Records);
    seqfile.seekp(offset, ios::beg);

    strcpy(Records.name, new_name);
    Records.emp_id = id;
    Records.salary = new_salary;

    seqfile.write((char*)&Records, sizeof(Records));

    cout << "Record updated.\n";

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Delete() {
    int id, pos = -1;

    cout << "\nEnter Emp_ID to delete: ";
    cin >> id;

    fstream seqfile("EMP.DAT", ios::in | ios::out | ios::binary);
    fstream indexfile("IND.DAT", ios::in | ios::out | ios::binary);

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records))) {
        if (id == Ind_Records.emp_id) {
            pos = Ind_Records.position;
            break;
        }
    }

    if (pos == -1) {
        cout << "Record not found.\n";
        return;
    }

    int offset = pos * sizeof(Records);
    seqfile.seekp(offset, ios::beg);

    strcpy(Records.name, "");
    Records.emp_id = -1;
    Records.salary = -1;

    seqfile.write((char*)&Records, sizeof(Records));

    offset = pos * sizeof(Ind_Records);
    indexfile.seekp(offset, ios::beg);
    Ind_Records.emp_id = -1;
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));

    cout << "Record deleted (logically).\n";

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Append() {
    int pos;
    fstream indexfile("IND.DAT", ios::in | ios::binary);


    indexfile.seekg(0, ios::end);
    pos = indexfile.tellg() / sizeof(Ind_Records);
    indexfile.close();

    indexfile.open("IND.DAT", ios::app | ios::binary);
    fstream seqfile("EMP.DAT", ios::app | ios::binary);

    cout << "\nEnter Name (max 9 chars): ";
    cin >> Records.name;
    cout << "Enter Emp_ID: ";
    cin >> Records.emp_id;
    cout << "Enter Salary: ";
    cin >> Records.salary;

    seqfile.write((char*)&Records, sizeof(Records));
    Ind_Records.emp_id = Records.emp_id;
    Ind_Records.position = pos;
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));

    cout << "Record appended.\n";

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Search() {
    int id, pos = -1;

    cout << "\nEnter Emp_ID to search: ";
    cin >> id;

    fstream indexfile("IND.DAT", ios::in | ios::binary);

    if (!indexfile) {
        cout << "Error opening index file.\n";
        return;
    }

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records))) {
        if (id == Ind_Records.emp_id) {
            pos = Ind_Records.position;
            break;
        }
    }

    indexfile.close();

    if (pos == -1) {
        cout << "Record not found.\n";
        return;
    }

    fstream seqfile("EMP.DAT", ios::in | ios::binary);
    int offset = pos * sizeof(Records);
    seqfile.seekg(offset, ios::beg);
    seqfile.read((char*)&Records, sizeof(Records));

    if (Records.emp_id == -1) {
        cout << "Record was deleted.\n";
    } else {
        cout << "Name: " << Records.name << "\n";
        cout << "Emp_ID: " << Records.emp_id << "\n";
        cout << "Salary: " << Records.salary << "\n";
    }

    seqfile.close();
}

int main() {
    EMP_CLASS emp;
    int choice;

    do {
        cout << "\n--- Employee Management ---\n";
        cout << "1. Create\n2. Display\n3. Update\n4. Delete\n5. Append\n6. Search\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: emp.Create(); break;
            case 2: emp.Display(); break;
            case 3: emp.Update(); break;
            case 4: emp.Delete(); break;
            case 5: emp.Append(); break;
            case 6: emp.Search(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
