#include"integer.h"
 int power(int base,int exp)
 {
     int res=1;
     for(int i=0;i<exp;i++)
        res*=base;
    return res;
 }
 Integer::Integer(std::string init)
 {
     if(init[0]=='-')
     {
        val=init.substr(1,init.size()-1);
        mode='-';
     }
    else if(init[0]=='+')
    {
        val=init.substr(1,init.size()-1);
        mode='+';
    }
    else
    {
        val=init;
        mode='+';
    }
    

 }
 Integer Integer::operator++()
 {
     return *this+1;
 }
 Integer Integer::operator--()
 {
     return *this-1;
 }
 
Integer::Integer(int init)
{
    std::stringstream ss;
    ss<<init;
    if(init<0)
        ss>>mode>>val;
    else
    {
    ss>>val;
    mode='+';
    } 
    
}
std::ostream & operator<<(std::ostream & os, Integer & showint)
{
    if(showint.mode=='-')
        os<<'-';
    os<<showint.getval();
    return os;
}
Integer::Integer(long long init)
{
    std::stringstream ss;
    ss<<init;
    if(init<0)
        ss>>mode>>val;
    else
    {
    ss>>val;
    mode='+';
    }
}
Integer operator-(const Integer & origin)
{
    if(origin.mode=='-')
        return origin.val;
    else
    {
        std::string celes;
        celes="-"+origin.val;
        //std::cout<<"seles is"<<celes;
        return celes;
    }
    
}
/*Integer operator+(int add1,const Integer & add2)
{
    Integer add1_class=Integer(add1);
    return add1_class+add2;
}*/
Integer operator+(const Integer & add1,const Integer & add2)
{
    int i=add1.val.size()-1,j=add2.val.size()-1,k=0;
    int a[10]={0};
    int sign1,sign2;
    if(add1.mode=='+')
         sign1=1;
    else
         sign1=-1;
    if(add2.mode=='+')
         sign2=1;
    else
         sign2=-1;
    for(;i>=0&&j>=0;j--,i--,k++)
    {
        a[k]=sign1*(add1.val[i]-48)+(add2.val[j]-48)*sign2;
        
    }
    while(i>=0)
    {
        a[k]=sign1*(add1.val[i]-48);
        i--;
        k++;
    }
    while(j>=0)//715+93
    {
        a[k]=sign2*(add2.val[j]-48);
        j--;
        k++;
    }
    for(i=0;i<add1.val.size()+add2.val.size();i++)
        if(a[i]>9||a[i]<-9)
        {
            a[i+1]+=(a[i])/10;
            a[i]=(a[i])%10;

        }
    while(a[i]==0)
        i--;
    char ansmode;
    if(a[i]>0)
        ansmode='+';
    else ansmode='-';
    if(ansmode=='+')
    {
        for(j=0;j<i;j++)
            if(a[j]<0)
            {
                a[j]+=10;
                a[j+1]--;
            }
    }
    else
    {
        for(j=0;j<i;j++)
            if(a[j]>0)
            {
                a[j]-=10;
                a[j+1]++;
            }
    }
    while(a[k]==0)
        k--;
    for(j=0,i=k;i>=j;j++,i--)
    {
        int swap=a[i];
        a[i]=a[j];
        a[j]=swap;

    }
    j=0;
    std::string res;
    std::stringstream ss;
    if(ansmode=='+')
    {
    while(j<=k)
    {
        ss<<a[j];
        j++;
        
    }
    ss>>res;
    }
    if(ansmode=='-')
    {while(j<=k)
    {
        ss<<-a[j];
        j++;
        
    }
    ss>>res;
    res="-"+res;
    }
    //std::cout<<res<<std::endl;
    return res;
    
}
 Integer operator%(const Integer & dividend,const Integer & divisor)
 {
     Integer quo=dividend/divisor;
     Integer product=quo*divisor;
     return (dividend-product);
 }
Integer operator/(const Integer & dividend,const Integer & divisor)
{
    Integer dividend_copy=dividend;
    Integer quo=0;
    Integer divisor_copy=divisor;
    while(dividend_copy.mode=='+')
    {
    //std::cout<<"dividend-copy is";
    //dividend_copy.show();
    Integer time=power(10,dividend_copy.val.size()-divisor.val.size()-1);
    //std::cout<<"time is";
    //time.show();
    divisor_copy=divisor*time;
    //std::cout<<"divisor copy is";
    //divisor_copy.show();
    dividend_copy=dividend_copy-divisor_copy;
    quo=quo+time;
    //std::cout<<"quo is";
    //quo.show();
    }
    return(quo-1);
    
    
}
Integer operator-(const Integer & sub1,const Integer & sub2)
{
    Integer celes=-sub2;
    return sub1+celes;

    


}
Integer operator*(const Integer & mul1,const Integer & mul2)
{
    int i,j,k;
    int a[20]={0};
    for(i=0;i<mul1.val.size();i++)
        for(j=0;j<mul2.val.size();j++)
    a[mul1.val.size()-1-i+mul2.val.size()-1-j]+=(int)(mul1.val[i]-48)*(int)(mul2.val[j]-48);
    for(k=0;k<i+j;k++)
        if(a[k]>9)
        {
            a[k+1]+=a[k]/10;
            a[k]=a[k]%10;
        }
    while(a[k]==0)
        k--;
    for(i=0,j=k;i<=j;i++,j--)
    {
        int swap=a[i];
        a[i]=a[j];
        a[j]=swap;
    }
    std::stringstream ss;
    for(j=0;j<=k;j++)
     ss<<a[j];
       
    
       
    std::string res;
    ss>>res;
    //std::cout<<res<<std::endl;
    return res;
}
