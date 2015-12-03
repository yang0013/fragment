//
// 火星坐标系 (GCJ-02) 与百度坐标系 (BD-09) 的转换算法
//
#include <math.h>  
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>  
#include <string>  
#include <sstream> 
#include <vector> 
using namespace std;
  
const double x_pi = 3.14159265358979324 * 3000.0 / 180.0;  
  
template <class Type>  
Type stringToNum(string& str)  
{  
    istringstream iss(str);  
    Type num;  
    iss >> num;  
    return num;      
}  

//字符串分割函数  
vector<string> split(string str,string pattern)  
{  
    string::size_type pos;  
    vector<string> result;  
    str+=pattern;//扩展字符串以方便操作  
    int size=str.size();  
  
    for(int i=0; i<size; i++)  
    {  
        pos=str.find(pattern,i);  
        if(pos<size)  
        {  
            string s=str.substr(i,pos-i);  
            result.push_back(s);  
            i=pos+pattern.size()-1;  
        }  
    }  

    return result;  
}  

// bd_encrypt 将 GCJ-02 坐标转换成 BD-09 坐标
void bd_encrypt(double gg_lat, double gg_lon, double &bd_lat, double &bd_lon)  
{  
    double x = gg_lon, y = gg_lat;  
    double z = sqrt(x * x + y * y) + 0.00002 * sin(y * x_pi);  
    double theta = atan2(y, x) + 0.000003 * cos(x * x_pi);  
    bd_lon = z * cos(theta) + 0.0065;  
    bd_lat = z * sin(theta) + 0.006;  
}  
  
// BD-09 坐标转换成 GCJ-02 坐标
void bd_decrypt(double bd_lat, double bd_lon, double &gg_lat, double &gg_lon)  
{  
    double x = bd_lon - 0.0065, y = bd_lat - 0.006;  
    double z = sqrt(x * x + y * y) - 0.00002 * sin(y * x_pi);  
    double theta = atan2(y, x) - 0.000003 * cos(x * x_pi);  
    gg_lon = z * cos(theta);  
    gg_lat = z * sin(theta);  
}  

int main(int argc, char *argv[]) {

    if (argc != 3 ) {
        cout << "请输入文件名！" << endl;
        return 1;
    }

    ofstream out;  
    ifstream in;  
    string pattern = ",";
    
    char *file = argv[1];
    char *outfile = argv[2];
	cout << "infile: " << file << " outfile:" << outfile << endl;
    in.open(file, ios::in);
    out.open(outfile, ios::out);
    out.precision(15);

    if (!in.is_open())  
    {
        cout << "Error opening file"; 
        return 1; 
    }  

//	out<<"name,address,longitude,latitude"<<endl;
    while (!in.eof())  
    {  
        string str; 
        in >> str; 

        vector<string> result=split(str,pattern);  
        
        if(result.size() ==4 ) {
            double x;
            double y;
            x=atof(result[2].c_str());
            y=atof(result[3].c_str());
            if(x>0 && y > 0) {
                double nx; double ny;
                bd_decrypt(y,x,ny,nx);
                out<<result[0]<<pattern<<result[1]<<pattern<<nx<<pattern<<ny<<endl;
            }
        }
    }  

    return 0;
}

