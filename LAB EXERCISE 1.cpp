#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

struct studInfo
{
    string studentId;
    string surname;
    string firstname;
    string birthdate;
    string sex;
};

void printStudInfo(string filename, const vector<studInfo>& i1, int var);
vector<studInfo> readFromData(string filename);
void saveData(string filename, const vector<studInfo>& i1);
int main()
{
    vector <studInfo> tempvec;

    string filename;
    int opt;

    do
    {
        cout<<"[1]Create New File  [2]Open an Existing File  [3]Manage Data [4]Exit"<<endl;
        cin>>opt;

        if(opt == 1)
        {
            cout<<"Enter filename(sample.txt): ";
            cin>>filename;

            ofstream outStudInfo(filename);
        }
        else if(opt == 2)
        {
            cout<<"Enter filename(sample.txt): ";
            cin>>filename;

            tempvec = readFromData(filename);

            printStudInfo(filename, tempvec, 1);
        }
        else if(opt == 3)
        {
            cout<<"Enter filename(sample.txt): ";
            cin>>filename;

            tempvec = readFromData(filename);

            char opt2;

            do
            {
                printStudInfo(filename, tempvec, 2);
                cin>>opt2;

                if(opt2 == 'A')
                {
                    studInfo tempInfo;

                    cout << "Student ID: ";
                    cin >> tempInfo.studentId;
                    cout << "Surname: ";
                    cin >> tempInfo.surname;
                    cout << "Firstname: ";
                    cin.ignore(); // ignore the newline character left in the input buffer
                    getline(cin, tempInfo.firstname);
                    cout << "Birthdate(99/99/99): ";
                    cin >> tempInfo.birthdate;
                    cout << "Sex(M | F): ";
                    cin >> tempInfo.sex;

                    tempvec.push_back(tempInfo);
                }
                else if(opt2 == 'E')
                {
                    int opt3;
                    cout<<"Choose Edit: ";
                    cin>>opt3;

                    cout<<"Student ID: "<<tempvec[opt3-1].studentId<<": ";
                    cin>>tempvec[opt3-1].studentId;
                    cout<<"Surname: "<<tempvec[opt3-1].surname<<": ";
                    cin>>tempvec[opt3-1].surname;
                    cout<<"Firstname: "<<tempvec[opt3-1].firstname<<": ";
                    cin.ignore();
                    getline(cin,tempvec[opt3-1].firstname);
                    cout<<"Birthdate: "<<tempvec[opt3-1].birthdate<<": ";
                    cin>>tempvec[opt3-1].birthdate;
                    cout<<"Sex: "<<tempvec[opt3-1].sex<<": ";
                    cin>>tempvec[opt3-1].sex;
                }
                else if(opt2 == 'D')
                {
                    int opt4;

                    cout<<"Choose Delete: ";
                    cin>>opt4;

                    tempvec.erase(tempvec.begin() + (opt4-1));
                }
                else if(opt2 == 'S')
                {
                    int opt5, opt6;
                    studInfo tempInfo;

                    cout<<"Choose sort 1: ";
                    cin>>opt5;
                    cout<<"Choose sort 2: ";
                    cin>>opt6;

                    tempInfo = tempvec[opt5-1];
                    tempvec[opt5-1]=tempvec[opt6-1];
                    tempvec[opt6-1]=tempInfo;

                }
                else if(opt2 == 'V')
                {
                    cout<<"Changes saved!"<<endl;
                    saveData(filename, tempvec);
                }
                else
                {
                    cout<<"Option does not exist!"<<endl;
                }
                saveData(filename, tempvec);
            }while(opt2!='X');
        }
        else
        {
             cout<<"Option does not exist!"<<endl;
        }
    }while(opt!=4);
}
void printStudInfo(string filename, const vector<studInfo>& i1, int var)
{
    if(var == 1)
    {
        int ind = 1;


        cout<<"Active File: ["<<filename<<"]"<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
        cout<<setw(15)<<left<<"Rec"<<setw(15)<<left<<"Student ID"<<setw(15)<<left<<"Surname"<<setw(15)<<left<<
        "Firstname"<<setw(15)<<left<<"Birthdate"<<setw(15)<<left<<"Sex"<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
        for (const auto& entry : i1)
        {
            cout<<setw(15)<<left<<ind<<setw(15)<<left<< entry.studentId <<setw(15)<<left
                << entry.surname <<setw(15)<<left << entry.firstname <<setw(15)<<left
                << entry.birthdate <<setw(15)<<left << entry.sex << endl;
            ind++;
        }
        cout<<"--------------------------------------------------------------------------------"<<endl;
    }
    else if(var == 2)
    {
        int ind = 1;

        cout<<"Active File: ["<<filename<<"]"<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
        cout<<setw(15)<<left<<"Rec"<<setw(15)<<left<<"Student ID"<<setw(15)<<left<<"Surname"<<setw(15)<<left<<
        "Firstname"<<setw(15)<<left<<"Birthdate"<<setw(15)<<left<<"Sex"<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
        for (const auto& entry : i1)
        {
                cout<<setw(15)<<left<<ind<<setw(15)<<left<< entry.studentId <<setw(15)<<left
                << entry.surname <<setw(15)<<left << entry.firstname <<setw(15)<<left
                << entry.birthdate <<setw(15)<<left << entry.sex << endl;
            ind++;
        }
        cout<<"--------------------------------------------------------------------------------"<<endl;
        cout<<"[A]dd [E]dit [D]elete [S]ort sa[V]e e[X]it"<<endl;
    }
    else
    {
        cout<<"OPTION DOES NOT EXIST!"<<endl;
    }
}
void saveData(string filename, const vector<studInfo>& i1)
{
    ofstream outInfo;
    outInfo.open(filename, ios::out);

    for(int i = 0; i<i1.size(); i++)
    {
        outInfo<<i1[i].studentId<<"\t";
        outInfo<<i1[i].surname<<"\t";
        outInfo<<i1[i].firstname<<"\t";
        outInfo<<i1[i].birthdate<<"\t";
        outInfo<<i1[i].sex<<endl;
    }

}
vector<studInfo> readFromData(string filename)
{
    vector <studInfo> tempVec;
    ifstream inInfo;
    inInfo.open(filename);

    string line;
    while(getline(inInfo, line)) // Read the entire line
    {
        if(line.empty()) // Check if the line is empty
            continue;

        studInfo tempInfo;
        stringstream ss(line);
        getline(ss, tempInfo.studentId, '\t');
        getline(ss, tempInfo.surname, '\t');
        getline(ss, tempInfo.firstname, '\t');
        getline(ss, tempInfo.birthdate, '\t');
        getline(ss, tempInfo.sex);

        tempVec.push_back(tempInfo);
    }
    return tempVec;
}
