//IMPLEMENTATION OF BIG INTEGER LIBRAY TO PERFORM ADDITION,SUBTRACTION,MULTIPLICATION,DIVISION
#include <stdio.h>
#include <stdlib.h>
/// CREATION OF LINKED LIST STRUCTURE
struct node{
    int data;
    struct node *next;

};


//CREATION OF STRUCTURE OF BIG INTEGERS
struct big_int{
    struct node *head;
    int size;
    int sign;   //1 for positive and
                //-1 for negative
};


//to create node
struct node * createnode(int data)
{
    struct node *new=(struct node *)malloc(sizeof(struct node));
    new->data=data;
    new->next=NULL;
    return new;

}

//to create a biginteger
struct big_int * initialize_bigint()
{
    struct big_int *n=(struct big_int *)malloc(sizeof(struct big_int));
    n->head=NULL;
    n->size=0;
    n->sign=1;
    return n;
}



//
void push(struct big_int *n,int val)
{
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    temp->data=val;
    temp->next=n->head;
    n->head=temp;
    n->size++;

}


//
/*void adddigit(struct big_int* bigint,int data)
{
    struct node *new=createnode()
}*/



//to print the result or the entered big integer
void display(struct big_int *n)
{
    if(n->size==0)
    {
        printf("0");
    }
    else
    {
        struct node *curr=n->head;
        while (curr!=NULL)
        {
            printf("%d",curr->data);
            curr=curr->next;
        }
    }
    printf(" \n ");

}



// Function to remove extra zeros
void truncate(struct big_int * bigInt) {
    while (bigInt->head != NULL && bigInt->head->data == 0) {
        struct Node * temp = bigInt->head;
        bigInt->head = bigInt->head->next;
        free(temp);
    }
}





//to reverse
struct node *reverse(struct node *head)
{
    struct node *prevptr=0,*current,*nextptr;
    current=head;
    while(current!=0)
    {
       nextptr=current->next;
       current->next=prevptr;
       prevptr=current;
       current=nextptr;

    }
    return prevptr;
}

///to compare two big integers
int compare(struct big_int* num1,struct big_int* num2)
 {
    truncate(num1);
    truncate(num2);

    if (num1->head == NULL && num2->head == NULL)
        return 0;

    if (num1->head == NULL)
        return -1;

    if (num2->head == NULL)
        return 1;

    struct node * n1= num1->head;
    struct node * n2 = num2->head;

    while (n1 != NULL && n2 != NULL)
    {
       if((n1->data)>(n2->data))
       {
        return 1;
       }
       else{
        return -1;
       }
    }
    if(n1!=0)
    {
        return 1;
    }
    if(n2!=0)
    {
        return -1;
    }
 }







///function to add big intergers
struct big_int * addition(struct big_int * num1,struct big_int *num2)
{
    int carry=0;
   struct big_int *res=initialize_bigint();
   
    struct node * n1=num1->head;
    struct node *n2=num2->head;
    while(n1||n2||carry)
    {
        int sum=carry;
        if(n1)
        {
            sum=sum+(n1->data);
            n1=n1->next;

        }

        if(n2)
        {
            sum=sum+(n2->data);
           n2=n2->next;
        }

        

        carry=sum/10;
        push(res,sum%10);

    }
    return res;

}





//FUNCTION TO SUBTRACT BIG INTEGERS
struct big_int * subtraction(struct big_int * num1,struct big_int * num2)
{
    struct big_int *res=initialize_bigint();
    int borrow=0;
    struct node * n1=num1->head;
    struct node *n2=num2->head;

    while(n1!=0 || n2!=0)
    {
        int v1=n1->data;
        int v2=n2->data;
        //int sub;
        int sub=v1-v2-borrow;
       /* if((n1->data)>(n2->data))
        {
            sub=v1-v2-borrow;
        }
        else{
            sub=v2-v1-borrow;
        }*/
        if(sub<0)
        {
             sub=sub+10;
             borrow=1;
        }
        else{
            borrow=0;
        }
        push(res,sub);
        n1=n1->next;
        n2=n2->next;
        
        
          

      
    }
    
    /*///to remove zero (truncate)
    while(res->size>1 && res->head->data==0)
    {
        struct node *temp=res->head;
        res->head=res->head->next;
        free(temp);
        res->size--;

    }*/

        


    truncate(res);
    return res;
    

}



///to multiply two big integers
struct big_int *mul(struct big_int *num1,struct big_int *num2)
{
    
    struct big_int *res=initialize_bigint();
    
    //struct big_int *ptr=initialize_bigint();
    struct node *headmain=0;
    
    
    /*int itr=1;
    while(n2!=0)
    {
        struct node *headnew=0;
        n1=num1->head;
        while(n1!=0)
        {
            push(headnew,n1->data*n2->data);
            n1=n1->next;
        }
        if(itr>1)
        {
            int x=1;
            while(x<itr)
            {
                struct node *new=(struct node*)malloc(sizeof(struct node));
                new->data=0;
                new->next=headnew;
                headnew=new;
                x++;
            }
        }
        struct big_int *newans;
        newans->head=headnew;
        res=addition(res,newans);
        res=reverse(res->head);
        n2=n2->next;
        itr++;
    }
    res=reverse(res->head);
    //truncate(res);
    return res;*/
    
    int shift=0;
    struct node *n1=num1->head;
    while(n1!=0)
    {
        int carry=0;
        int digit=n1->data;
        struct node *n2=num2->head;
        struct big_int *temp=initialize_bigint();
        for(int i=0;i<shift;i++)
        {
            push(temp,0);
        }
        
        while(n2!=0 || carry)
        {
            int p=(n2 ? n2->data:0)*digit+carry;
            
            carry=p/10;
            //p=p%10;
           
            push(temp,p%10);
            
            if(n2)
            {
                n2=n2->next;
            }
           

        }
        
        res=addition(res,temp);
        shift++;
        n1=n1->next;

        
    }
    //reverse(res);
    truncate(res);
    return res;

}



//to divide two bigintegers
struct big_int *division(struct big_int *num1,struct big_int *num2)
{
    if(num2->head==0 ||num2->head->data==0 )
    {
        printf("division not possible by zero");
        return 0;

    }
    
    struct big_int *res=initialize_bigint();
    struct big_int *temp=initialize_bigint();
    struct big_int *ptr=initialize_bigint();
    int divisorval=0;
    struct node *n1=num1->head;
    //struct node *n2=num2->head;
    
    
    while(n1!=0)
    {
       push(ptr,n1->data);
       //truncate(temp);
       n1=n1->next;

       divisorval=0;
       while(compare(ptr,num2)>=0)
       {
        subtraction(ptr,num2);
        divisorval++;
       }
       push(res,divisorval);
      
    }
    
    truncate(res);
    return res;

}







int main()
{
    struct big_int *num1=initialize_bigint();
    struct big_int *num2=initialize_bigint();


    //inserting values 
    push(num1,9);
    push(num1,3);
    push(num1,3);
    

    push(num2,5);
    push(num2,7);
    push(num2,5);
    

    //calling function for addition of two numbers
    struct big_int *sum=addition(num1,num2);
    printf("sum =");
    display(sum);

    
    //calling function for subtraction of two numbers
    struct big_int *sub=subtraction(num1,num2);
    printf("subraction =");
    display(sub);

    //calling function for multiplication
    struct big_int *multi=mul(num1,num2);
    printf("multiplication =");
    display(multi);

    //calling function for division
    struct big_int *div=division(num1,num2);
    printf("division =");
    display(div);


    return 0;


}
