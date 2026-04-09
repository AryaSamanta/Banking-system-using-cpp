#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

int st_int(string s){
    int h=1;
    for(int i=0;i<s.size()-1;i++){              //string to integer conversion
        h=h*10;
    }
    int s1=0;
    for(int i=0;i<s.size();i++){
        char ch=s[i];
        s1=s1+h*(ch - '0');
        h=h/10;
    }
    return s1;
}

string int_st(int num){                         //integer to string function conversion
    stringstream ss;
    ss << num;

    string s = ss.str();
    return s;
}



void createaccount(){
    string username,name,password,amount;
    cout<<"Enter name(1word): ";
    cin>>name;
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;
    cout<<"Enter amount: ";
    cin>>amount;
    ofstream file("bank.csv", ios::app);
    if(!file) {
        cout << "Error opening file!";
        return;
    }
    file << name << "," << username << "," << password << "," << amount << endl;
    cout<<"Account created successfully\n";
    file.close();
}
void admin(string password){
    const string  ps ="aryabanking";
    if(password==ps){
        string line;
        ifstream file("bank.csv");
        while(getline(file, line)){
            cout<<line<<"\n";
        }
    }
}
void userlogin(){
    string inputUser, inputPass;

    cout << "Enter username: ";
    cin >> inputUser;

    cout << "Enter password: ";
    cin >> inputPass;

    ifstream file("bank.csv");
    ofstream temp("temp.csv");
    string line;
    bool found = false;

    while(getline(file, line)) {


        stringstream ss(line);
        string name, username, password, amount;

        // Split CSV
        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, amount, ',');

        // Check match
        if(username == inputUser && password == inputPass) {
            cout << "Login successful!\n";
            int opt;
            cout<<"1 : deposit\n2 : withdraw\n3: checkbalance\n4:go back\n";
            cin>>opt;
            if(opt == 1){
                int depamt,newamt;
                cout<<"Enter amount to deposit: ";
                cin>>depamt;
                amount=int_st(st_int(amount)+depamt);
                 cout<<"Successfully deposit the amount\n";
            }else if(opt==2){
                int withdrawamount;
                cout<<"Enter the withdraw amount";
                cin>>withdrawamount;
                if(withdrawamount<=st_int(amount)){
                    amount=int_st(st_int(amount)-withdrawamount);
                    cout<<"Successfully withdrawn\n";
                }
                else if(withdrawamount>st_int(amount)){
                    cout<<"Withdraw not possible , INSUFFICIENT BALANCE\n";
                }
            }else if(opt==3){
                cout<<"NAME : "<<name<<"\n";
                cout<<"USERNAME :"<<username<<"\n";
                cout<<"AMOUNT: "<<amount<<"\n";
            }else if(opt==4){
                break;
            }
            found = true;
        }
        temp << name << "," << username << "," << password << "," << amount << endl;

    }
    if(!found) {
        cout << "Invalid username or password!\n";
    }
    file.close();
    temp.close();
    remove("bank.csv");
    rename("temp.csv", "bank.csv");

}
int main(){
    while(1){
        int j;
        cout<<"1 : create account\n2: bank user login\n3: admin login\n4: exit\n";
        cin>>j;
        if(j==4){
            break;
        }
        else if(j==1){
            createaccount();
        }
        else if(j==2){
            userlogin();
        }
        else if(j==3){
            string aps;
            cout<<"Enter admin password";
            cin>>aps;
            admin(aps);
        }
        else{
            cout<<"Invalid option\n";
        }
    }
}
