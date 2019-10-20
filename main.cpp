/* 字符串首NEXT值为-1*/
#include <iostream>
#include <string>
using namespace std;
class MyString
{
private:
    string myStr;
    int size;
    /*对传入的任一字符串求其next值*/
     void getNext_from_neg1(string p,int next[]);
    void getNext_from_zero(string p,int next[]);
    int KMPfind(string &p,int pos,int next[]);
public:
    MyString(){
        myStr="";
        size=0;
    };
    ~MyString(){
        myStr="";
        size=0;
    }
    void initial(string &str)
    {
        myStr=str;
        size=str.size();
    }
    int KMPFindSubStr(string p,int pos);
    void ReplaceSubStr(string substr,string repstr)
    {
        while(KMPFindSubStr(substr,0)>=0)
        {
            myStr.replace(KMPFindSubStr(substr,0),substr.size(),repstr);
        }
        cout<<myStr;
    };
    void LongestRepStr();
};
int MyString::KMPFindSubStr(string p, int pos) {
    /*对子串求next值*/
    int *sub_next=new int[p.size()];
    getNext_from_neg1(p,sub_next);
    for (int i = 0; i < p.size(); ++i) {
        cout<<sub_next[i]<<' ';
    }
    cout<<endl;
    /*利用私有函数*/
    int find_pos=KMPfind(p,pos,sub_next);
}
void MyString::getNext_from_neg1(string p, int *next) {
    /*i是字符串检查的后指针，从检查位置的头开始，j的初始值为串头的next值*/
    int i=0,j=-1;
    /*设置串头的next值*/
    next[0]=j;
    while(i<p.size())
    {
        /*j==-1指示回到串头*/
        if(j==-1||p[i]==p[j])
        {
            ++i;
            ++j;
            next[i]=j;
        }
        else{
            j=next[j];
        }
    }
}
void MyString::getNext_from_zero(string p, int *next) {
    /*i是字符串检查的后指针，从检查位置的头开始，j的初始值为串头的next值*/
    int i=1,j=0;
    /*next[0]保存字符串长*/
    next[0]=p.size();
    next[1]=j;
    while(i<next[0])
    {
        /*j==-1指示回到串头*/
        if(j==0||p[i]==p[j])
        {
            ++i;
            ++j;
            next[i]=j;
        }
        else{
            j=next[j];
        }
    }
}
/*不在next数组里保存长度，字符串检查从0开始，失败则返回-1,否则返回对应数组下标*/
int MyString::KMPfind(string &p, int pos, int *next) {
    int i=pos,j=0;
    /*i和j分别指示主串和子串检查的起始位置*/
    /*size（）函数返回无符号数，而j有可能为负数，两者进行比较会将j转化为无符号数，则-1->1*/
    while(i<myStr.size()&&j<(int)p.size())
    {
        if(j==-1||myStr[i]==p[j])
        {
            ++i;
            ++j;
        }
        else{
            j=next[j];
        }
    }
    if(j==p.size())
    {
        return i-j;
    }else{
        return -1;
    }
}
void MyString::LongestRepStr() {
    int maxx= 0;
    /*最长可重复子串，即next值中的最大值*/
    int *next=new int[size];
    getNext_from_neg1(myStr,next);
    for (int i = 0; i < size; ++i) {
        if(next[i]>maxx)
        {
            maxx=next[i];
        }
    }
    if(maxx!=0)
    {
        cout<<maxx+2<<endl;
    }
    else cout<<"-1"<<endl;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        string mainstr,substr,restr;
        cin>>mainstr>>substr;
        MyString main;
        main.initial(mainstr);
        cout<<main.KMPFindSubStr(substr,0)<<endl;
        cin>>restr;
        main.ReplaceSubStr(substr,restr);
        main.LongestRepStr();
    }
}