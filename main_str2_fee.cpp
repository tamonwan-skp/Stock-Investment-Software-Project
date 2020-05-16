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
	cout << "---------------Strategy 2 : Stochastic Oscillator---------------"<<endl;
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
	float price[NUM_ROW],buy_sh,sell_sh,buy_pr,sell_pr,re_budget,budget = 10000,gain_loss,fee = 10;
	int n_act,act_temp,num_sh = 0;
	int num_K = 14,num_D = 3,K_count;
	float H14, L14, C, K,K_b,D,D_b,temp_K[NUM_ROW],cur_price,temp_d,k_temp,Kmax = 0, Kmin = 5000,numyear,annual;
	
	char act[4];
	
	cout << "Reading dataset from file ..."<<endl;
	while ( file.good() )
	{
	     getline ( file, date[i], ',' );
	     getline ( file, temp);
	     stringstream(temp) >> price[i];
	     i++;
	}
	cout << "Done ..."<<endl;
	cout << "---------------------------------------------------------------------------"<<endl;
//---------------------------------------strategy2--------------------------------------
	cout << "Starting balance: 10000"<<endl;
	cout <<"Date-Month-Year"<<"\tK(%)"<<"\tD(%)"<<"\tStatus"<<"\tsh pri"<< "\tFee"<<"\tNo.sh"<<"\tBalance"<<endl;

	for (k = 1; k < NUM_ROW1+num_D ; k++)
    {
	Kmax = 0;
	Kmin = 5000;
		for (j = k; j < k+num_K; j++)
        {
            if(Kmax<price[j])
            {
            	Kmax=price[j];
			}
			if(Kmin>price[j])
            {
            	Kmin=price[j];
			}
        }
        H14 = Kmax;
        L14 = Kmin;
        C = price[k];
        k_temp = 100*((C-L14)/(H14-L14));


		temp_K[k] = k_temp;

    }


 	temp_d = 0;
  	for (i = NUM_ROW1+1; i <= NUM_ROW1+num_D ; i++)
  	{
  		temp_d+=temp_K[i];
	}
	D_b = temp_d/num_D;
	K_b = temp_K[NUM_ROW1+1];
	
  	for (k = NUM_ROW1; k >= 1 ; k--)
  	{
  		temp_d = 0;
  		for (i = k; i < k+num_D ; i++)
  		{
  			temp_d+=temp_K[i];
		}
		D = temp_d/num_D;
		K = temp_K[k];
//		cout << date[k] <<"\tK " <<K<<"\tD " <<D<<endl;
		
		if ((D_b<K_b)&&(D>=K)&&(D<=20))
			{

					strcpy(act,"BUY");
					n_act = 0;

				
			}
		else if ((D_b>K_b)&&(D<=K)&&(D>=80))
			{

					strcpy(act,"SELL");
					n_act = 1;

			}
		D_b = D;
		K_b = K;
		
		if ((k < NUM_ROW1+1)&&(k>1))
        	{
        		if (n_act != act_temp)
            	{
            		if (n_act == 0)
            		{
            			num_sh = budget/price[k];
	            		buy_pr = num_sh*price[k];
	            		re_budget = budget - buy_pr - fee;
	            		buy_sh = price[k];
	            		cout << date[k]<< "\t" <<K<< "\t" <<D;
	            		cout<<"\t"<<act<<"\t"<<price[k];
	            		cout<<"\t"<<fee<<"\t"<<num_sh<<"\t"<<re_budget<<endl;
					}

					else if ((n_act == 1)&&(num_sh !=0))
					{
						sell_pr = num_sh*price[k];
						budget = re_budget + sell_pr - fee;
						sell_sh = price[k];
						cout << date[k]<< "\t" <<K<< "\t" <<D;
						cout<<"\t"<<act<<"\t"<<price[k];
						cout<<"\t"<<fee<<"\t"<<num_sh<<"\t"<<budget<<endl;
						num_sh = 0;
					}
				}
			}
		else if (k == 1)
			{
				if (act_temp == 0)
				{
					strcpy(act,"SELL");
					sell_pr = num_sh*price[k];
					budget = re_budget + sell_pr - fee;
					sell_sh = price[k];
					cout << date[k]<< "\t" <<K<< "\t" <<D;
					cout<<"\t"<<act<<"\t"<<price[k];
					cout<<"\t"<<fee<<"\t"<<num_sh<<"\t"<<budget<<endl;
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
}
