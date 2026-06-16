#include<iostream>
#include<string>
#include<cstring>
#include<limits>
using namespace std;

class Account
{
public:
    string  userName;
    string  accNumber;
    char pin[5];
    double balance;
    bool isValid=true;
    // below arrays and variable used for mini statement
    string Type[10];
    float amount[10];
    double balanceAfter[10];
    int count=0;

public:
    void Deposit(auto& userAccounts,  int userIndex)
    {   
        //cin.ignore();
        float depositAmount;
        cout<<"\nEnter Amount: ";
        while(!(cin>>depositAmount))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nInvaild Amount! \nPlease Enter Amount in Numbers!"<<endl;
            cout<<"Enter Again: ";
            
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        userAccounts[userIndex].balance+=depositAmount;
        cout<<"Amount Deposit Succesfully!"<<endl;


        //data collection for mini statement
        if(userAccounts[userIndex].count > 9)
        {
            for(int i=0;i<9;i++)
            {
                userAccounts[userIndex].Type[i]=userAccounts[userIndex].Type[i+1];
                userAccounts[userIndex].amount[i]=userAccounts[userIndex].amount[i+1];
                userAccounts[userIndex].balanceAfter[i]=userAccounts[userIndex].balanceAfter[i+1];
            }
            userAccounts[userIndex].count--;
        }
            
        userAccounts[userIndex].Type[userAccounts[userIndex].count]="Deposit";
        userAccounts[userIndex].amount[userAccounts[userIndex].count]=depositAmount;
        userAccounts[userIndex].balanceAfter[userAccounts[userIndex].count]=userAccounts[userIndex].balance;
        userAccounts[userIndex].count++;
                
        //cout<<userAccounts[userIndex].balance<<endl;
    }


    void Withdraw(auto& userAccounts,int userIndex)
    {
        float withdrawAmount;
        cout<<"\nEnter Amount: ";
        while(!(cin>>withdrawAmount))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nInvalid Amount! \nAmount format is only Numbers(0---9)."<<endl;
            cout<<"Enter Again: ";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        

        if(userAccounts[userIndex].balance < withdrawAmount)
        {
            cout<<"Insufficient Balance!"<<endl;
        }
        else
        {   
            userAccounts[userIndex].balance-=withdrawAmount;
            cout<<"'"<<withdrawAmount<<"' Rupees is deducted from your Account '"<<userAccounts[userIndex].accNumber<<"'"<<endl;


            // data collection for mini statement
            if(userAccounts[userIndex].count > 9)
            {
                for(int i=0;i<9;i++)
                {
                    userAccounts[userIndex].Type[i]=userAccounts[userIndex].Type[i+1];
                    userAccounts[userIndex].amount[i]=userAccounts[userIndex].amount[i+1];
                    userAccounts[userIndex].balanceAfter[i]=userAccounts[userIndex].balanceAfter[i+1];
                }    
                userAccounts[userIndex].count--;
            }
            
            userAccounts[userIndex].Type[userAccounts[userIndex].count]="withdraw";
            userAccounts[userIndex].amount[userAccounts[userIndex].count]=withdrawAmount;
            userAccounts[userIndex].balanceAfter[userAccounts[userIndex].count]=userAccounts[userIndex].balance;
            userAccounts[userIndex].count++;    
        }    

    }


    void showMiniStatement(auto& userAccounts,int userIndex)
    {   
        int lenght=userAccounts[userIndex].count; 

        cout<<"\n______Mini Statement_______\n"<<endl;

        if(userAccounts[userIndex].count<1)
        {
            cout<<"> NO Statement Available!"<<endl;
        }
        else
        {  
            for(int i=0;i<lenght;i++)
            {
                cout<<i+1<<". "<<userAccounts[userIndex].Type[i]<<"  "<<userAccounts[userIndex].amount[i]<<"     | "<<"Balance: "<<userAccounts[userIndex].balanceAfter[i]<<endl;
            }
        }

        cout<<"\n> Last "<<lenght<<" Transactions"<<endl;
        cout<<"-------------------------------------------"<<endl;
    }



    void displayBalance(auto& userAccounts, int userIndex)
    {
        cout<<"Current Balance: "<<userAccounts[userIndex].balance<<endl;
    }

};


class ATM:public Account 
{
public:
    int userCount=0;
    int capacity=2;
    Account* userAccounts=new Account[capacity];
public:
    void createAccount (auto& userAccounts, int &capacity, int& userCount)
    {
        
        //cin.ignore();
        if(capacity == userCount)
        {
            int newSize=capacity*2;
            Account* newUserAccounts= new Account[newSize];
            
            for(int i=0;i<capacity;i++)
            {
                newUserAccounts[i]=userAccounts[i];
            }

            delete[] userAccounts;
            userAccounts=newUserAccounts;
            capacity=newSize;
        }
            //userCount++;
            //cin.ignore();

            cout<<"ADD User Account Name: ";
            getline(cin,userAccounts[userCount].userName);
            isNameValid(userAccounts[userCount].userName);

            cout<<"ADD Account Number: ";
            getline(cin,userAccounts[userCount].accNumber);
            isAccountFound(userAccounts,userCount);

            cout<<"Create Pin (in digits): ";
            cin>>userAccounts[userCount].pin;
            isPinValid(userAccounts,userCount);

            cin.ignore();

            cout<<"Add Initial Amount: ";
            cin>>userAccounts[userCount].balance;
        

            cin.ignore();

            userCount++;
            cout<<"Account Created!"<<endl;
    }



    void userMenu(auto& userAccounts,  int userIndex)
    {
        
        cout<<"\n____User Menu____"<<endl;
        
        
        bool isContinue=true;

        while(true)
        {
            int userChoice;
            cout<<"\n1.Deposit \n2.Withdraw \n3.Current Balance \n4.Mini Statement \n5.Main Menu \n\nEnter Choice :";

            while(!(cin>>userChoice))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
                cout<<"\nInvalid Choice!"<<endl;
                cout<<"Please! Select from Option(1---5)"<<endl;;
            
                //cin>>userChoice;
                //cin.ignore();
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
            switch (userChoice)
            {
            case 1:
                //Deposit
                Deposit(userAccounts,userIndex);
                break;
            case 2:
                //Withdraw
                Withdraw(userAccounts,userIndex);
                break;
            case 3:
                //check balance
                displayBalance(userAccounts,userIndex);
                break;
            case 4:
                //mini statement
                showMiniStatement(userAccounts,userIndex);
                break;
            case 5:
                //Main menu
                isContinue=false;
                break;
            default:
                cout<<"Invalid Choice!"<<endl;
                //cin.ignore();
                break;
            }

            if(!isContinue)
                break;
        }
        

    }


    void Login(auto& userAccounts,int usercount)
    {
        if(usercount<1)
        {
            cout<<"No Account Found!"<<endl;
        }
        else
        {
            string LoginAccNum;
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout<<"Enter Account Number: ";
            getline(cin,LoginAccNum);

            bool isAccValid=false;
            int LoginAccIndex;
            bool isAccRun=true;

            for(int i=0;i<usercount;i++)
            {
                if(userAccounts[i].accNumber==LoginAccNum)
                {
                    if(userAccounts[i].isValid)
                    {
                        isAccValid=true;
                        LoginAccIndex=i;
                        break;
                    }
                    else
                    {
                        isAccRun=false;
                        break;    
                    }
                }
            }

            bool isAccBlock=false;
            int tryCount=4;
            char enteredPin[5];

            if(!isAccRun)
            {
                cout<<"Account Blocked!"<<endl;
            }
            else
            {
                if(isAccValid)
                { 
                    while(tryCount>0)
                    {
                        cout<<"Enter Login Pin: ";
                        cin>>enteredPin;
                    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if(strcmp( enteredPin,userAccounts[LoginAccIndex].pin)==0)
                        {
                            cout<<"\nAccount Login Successfully!"<<endl;
                            userMenu(userAccounts, LoginAccIndex);
                            isAccBlock=false;
                            break;
                        }
                        else
                        {   
                            tryCount--;
                            cout<<"Wrong PIn! You have  only ("<<tryCount<<") try left."<<endl;
                            isAccBlock=true;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        }
                    }    
                }
                else
                {
                    cout<<"Account Not Found!"<<endl;
                }
                
                if(isAccBlock)
                {
                    cout<<"Your Account has been blocked!"<<endl;
                    userAccounts[LoginAccIndex].isValid=false;
                } 

            }
        }
    }



    void isPinValid(auto& userAccounts,int index)
    {

        if(strlen(userAccounts[index].pin)!=4)
        {   
            cin.clear();
            cout<<"\npin lenght should have 4_digits"<<endl;
            cout<<"Enter Again: ";
            cin>>userAccounts[index].pin;
            isPinValid(userAccounts,index);
        }
        else
        {
        
            bool isValid=false;
        
            for(int i=0;i<4;i++)
        
            {
                if(!(isdigit(userAccounts[index].pin[i]) && userAccounts[index].pin[i] !=' '))
                {
                    isValid=true;
                    break;
                }

            }

            if (isValid) 
            {   
                cout<<"\nPIN must contain digits only!\n";
                cout<<"Enter Again: ";
                cin>>userAccounts[index].pin;
                isPinValid(userAccounts,index);
            }
        }

        
    bool isAvalaible=true;
    for(int i=0;i<index;i++)
    {
            
        if(strcmp(userAccounts[index].pin,userAccounts[i].pin)==0)
        {    
            isAvalaible=false;
            cout<<"\nPin is not Available!"<<endl;
            cout<<"Enter Again: ";
            cin>>userAccounts[index].pin;
            break;
        }
        else
        {
            isAvalaible=true;
        }
            
        
    }

    if(!isAvalaible)
    {
        isPinValid(userAccounts,index);
    }

    }



    void isAccountFound(auto& userAccounts, int userCount)
    {
        
        while(true)
        {
            bool isValid=true;
            for(int i=0;i<userCount;i++)
            {
                if(userAccounts[i].accNumber==userAccounts[userCount].accNumber)
                {   
                    isValid=false;
                    cout<<"\nAccount Number is not Available."<<endl;
                    cout<<"Enter Again: ";
                    getline(cin,userAccounts[userCount].accNumber);
                    break;
                }
            }

            if(isValid)
            {
                break;
            }   
        }
        
    }


    void isNameValid(string name)
    {
        while(true)
        {
            bool isAllow=true;
            for(char c: name)
            {
                if(!isalpha(c))
                {
                    isAllow=false;
                    cout<<"\nName shouuld be in Alphabets: "<<endl;
                    cout<<"Enter Again: ";
                    getline(cin,name);
                    break;
                }
            }
            
            if(isAllow)
                break;

        }
        
    }



    void mainMenu()
    {  
        //int userCount=0;
        bool flag=false;

        //int capacity=2;
        //Account* userAccounts=new Account[capacity];
        
        cout<<"Welcome to  ATM Management System"<<endl;

        while(true)
        {

            char choice;
            cout<<"\n____Main_Menu____\n\n1. Login Account \n2. Create Account \n3. Exit"<<endl;
            cin>>choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //cin.ignore();

            switch(choice)
            {
                case '1':
                //login
                    Login(userAccounts, userCount);
                    break;
                case '2':
                    //create account
                    createAccount(userAccounts,capacity, userCount);
                    break;
                case '3':
                //exit
                    flag=true;
                    break;
                default:
                    cout<<"Invalid Input!"<<endl;
                    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
            }

        if(flag)
        {
            break;
        }
        }

        cout<<"END";
        //return 0;
    }
};

int main() 
{
    ATM atm;
    atm.mainMenu();
    return 0;
}
