#include <iostream>
using namespace std;

#define MAX 100

class Hospital
{
    public:
    struct Patient
    {
        string name;
        int priority;
    };

    Patient queue[MAX];
    int size;

    Hospital()
    {
        size =0;
    }

    void insert(string name, int priority)
    {
        if(size >=MAX)
        {
            cout<<"\nQueue is full ";
        }
        int i;
        for(i=size-1;i>=0;i--)
        {
            if(priority < queue[i].priority)
            {
                queue[i+1] = queue[i];
            }
            else
            {
                break;
            }
        }
        queue[i+1].name =name;
        queue[i+1].priority =priority;
        size++;
    }
    void serve()
    {
        if(size==0)
        {
            cout<<"\nNo patients to serve ";

        }
        cout<<"\nServing Patient is " <<queue[0].name <<endl;
        for(int i=0;i<size-1;i++)
        {
            queue[i] =queue[i+1];
        }
        size--;
    }

    void display()
    {
        if(size==0)
        {
            cout<<"\nNothing to display ";

        }
        cout<<"\nCurrent patients ";
        for(int i=0;i<size;i++)
        {
            cout<<i + 1 <<"." <<queue[i].name <<"(";

            if(queue[i].priority==1)
            {
                cout<<"\nSerious ";
            }
            else if(queue[i].priority==2)
            {
                cout<<"\nNon Serious ";
            }
            else
            {
                cout<<"\nGeneral Checkup ";
            }
            cout<<")\n";
        }
    }

};

int main() {
    Hospital hq;
    int choice;
    string name;
    int priority;

    do {
        cout << "\n---- Hospital Priority Queue System ----\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Display Patients\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter patient name: ";
                cin >> name;
                cout << "Enter patient condition (1 = Serious, 2 = Non-Serious, 3 = General Checkup): ";
                cin >> priority;
                if (priority < 1 || priority > 3) {
                    cout << "Invalid priority.\n";
                } else {
                    hq.insert(name, priority);
                }
                break;

            case 2:
                hq.serve();
                break;

            case 3:
                hq.display();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
