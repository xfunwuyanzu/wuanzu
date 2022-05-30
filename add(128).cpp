#include <iostream>
#include <cstring>
using namespace std;
 
//找到小数点的位置，return int
int find_dot(char num[])
{
    int i;
    for(i=0;i<128;i++)
        if(num[i]=='.') break；
    return i;
}
 
//做浮点数加法
void add_float(char* a, char* b, char* res)
{
    /*测试函数的调用
    cout<<a[1]<<endl;
    cout<<b[2]<<endl;
    */
 
    //确定两个浮点数的小数点位置，浮点数前的0可以忽略
    int dotp1=find_dot(a);
    int dotp2=find_dot(b);
 
    //res的小数点位置是两个数的最大小数点位置+1,写入小数点
    int dot_res=max(dotp1,dotp2)+1;
    //cout<<"dot_res="<<dot_res<<endl;
    res[dot_res]='.';
 
    //做小数部分的加法:0.01+0.09
    int len1=strlen(a);
    int len2=strlen(b);
    int back_res=max(len1-1-dotp1,len2-1-dotp2);//res的小数个数
    int len_res=back_res+dot_res;//res末尾的数组计数法位置
    res[len_res+1]='\0';//让res结束
    for(int i=0;i<128;i++) if(a[i]='\0')a[i]='0';
    for(int i=0;i<128;i++) if(b[i]='\0')b[i]='0';
    for(int i=len_res;i>dot_res+1;i--)
    {
        if((res[i]-'0')+(a[dotp1+i-dot_res]-'0'+b[dotp2+i-dot_res]-'0')<10)
            res[i]=(res[i]-'0')+(a[dotp1+i-dot_res]-'0'+b[dotp2+i-dot_res]-'0')+'0';
        else
        {
            res[i]=(res[i]-'0')+(a[dotp1+i-dot_res]-'0'+b[dotp2+i-dot_res]-'0')-10+'0';
            res[i-1]='1';
        }
    }
    //小数点后一位的运算可能涉及到整数部分，因此分开考虑
    if((res[dot_res+1]-'0')+(a[dotp1+1]-'0'+b[dotp2+1]-'0')<10)
        res[dot_res+1]=res[dot_res+1]-'0'+(a[dotp1+1]-'0'+b[dotp2+1]-'0')+'0';
    else
    {
        res[dot_res+1]=res[dot_res+1]-'0'+(a[dotp1+1]-'0'+b[dotp2+1]-'0')-10+'0';
        res[dot_res-1]='1';
    }
 
 
    //实现整数部分的加法
    for(int i=dot_res-1;i>0;i--)//首位的处理包含在内
    {
        if((res[i]-'0')+(a[dotp1-(dot_res-i)]-'0'+b[dotp2+i-dot_res]-'0')<10)
            res[i]=(res[i]-'0')+(a[dotp1-(dot_res-i)]-'0'+b[dotp2+i-dot_res]-'0')+'0';
        else
        {
            res[i]=(res[i]-'0')+(a[dotp1-(dot_res-i)]-'0'+b[dotp2+i-dot_res]-'0')-10+'0';
            res[i-1]='1';
        }
    }
 
    if(res[0]=='0')
    {for(int i=0;i<127;i++) res[i]=res[i+1];
    dot_res--;}
 
    //删掉小数点后的全0
    //cout<<"bool前的res:"<<res<<endl;
    bool all_zero =true;
    //cout<<"dot_res:"<<dot_res<<endl;
    //cout<<"res[dot_res+1]:"<<res[dot_res+1]<<endl;
    for(int i=dot_res+1;i<=len_res;i++)
        if (res[i]!='0'&&res[i]!=0)
        {
            //cout<<"i:"<<i<<endl;cout<<"res[i]:"<<res[i]<<endl;
            all_zero=false;break;
        }
    //cout<<"all_zero:"<<all_zero<<endl;
    if(all_zero) {res[dot_res+1]='\0';}
 
    bool all_zeroz =true;
    //cout<<"dot_res:"<<dot_res<<endl;
    //cout<<"res[dot_res]:"<<res[dot_res]<<endl;
    for(int i=0;i<dot_res;i++)
        if (res[i]!='0'&&res[i]!=0)
        {
            //cout<<"i:"<<i<<endl;cout<<"res[i]:"<<res[i]<<endl;
            all_zeroz=false;break;
        }
    //cout<<"all_zeroz:"<<all_zeroz<<endl;
    //cout<<"res:"<<res<<endl;
    if(all_zeroz)
        for(int i=0;i<127;i++)
            res[i]=res[i+dot_res];
    //cout<<"res:"<<res<<endl;
    int newlen_res=strlen(res);
    for(int i=newlen_res;i>0;i--)
    {
        if(res[i]!=0&&res[i]!='0') break;
        else res[i]='\0';
    }
}
 
int main()
{
    char num1[128], num2[128], res[128];
    memset(num1,'0',128);
    memset(num2,'0',128);
    memset(res,'0',128);
    cin >> num1;
    cin >> num2;
    add_float(num1, num2, res);
 
    cout <<res<< endl;
    return 0;
}
