#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};
//functions to generate bills
void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");
         printf("==============FOOD GARDEN==================\n \tVeg & Nonveg Restaurant\n \t\tMangalore");
        printf("\n\t   -----------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
       
}
void generateBillBody(char item[30],int qty, float price){
    printf("%s\t\t",item); 
        printf("%d\t\t",qty); 
        printf("%.2f\t\t",qty * price); 
        printf("\n");
        
}



void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.05*netTotal,grandTotal=netTotal + 2*cgst;  //netTotal + cgst + sgst
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @5%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @5%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
    printf("\n\t\t Thank you. Visit Again :)\n\n");
        printf("\n\n");
}
int main(){
    
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag = 'y';
    char name[50];
    FILE *fp;
       //dashboard
    while(contFlag == 'y'){
    system("clear");
    float total = 0;
    int invoiceFound = 0;
    printf("\n");
    printf("\t\t\t\t\t\t\t============FOOD GARDEN============\n");
printf("\t\t\t\t\t\t\t\tVeg & Nonveg Restaurant\n \t\t\t\t\t\t\t\t\tMangalore");
    printf("\n\nPlease select your prefered operation");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt){
        case 1:
        system("clear");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);                            //This line reads a string of characters from the standard input stream stdin (i.e., the console), up to a maximum of 50 characters, and stores it in the ord.customer array. The fgets function reads characters until it encounters a newline character or the maximum number of characters specified, whichever comes first.
        ord.customer[strlen(ord.customer)-1] = 0;            //modifies a string by removing its last character
        strcpy(ord.date,__DATE__);                           //This line copies the current date and time (represented as a string) to the ord.date array. The __DATE__ macro is a predefined macro in C that expands to a string representing the date on which the program was compiled.
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.numOfItems = n;                                     //This line assigns the value of n to the numOfItems member of the ord struct, which represents the number of items in the order.
        for(int i=0;i<n;i++){                              // loop iterates upto n items to collect name, quantity and price of each item
            fgetc(stdin);                                 
            printf("\n\n");
            printf("Please enter the item %d:\t",i+1);    //enter 1st item ==> 0+1=1
            fgets(ord.itm[i].item,20,stdin);               //This line reads a string of characters from the standard input stream, representing the name of the current item, and stores it in the item member of the i-th element of the itm array in the ord struct. 
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;      //This line removes the newline character at the end of the string entered by the user, similar to the earlier line that removed the newline character from the customer name.
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);                   //qty member of ith element of itm array of struct ord    
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;      //multiplying quantity and price and output to total
        }

        generateBillHeader(ord.customer,ord.date);          //function call to output bill header
        for(int i=0;i<ord.numOfItems;i++){                   
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);       // function call to output bill body for each item
        }
        generateBillFooter(total);

        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s",&saveBill);

        if(saveBill == 'y'){
           fp = fopen("RestaurantBill.dat","a+");

          /*opens a file named "RestaurantBill.dat" in append mode, 
          which means that any data written to the file will be added to the end of 
         the existing data. The fopen function returns a pointer to a FILE structure that 
          represents the opened file. This pointer is stored in the fp variable,
           which will be used to access the file in subsequent file I/O operations.*/
  
            fwrite(&ord,sizeof(struct orders),1,fp);  //contents of ord variable are stored in the file referenced by fp variable ie, RestaurantBill.dat. four arguments: a pointer to the data to be written (&ord), the size of each element of the data (sizeof(struct orders)), the number of elements to write (1), and a pointer to the file to write to (fp).
            if(fwrite != 0)
            printf("\nSuccessfully saved");
            else 
            printf("\nError saving");
            fclose(fp);
        }
        break;

        case 2:         //display all saved invoices
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\n  *****Your Previous Invoices*****\n");
        while(fread(&order,sizeof(struct orders),1,fp)){    //contents of ord variable in the file referred by fp variable is read one by one so while loop is used
            float tot = 0;
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;

        case 3:
        printf("Enter the name of the customer:\t");
        //fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;    //This line removes the newline character ('\n') at the end of the string stored in the name variable.
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\t*****Invoice of %s*****",name);
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(!strcmp(order.customer,name)){   //if names match, result of strcmp(order.customer,name) is 0. So the expression is negated to give 1 and enter the if condition.
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
            invoiceFound = 1;
            }
        
        }
        if(!invoiceFound){
            printf("Sorry the invoice for %s doesnot exists",name);
        }
        fclose(fp);
        break;

    case 4:
    printf("\n\t\t Thank you. Visit Again  :)\n\n");
    exit(0);
    break;

    default:
    printf("Sorry invalid option");
    break;
    }
    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf("%s",&contFlag);
    }
    printf("\n\t\t Thank you. Visit Again :)\n\n");
    printf("\n\n");

    return 0;
}
