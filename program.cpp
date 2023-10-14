/* Customer Billing Management System */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
using namespace std;
class head
{
    char itemName[50][50];

public:
    int totalItems;
    float Qty[3];
    float price[3];
    int vatPrice[3];
    int totalPrice[3];
    void input();
    void output();
};
class vat : public head
{
    float vats;

public:
    void calculateVat();
    void outputs();
    void sum();
};

//******************************************************************
//      INPUT FUNCTION
//******************************************************************

void head::input()
{
    system("CLS");
    cout << "\nEnter number of items= ";
    cin >> totalItems;

    for (int i = 0; i < totalItems; i++)
    {
        cout << "\nEnter name of item " << i + 1 << ": ";
        cin >> itemName[i];
        cout << "Enter quantity: ";
        cin >> Qty[i];
        cout << "Enter price of item " << i + 1 << ": ";
        cin >> price[i];
        totalPrice[i] = Qty[i] * price[i];
    }
}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//     OUTPUT FUNCTION
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void head::output()
{
    int a;

    ifstream infile("COUNT.TXT");
    infile >> a;

    ofstream outfile("COUNT.TXT");
    a += 1;
    outfile << a;
    outfile.close();

    {
        ofstream outfile("HISTORY.TXT", ios::app);
        outfile << endl
                << "Bill No.: " << a << endl;
        outfile << "------------------------------------------------------------------------" << endl;
        cout << "\n";
        cout << "Name of Item\tQuantity   Price  Total Price\n";
        for (int i = 0; i < totalItems; i++)
        {
            outfile << "Name: " << itemName[i] << " Qty: " << Qty[i] << " Price: " << totalPrice[i] << endl;
            cout << itemName[i] << "\t\t" << Qty[i] << "\t   " << price[i] << "\t   " << totalPrice[i] << '\n';
        }

        outfile << "------------------------------------------------------------------------" << endl;
        outfile.close();
    }
}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//     VAT CALCULATION
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void vat::calculateVat()
{
    input();
    for (int i = 0; i < totalItems; i++)
    {
        if (price[i] <= 100.00)
        {
            vatPrice[i] = totalPrice[i] + (0.03 * totalPrice[i]);
        }
        else
        {
            vatPrice[i] = totalPrice[i] + (0.1 * totalPrice[i]);
        }
    }
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//      VAT OUTPUTS
//*  * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * *
void vat::outputs()
{
    output();

    float cash = 0, sum = 0, qty = 0, sumOfTotal = 0;

    for (int i = 0; i < totalItems; i++)
    {
        sumOfTotal += totalPrice[i];
        sum += vatPrice[i];
        qty += Qty[i];
    }
    cout << "\nTotal:";
    cout << "\n------------------------------------------------------------------------------";
    cout << "\n\tQuantity= " << qty << "\t\t Sum= " << sumOfTotal << "\tWith Vat:" << sum;
    cout << "\n------------------------------------------------------------------------------";

pay:

    cout << "\n\n\t\t\t * * * * PAYMENT SUMMARY * * * * \n";
    cout << "\n\t\t\tTotal cash given: ";
    cin >> cash;

    if (cash >= sum)
        cout << "\n\t\t\tTotal cash repaid: " << cash - sum << '\n';

    else
    {
        cout << "\n\t\t\tCash given is less than total amount!!!";

        goto pay;
    }
}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//      PROTECTION PASSWORD
//* * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

int passwords()
{

    char p1, p2, p3;

    cout << "\n\n\n\n\n\n\t\t\tENTER THE PASSWORD: ";

    cin >> p1;
    cout << "*";
    cin >> p2;
    cout << "*";
    cin >> p3;
    cout << "*";

    if ((p1 == 's' || p1 == 'S') && (p2 == 'i' || p2 == 'I') && (p3 == 'd' || p3 == 'D'))

        return 1;

    else
        return 0;
}
// END of Password.

//****************************************************************
//      THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
    vat obj;
    char opt, ch;
    int a = 1;
    ifstream fin;

    a == passwords();
    if (!a)
    {
        for (int i = 0; i < 2; i++)
        {
            cout << "\nWrong password try once more\n";
            if (passwords())
            {
                goto last;
            }
            else
            {
                cout << "\n\n\t\t\t all attempts failed.....";
                cout << "\n\n\n\t\t\t see you.................. ";
                exit(0);
            }
        }
        cout << "\t\t\t sorry all attempts failed............. \n \t\t\tinactive";
    }
    else
    {
    last:;
        do
        {
        start:
            system("PAUSE");
            system("CLS");
            cout << "\n\n\t\t\t------------------------------";
            cout << "\n\t\t\tBilling Management System";
            cout << "\n\t\t\t------------------------------";
            cout << "\n\n\t\t\tWhat you want to do?";
            cout << "\n\t\t\t1.\tTo enter new entry\n\t\t\t2.\tTo view previous entries\n\t\t\t3.\tExit\n";
            cout << "\n\nEnter your option: ";
            cin >> opt;
            switch (opt)
            {
            case '1':
                obj.calculateVat();

                obj.outputs();
                goto start;
            case '2':

                fin.open("HISTORY.TXT", ios::in);
                while (fin.get(ch))
                {
                    cout << ch;
                }
                fin.close();

                goto start;
            case '3':
                exit(0);
            default:
                cout << "\a";
            }

        } while (opt != 3);
    }
    return 0;
}
