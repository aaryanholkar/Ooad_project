#ifndef shopkeeper_portal_cpp
#define shopkeeper_portal_cpp
#include<bits/stdc++.h>
using namespace std;
#include "database.cpp"
#include "shopkeeper.cpp" 
#include "shop.cpp" 

ulli number_of_items=0;

int home_page_shpkpr(Shopkeeper); 
void display_transaction_details(char* name){
    string name1(name);
    Shop_trans trans;
    string path="database/transaction_data/"+name1+".ooad";
    ifstream file(path.c_str());
    cout<<"email\t\tname\t\tquantity"<<endl;
    while(file.read((char*)&trans,sizeof(Shop_trans))){
        cout<<trans.email<<"\t\t"<<trans.name<<"\t\t"<<trans.quantity<<endl;
    }
}

int process(ulli option, Shopkeeper shopkeeper)
{
    switch (option)
    {
    case 1:
    {
        cout << "> Name : " << shopkeeper.name << endl;
        cout<<"> shop name : "<<shopkeeper.shop_name<<endl;
        cout << "> Email : " << shopkeeper.email << endl;
        cout << "> contact number : " << shopkeeper.contact_number << endl;
        cout << "> Account Number : " << shopkeeper.account_name << endl;
        cout << "> IFSC code : " << shopkeeper.IFSC_code << endl;
        cout << "> Pending amount : " << shopkeeper.pending_amount << endl;
        cout <<"> Account Number : " << shopkeeper.account_name << endl;
        
        char option1;
        cin >> option1;
        switch (option1){
        case 'a':
        {
            system("clear");
            return home_page_shpkpr(shopkeeper);
        }
        case 'b':
        {
            return -1;
        }
        }
        break;
    }
    case 2:
    {
        if(number_of_items==0)
            cout<<"> No items to display\n";
        else
            display_shop_details(shopkeeper.shop_category);
        return home_page_shpkpr(shopkeeper);      
    }
    case 3:
    {
        Shop shop;
        cout<<"> Shop_Category -> "<<shopkeeper.shop_category<<" shop"<<endl;
        shop.add_items(shopkeeper.shop_category,number_of_items+1); 

        cout<<"> item added sucessfully\n";

        number_of_items++;
        string temp_id(Utilities::ulli_to_string(shopkeeper.shop_id));
        
        string path="database/shop_data/"+temp_id+".num";
        ofstream file(path.c_str());
        file<<number_of_items;
        file.close();

        return home_page_shpkpr(shopkeeper);
        break;
    }
    case 4:
    {
        display_shop_details(shopkeeper.shop_category);
        cout << "> Enter the ID of the item whose record is to be updated : ";
        ulli num;
        cin >> num;
        Item item = get_item(shopkeeper.shop_category, num);
        string name(shopkeeper.shop_category);
        update_item_record(item, name);
        return home_page_shpkpr(shopkeeper);
    }
    case 5:
    {
        display_transaction_details(shopkeeper.shop_category);
        return home_page_shpkpr(shopkeeper);
    }
    case 6:
    {
        return -1;
    }
    default:
    {
        return -1;
    }
    }
    return -1;
}


int home_page_shpkpr(Shopkeeper shopkeeper)
{
    string id=Utilities::ulli_to_string(shopkeeper.shop_id);
    
    string path="database/shop_data/"+id+".num";
    fstream file(path.c_str());
    file>>number_of_items;
    file.close();

    cout << "> Select any of the following options (Type the corresponding index to select a option):\n";
    cout << "> 1) profile\n";
    cout << "> 2) view items in the shop\n";
    cout << "> 3) add items to shop\n";
    cout << "> 4) update item record\n";
    cout << "> 5) transaction history\n";
    cout << "> 6) Logout\n";
    cout << "\n> ";
    ulli option; //contains the input option given by the user
    cin >> option;
    system("clear");
    return process(option,shopkeeper);
}



int shopkeeper_portal(string email)
{
    Shopkeeper shopkeeper(get_number_of_shops());
    shopkeeper=get_shopkeeper(email);
    cout<<"> Enter your password :: ";
    string password=Terminal::input_password();
    
    if(password.length()==0)
        return -1;

    while(!shopkeeper.login(password))
    {
        cout<<"> invalid email password combination";
        cout<<"\n> Do you want to re-enter password? (y/n)";
        char input;
        cin>>input;
        
        if(input=='y'||input=='Y')
        {
          cout<<"> Enter your password :: ";
          password=Terminal::input_password();
    
        if(password.length()!=0)
        continue;
        }
        else 
        return -1;
    }
    cout << "\n> Welcome " << shopkeeper.name << " !\n";

    return home_page_shpkpr(shopkeeper);
}
#endif

