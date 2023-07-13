#include<iostream>
using namespace std;

int main()
{
int arr[] = {1,2,3,7,5};
int k=1,flag=0;
int n=12;
while(k!=5)
{
   for(int i=0;i<5;i++)
   {
       int l=i;
       int sum=0;
       for(int j=0;j<k;j++)
       {
        sum=sum+arr[l];
        //printf("%d,",l);
        cout<<l<<",";
       l++;

       }
      // printf(" sum=%d\n",sum);
      cout<<"sum="<<sum<<endl;
       if(sum==n)
       {
           //printf("st=%d,en=%d\n",i,l-1);
           cout<<"i="<<i<<"l-1"<<l-1<<endl;
           flag=1;
       }
   }
   k=k+1;
}

if(flag==1)
{
    return -1;
}
return 0;
}
