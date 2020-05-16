#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <iomanip>
#include <cmath>

using namespace std;

int main(){
	
	cout << fixed << setprecision(2);
	
	// ---------------------------------------------------
	ifstream file ( "sp500.csv" ); // change to sp500.cvs when you're ready
	
	int NUM_ROW = 16534 ,NUM_ROW1; //skip the first row, use index in the range [1, 16532]
	// all NUM_ROW = 16426
	// 1 year NUM_ROW = 253
	// 3 years NUM_ROW = 754
	// 5 years NUM_ROW = 1260
	// 10 years NUM_ROW = 2517
	int i=0,k=0,j=0,num1 = 15,num2 = 50;
	cout << "---------------Strategy 1 : Moving Average Crossover---------------"<<endl;
	cout<<"Choices: "<<endl;
	cout<<"1) 253 business days (1 years) "<<endl;
	cout<<"2) 754 business days (3 years) "<<endl;
	cout<<"3) 1260 business days (5 years) "<<endl;
	cout<<"4) 2517 business days (10 years) "<<endl;
	cout<<"5) 16429 business days (65 years) "<<endl;
	cout<<"6) Any business days "<<endl;
	cout<<"How many business days: ";
	cin>>NUM_ROW1;
	string date[NUM_ROW],date_s[NUM_ROW], temp;
	float buy_sh,sell_sh,buy_pr,sell_pr,re_budget,budget = 10000,gain_loss,numyear;
	int n_act,act_temp,num_sh = 0;
	float price[NUM_ROW],price_s[NUM_ROW],total1,avg1,total2,avg2,MA15,MA50,annual;
	char act[4];
	
	//cout << "Reading dataset from file ..."<<endl;
	while ( file.good() )
	{
	     getline ( file, date[i], ',' );
	     getline ( file, temp);
	     stringstream(temp) >> price[i];
	     i++;
	}
	//cout << "Done ..."<<endl;
	cout << "Starting balance: 10000"<<endl;
//-------------------------------------strategy1--------------------------------------------------------------

	cout <<"Date-Month-Year"<<"\tMA[15]"<<"\tMA[50]"<<"\tStatus"<<"\tsh pri"<<"\tNo.sh"<<"\tBalance"<<endl;
    for (k = NUM_ROW1; k >= 1 ; k--)
    {
    	total1 = 0;
    	avg1 = 0;
        for (j = k; j < k+num1; j++)
        {
            total1+=price[j];
        }
        avg1 = total1/num1;
        MA15 = avg1;
        
    	total2 = 0;
    	avg2 = 0;
        for (j = k; j < k+num2; j++)
        {
            total2+=price[j];
        }
        avg2 = total2/num2;
        MA50 = avg2;
//       cout << date[k]<< "\t" <<MA15<< "\t" <<MA50;
        
        if (MA15>MA50)
			{
				strcpy(act,"BUY");
				n_act = 0;
//				cout <<"\t" <<act<<endl;
			}
		else if (MA15<MA50)
			{
				strcpy(act,"SELL");
				n_act = 1;
//				cout <<"\t"  <<act<<endl;
			}
			
		if (k < NUM_ROW1+1)
        	{
        		if (n_act != act_temp)
            	{
            		if (n_act == 0)
            		{
            			num_sh = budget/price[k];
	            		buy_pr = num_sh*price[k];
	            		re_budget = budget - buy_pr;
	            		buy_sh = price[k];
	            		cout << date[k]<< "\t" <<MA15<< "\t" <<MA50;
	            		cout<<"\t"<<act<<"\t"<<price[k];
	            		cout<<"\t"<<num_sh<<"\t"<<re_budget<<endl;
					}

					else if ((n_act == 1)&&(num_sh !=0))
					{
						sell_pr = num_sh*price[k];
						budget = re_budget + sell_pr;
						sell_sh = price[k];
						cout << date[k]<< "\t" <<MA15<< "\t" <<MA50;
						cout<<"\t"<<act<<"\t"<<price[k];
						cout<<"\t"<<num_sh<<"\t"<<budget<<endl;
						num_sh = 0;
					}
				}
			}
			else
			{
				
				act_temp = n_act;
				
			}
			act_temp = n_act;
			
    }
    
	cout << "Ending balance: " << budget<<endl;
	gain_loss = budget - 10000;
	
	float NUM_ROW2 = NUM_ROW1;
	numyear = ceil(NUM_ROW2/253);
	annual =((gain_loss/10000)*100/numyear);
	
	cout << "gain/loss : " << gain_loss<<" (" <<annual<< " % annualised)"<<endl;
	
	return 0;
}
