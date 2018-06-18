//---------------------------------------------SUPER MARKET MANAGEMENT SYSTEM-----------------------------------------
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include <windows.h>
#include<process.h>	
using namespace std;
int flag=0;
class product
{
int product_number;
char product_name[50];
float product_price,product_quantity,tax,product_discount;
public:
void create_product()
{
	cout<<"\n\n\t\t\t\t------------------:PRODUCT DETAILS:---------------------";
	cout<<"\n\nEnter The Product Number: ";
	cin>>product_number;
	cout<<"\nEnter The Product Name: ";
	cin.ignore();
	cin.getline(product_name,50,'\n');
	cout<<"\nEnter The Product Price: ";
	cin>>product_price;
	cout<<"\nEnter The Discount (%): ";
	cin>>product_discount;
}   
void show_product()
{		
	cout<<"\n\t\t\t\t\t\tProduct Number: #"<<product_number;
	cout<<"\n\t\t\t\t\t\tProduct Name: "<<product_name;
	cout<<"\n\t\t\t\t\t\tProduct Price: "<<product_price;
	cout<<"\n\t\t\t\t\t\tDiscount: "<<product_discount;
}
int getProduct()
{
	return product_number;
}

float getPrice()
{
	return product_price;
}

char* getName()
{
	return product_name;
}

float getDiscount()
{
	return product_discount;
}
}; 
//---------------------------FUNCTION TO DISPLAY TOPBAR---------------------------------
void topbar()
{
int i,j;
for(i=0;i<30;i++)
cout<<"&~*~";
for(j=0;j<30;j++)
cout<<"&~*~";
cout<<"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* PARADISE SUPER MART *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~";
cout<<"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*   DR.RADHAKRISHNAN SALAI   ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~";
cout<<"*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!   GOPALPURAM CHENNAI-600086   !*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!";
cout<<"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*   TEL NUMBER:044-4095184   ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~";
cout<<"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* !!HAVE A GOOD DAY!! ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*";
for(i=0;i<30;i++)
cout<<"&~*~";
for(j=0;j<30;j++)
cout<<"&~*~";
} 
fstream fp;
product produc; 
//------------------------------------------------FUNCTION TO CREATE PRODUCT---------------------------------------------------------------------
void save_product()
{
fp.open("database.dat",ios::out|ios::app);
produc.create_product();
fp.write((char*)&produc,sizeof(product));
fp.close();
cout<<endl<<endl<<"\n\t\t\t\t\tPRODUCT SUCCESSFULLY CREATED!!";
}
//---------------------------------------------FUNCTION TO SHOW THE DETAILS OF THE PARTICULAR PRODUCT---------------------------------------------  
void display_record(int num)
{
bool found=false;
fp.open("database.dat",ios::in);
while(fp.read((char*)&produc,sizeof(product)))
{
	if(produc.getProduct()==num)
	{
		system("cls");
		topbar();
		cout<<"\n\n\n";
		produc.show_product();
		found=true;
	}
}
fp.close();
if(found == false)
{
cout<<"\n\n\n\t\t\t\t\t\t  NO RECORD FOUND!!!";
}
}
//-----------------------------------------FUNCTION TO EDIT PRODUCT DETAILS------------------------------------------------------ 
void edit_product()
{
int num;
bool found=false;
system("cls");
topbar();
cout<<endl<<endl<<"Enter The Product Whose Details has to Be Modified: ";
cin>>num;	
fp.open("database.dat",ios::in|ios::out);
while(fp.read((char*)&produc,sizeof(product)) && found==false)
{
	if(produc.getProduct()==num)
	{
		produc.show_product();
		produc.create_product();
		int pos=-1*sizeof(produc);
		fp.seekp(pos,ios::cur);
		fp.write((char*)&produc,sizeof(product));
		cout<<endl<<endl<<"\t\t\t\t\tRECORD SUCCESSFULLY MODIFIED!!";
		found=true;
	}
}
fp.close();
if(found==false)
{
cout<<"\n\n\n\t\t\t\t\t\t  NO RECORD FOUND!!!";
}
}
//------------------------------------------------------------FUNCTION TO DELETE PRODUCT DETAILS-------------------------------------------------- 
void delete_product()
{
int num;
system("cls");
topbar();
cout<<endl<<endl<<"Enter the Product Number Which Is To Be Deleted: ";
cin>>num;
fp.open("database.dat",ios::in|ios::out);
fstream fp2;
fp2.open("Temp.dat",ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&produc,sizeof(product)))
{
	if(produc.getProduct()!=num)
	{
		fp2.write((char*)&produc,sizeof(product));
	}
}
fp2.close();
fp.close();
remove("database.dat");
rename("Temp.dat","database.dat");
cout<<endl<<endl<<"\t\t\t\t\tRECORD SUCCESSFULLY DELETED!!";
}
//---------------------------------------FUNCTION TO DISPLAY ALL PRODUCTS--------------------------------------- 
void product_menu()
{
system("cls");
topbar();
fp.open("database.dat",ios::in);
cout<<"\n\n\t\t\t\t---------------------:PRODUCT MENU:---------------------\n";
for(int i=0;i<120;i++)
cout<<"-";
cout<<"  P.NO\t\t\t\t\t\t    NAME\t\t\t\t\t\t\tPRICE\n";
for(int j=0;j<120;j++)
cout<<"-";
while(fp.read((char*)&produc,sizeof(product)))
{
	cout<<"  "<<produc.getProduct()<<"\t\t\t\t\t\t    "<<produc.getName()<<"      \t\t\t\t\t\t\t"<<produc.getPrice()<<endl;
}
fp.close();
}
//---------------------------------------FUNCTION TO PLACE ORDER-------------------------------------------  
void place_order()
{
int order_arr[150],quan[150],c=0;
float amt,damt,total=0;
char ch='Y';
cout<<"\n\n\t\t\t\t---------------------:PLACE ORDER:---------------------\n";
do
{
	cout<<"\n\n\t\t\t\tEnter the Product Number: ";
	cin>>order_arr[c];
	cout<<"\n\t\t\t\tEnter the Quantity to Order: ";
	cin>>quan[c];
	c++;
	cout<<"\n\t\t\t\tDo You Want To Order Another Product?(Y/N): ";
	cin>>ch;
}while(ch=='y'||ch=='Y');
system("cls");
topbar();
cout<<"\n\n\t\t\t--------------------------------INVOICE-----------------------------------\n\n";
for(int k=0;k<120;k++)
cout<<"*";
cout<<"\nPr No.\t\t Pr Name     \tQuantity    \t\tPrice \t\t\tAmount \t\t Discounted Amount \n";
for(int l=0;l<120;l++)
cout<<"*";
for(int x=0;x<=c;x++)
{
	fp.open("database.dat",ios::in);
	fp.read((char*)&produc,sizeof(product));
	while(!fp.eof())
	{	
		if(produc.getProduct()==order_arr[x])
		{
			amt=produc.getPrice()*quan[x];
			damt=amt-(amt*produc.getDiscount()/100);
			cout<<"\n"<<order_arr[x]<<"\t\t "<<produc.getName()<<"     \t"<<quan[x]<<"   \t\t\t"<<produc.getPrice()<<"/- \t\t\t"<<amt<<"/- \t\t "<<damt<<"/-";
			total+=damt;
		}
		fp.read((char*)&produc,sizeof(product));
	}
	fp.close();
}
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t===============================";
cout<<"\n\t\t\t\t\t\t\t\t\t\t\tTOTAL = "<<total;
cout<<"\n\t\t\t\t\t\t\t\t\t\t\t===============================";
}

//-------------------------------------------------FUNCTION FOR PASSWORD-----------------------------------------
int password()
{
	char a[20],b[20];
    int i,j,flag=0;
    for(i=0;i<20;i++)
    {
        a[i]=getch();
        if(a[i]==13)
            break;
        else
            cout<<"*";
    }
    cout<<"\n";
     for(j=0;j<i;j++)
        strcpy(b,a); 
		b[j]='\0';
		//cout<<b;
		cout<<"\n";   
    if(strcmp(b,"admin")==0)
    {
    	flag=1;
	}
	return(flag);
}
//----------------------------------------------------ADMIN MENU------------------------------------------------ 
void admin_menu()
{
system("cls");
int option;
char ch;
first:
topbar();
cout<<"\n\n\t\t\t\t---------------------:WELCOME!!:---------------------\n";
cout<<"\n\t\t\t\t\tWHICH OPERATION DO YOU WANT TO PERFORM??";
cout<<"\n\t\t\t\t\t1.CREATE PRODUCT";
cout<<"\n\t\t\t\t\t2.DISPLAY THE LIST OF ALL PRODUCTS";
cout<<"\n\t\t\t\t\t3.DISPLAY THE DETAILS OF A PARTICULAR PRODUCT";
cout<<"\n\t\t\t\t\t4.MODIFY PRODUCT DETAILS";
cout<<"\n\t\t\t\t\t5.DELETE PRODUCT";
cout<<"\n\t\t\t\t\t6.PLACE AN ORDER";
cout<<"\n\t\t\t\t\t7.RETURN TO MAIN MENU";
cout<<"\n\t\t\t\t\t8.EXIT";
cout<<"\n\t\t\t\t\tPLEASE ENTER YOUR CHOICE: ";
cin>>option;	
switch(option)
{
	case 1: system("cls");
	        topbar();
			save_product();
			ss:                                                 //label
			cout<<"\n\nDO YOU WANT TO CREATE MORE PRODUCT(S)(Y/N): ";
		    cin>>ch;
		    if(ch=='Y'||ch=='y')
		    {
		     system("cls");
	         topbar();
	         save_product();
	         goto ss;
		    }
		    else if(ch=='N'||ch=='n')
		    {
		     system("cls");
		     goto first;
		    }  
		    else
		    {
		     cout<<"\n\t\t\t\t\t\t     INVALID CHOICE!!";
		     cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		     cin>>ch;
		    if(ch=='Y'||ch=='y')
		     {
		        system("cls");
		        goto first;
		     }
		    else
		    {
		     system("cls");
		     cout<<"\n\n\n\n\n\n\n\n\n\n\n";
			 cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		     exit(0);
		    }
		    }
			break;
		
	case 2: system("cls");
		    topbar();
		    product_menu();
		    cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		    cin>>ch;
		    if(ch=='Y'||ch=='y')
		    {
		     system("cls");
		     goto first;
		    }
		    else if(ch=='N'||ch=='n')
		    {
		     system("cls");
		     goto first;
		    }  
		    else
		    {
		      cout<<"\n\t\t\t\t\t\t     INVALID CHOICE!!";
		      cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		      cin>>ch;
		      if(ch=='Y'||ch=='y')
		      {
		        system("cls");
		        goto first;
		      }
		      else
		      {
		        system("cls");
		        cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        exit(0);
		      }
		    }
			break;
			
	case 3: system("cls");
		    topbar();
		    rr:
		    cout<<"\n\n\nEnter the product number whose details you want to display: ";
		    int number;
		    cin>>number;
		    system("cls");
		    topbar();
			display_record(number); 
			cout<<"\n\nDO YOU WANT TO DISPLAY THE DETAILS OF MORE PRODUCT(S)(Y/N): ";
		    cin>>ch;
		    if(ch=='Y'||ch=='y')
			{
				system("cls");
		        topbar();
		        goto rr;
		    }
		    else if(ch=='N'||ch=='n')
			{
				system("cls");
				goto first;
		    } 
		    else
		    {
		        cout<<"\n\t\t\t\t\t\t     INVALID CHOICE!!";
		        cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        cin>>ch;
		        if(ch=='Y'||ch=='y')
		        {
		            system("cls");
		        	goto first;
		        }
		        else
		        {
		        	system("cls");
		        	cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				    cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	exit(0);
		        }
		    }
			break;
			
	case 4: system("cls");
		    topbar();
		    mm:
	        edit_product();
	        cout<<"\n\nDO YOU WANT TO MODIFY MORE PRODUCT(S)(Y/N): ";
		    cin>>ch;
		    if(ch=='Y'||ch=='y')
			{
				system("cls");
                topbar();	
		        goto mm;
		    }
		    else if(ch=='N'||ch=='n')
			{
				system("cls");
				goto first;
		    } 
		    else
		    {
		        cout<<"\n\t\t\t\t\t\t     INVALID CHOICE!!";
		        cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        cin>>ch;
		        if(ch=='Y'||ch=='y')
		        {
		            system("cls");
		        	goto first;
		        }
		        else
		        {
		        	system("cls");
		        	cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				    cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	exit(0);
		        }
		    }
         	break;
	
	case 5: system("cls");
		    topbar();
		    nn:
	        delete_product();
	        cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		    cin>>ch;
		    if(ch=='Y'||ch=='y')
			{
				system("cls");
		        topbar();
		        goto nn;
		    }
		    else if(ch=='N'||ch=='n')
			{
				system("cls");
				goto first;
		    } 
		    else
		    {
		        cout<<"\n\t\t\t\t\t\t     INVALID CHOICE!!";
		        cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        cin>>ch;
		        if(ch=='Y'||ch=='y')
		        {
		            system("cls");
		        	goto first;
		        }
		        else
		        {
		        	system("cls");
		        	cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				    cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	exit(0);
		        }
		    }
	        break;
			
	case 6: system("cls");
			topbar();
			oo:
			place_order(); 
			cout<<"\n\nDO YOU WANT TO ORDER MORE PRODUCT(S)(Y/N): ";
		    cin>>ch;
		    if(ch=='Y'||ch=='y')
			{
				system("cls");
				topbar();
		        goto oo;
		    }
		    else if(ch=='N'||ch=='n')
			{
				system("cls");
				goto first;
		    } 
		    else
		    {
		        cout<<"\n\t\t\t\t\t\t     INVALID CHOICE!!";
		        cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        cin>>ch;
		        if(ch=='Y'||ch=='y')
		        {
		            system("cls");
		        	goto first;
		        }
		        else
		        {
		        	system("cls");
		        	cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				    cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	exit(0);
		        }
		    }
			break;
	case 7:flag=1;
	       system("cls");
	       topbar();
	       break;
	case 8:system("cls");
	       cout<<"\n\n\n\n\n\n\n\n\n\n\n";
		   cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
	       exit(0);
		   break;	   		
	
	default:cout<<"\n\n\t\t\t\t\t\t     INCORRECT OPTION!!";
		    cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		    cin>>ch;
    	    if(ch=='Y'||ch=='y')
		    {
	    	    system("cls");
	    	    topbar();
		        goto first;
		    }
		    else if(ch=='N'||ch=='n')
		    {
			    system("cls");
				cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        exit(0);
		    }
			else
		    {
		        system("cls");
		        cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        exit(0);
		    }
}
}
//--------------------------------------------MAIN FUNCTION------------------------------------------------
int main()
{
system("cls");
int option;
topbar();
start:
cout<<"\n\n\t\t\t\t---------------------:WELCOME!!:---------------------\n";
cout<<"\n\t\t\t\t\t    WHOM DO YOU WANT TO SIGN IN AS:";
cout<<"\n\t\t\t\t\t    1.SALESMAN";
cout<<"\n\t\t\t\t\t    2.ADMINISTRATOR";
cout<<"\n\t\t\t\t\t    3.EXIT";
cout<<"\n\t\t\t\t\t    ENTER YOUR OPTION: ";
cin>>option;	
	switch(option)
	{
		case 1: system("cls");
		        int choice;
		        char ch;
		        st:  
				topbar();                                                                        //label
		        cout<<"\n\n\t\t\t\t---------------------:WELCOME!!:---------------------\n";
		        cout<<"\n\t\t\t\t\tWHAT OPERATION DO YOU WANT TO PERFORM??";
		        cout<<"\n\t\t\t\t\t1.DISPLAY THE LIST OF ALL THE PRODUCTS";
		        cout<<"\n\t\t\t\t\t2.DISPLAY A PARTICULAR PRODUCT DETAIL";
		        cout<<"\n\t\t\t\t\t3.PLACE ORDER";
		        cout<<"\n\t\t\t\t\t4.BACK TO MAIN MENU";
		        cout<<"\n\t\t\t\t\t5.EXIT";
		        cout<<"\n\t\t\t\t\tPLEASE ENTER YOUR CHOICE: ";
		        cin>>choice;
		        switch(choice)
		        {
		        	case 1:ll:                    //label
					       system("cls");
		        	       topbar();
		        	       product_menu();
		        	       cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        	       cin>>ch;
		        	       if(ch=='Y'||ch=='y')
		        	       {
		        	        goto ll;
		        	       }
		        	       else if(ch=='N'||ch=='n')
		        	       {
		        	       	system("cls");
		        	        goto st;
		        	       }  
		        	       else
		        	       {
		        	       cout<<"\n\t\t\t\t\t\t     INVALID CHOICE!!";
		        	       cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        	       cin>>ch;
		        	       if(ch=='Y'||ch=='y')
		        	       {
		        	       goto ll;
		        	       }
		        	       else
		        	       {
		        	       	system("cls");
		        	        cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				            cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	        exit(0);
		        	       }
		        	       }
		        	       break;
		        	       
		        	case 2:rr:
					       system("cls");
		        	       topbar();
		        	       cout<<"\n\n\nEnter the product number whose details you want to display: ";
		        	       int number;
		        	       cin>>number;
		        	       system("cls");
		        	       topbar();
					       display_record(number); 
						   cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        	       cin>>ch;
		        	       if(ch=='Y'||ch=='y')
						   {
					        goto rr;
		        	       }
		        	       else if(ch=='N'||ch=='n')
						   {
						   	system("cls");
						    goto st;
		        	       } 
		        	       else
		        	       {
		        	       cout<<"\n\t\t\t\t\t\t     INVALID CHOICE!!";
		        	       cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        	       cin>>ch;
		        	       if(ch=='Y'||ch=='y')
		        	       {
		        	       goto rr;
		        	       }
		        	       else
		        	       {
		        	       	system("cls");
		        	        cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				            cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	        exit(0);
		        	       }
		        	       }
		        	       break;
		        	       
					case 3:zz:
					       system("cls");
					       topbar();
						   place_order(); 
						   cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        	       cin>>ch;
		        	       if(ch=='Y'||ch=='y')
						   {
						    goto zz;
		        	       }
		        	       else if(ch=='N'||ch=='n')
		        	       {
		        	       	system("cls");
						    goto st;
		        	       }
		        	       else
		        	       {
		        	       cout<<"\n\t\t\t\t\t\t     INVALID CHOICE!!";
		        	       cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        	       cin>>ch;
		        	       if(ch=='Y'||ch=='y')
		        	       {
		        	        goto zz;
		        	       }
		        	       else
		        	       {
		        	       	system("cls");
		        	        cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				            cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	        exit(0);
		        	       }
		        	       }
		        	       break;
		        	       
		        	case 4:system("cls");
		        	       topbar();
					       goto start;
					       break;
						         
					case 5:system("cls");
		        	       cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				           cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
					       exit(0);
					       break;
					       
					default:cout<<"\n\n\t\t\t\t\t\t    INVALID CHOICE!!";
					        cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        	        cin>>ch;
		        	        if(ch=='Y'||ch=='y')
		        	        {
		        	        system("cls");
		        	        goto st;
		        	        }
		        	        else if(ch=='N'||ch=='n')
		        	        {
							system("cls");
							cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				            cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	        exit(0);
		        	        }
							else
		        	        {
		        	         system("cls");
		        	         cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				             cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	         exit(0);
		        	        }			   	       
				}
		    	break;
		    	
		case 2: aa:                                             //label
		        system("cls");
		        topbar();
		        cout<<"\n\n\n\t\t\t\t\tPLEASE ENTER THE PASSWORD: ";
		        if(password()==1)
		        {
		        admin_menu();
		        if(flag==1)
		        goto start;
		        }
				else
				{
				 cout<<"\n\n\n\n\t\t\t\t\t\tINVALID PASSWORD!!";
				 tt:                                             //label
				 cout<<"\n\nDo you want to continue?(Y/N): ";
				 cin>>ch;
				 if(ch=='Y'||ch=='y')
				 {
				  goto aa;
			     }  
				 else if(ch=='N'||ch=='n')
				 {
				  system("cls");
				  topbar();	
				  goto start;
				 }
				 else
				 { 
				  cout<<"\nINVALID CHOICE!!";
				  goto tt;
				 }
			    }
				break;
				
		case 3: system("cls");
		        cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
				exit(0);
		
		default:cout<<"\n\n\t\t\t\t\t\t     INCORRECT OPTION!!";
		        cout<<"\n\nDO YOU WANT TO CONTINUE(Y/N): ";
		        cin>>ch;
    	        if(ch=='Y'||ch=='y')
		        {
	    	        system("cls");
	    	        topbar();
		        	goto start;
		        }
		        else if(ch=='N'||ch=='n')
		        {
					system("cls");
					cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				    cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	exit(0);
		        }
				else
		        {
		        	system("cls");
		        	cout<<"\n\n\n\n\n\n\n\n\n\n\n";
				    cout<<"\n\t\t\t\t\t\t    THANK YOU!!!";
		        	exit(0);
		        }
	}
getche();
}
//-------------------------------------------------------END OF PROGRAM--------------------------------------------------------
