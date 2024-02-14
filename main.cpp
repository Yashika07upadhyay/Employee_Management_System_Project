#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<cstdlib>
#include<string>
#include<iomanip>
using namespace std;
const int EMP_ID_WIDTH=8;
const int EMP_NAME_WIDTH=20;
const int EMP_EMAIL_WIDTH=25;
const int EMP_NUMERIC_WIDTH=10;
const int TOTAL_WIDTH=100;
struct Employee{
	int empId;
	string name;
	double basicSalary;
	double pf;
	double healthInsAmt;
	string email;
};
void readfile(	vector<Employee>& v_emp){
	ifstream fin("emp.txt");
	if(!fin){
		cout<<"Unable to open database file with this name."<<endl;
		cout<<"Make sure you have entered correct name."<<endl;
		exit(1);
	}
	string line;
	int recNo=0;
	while(!fin.eof()){
		std::getline(fin,line);
		recNo++;
		//cout<<recNo<<"-"<<line<<endl;
istringstream iss(line);
string strEmpId;
string strName;
string BasicSalary;
string strpf;
string strHealthAmt;
string strEmail;
std::getline(iss,strEmpId,',');
std::getline(iss,strName,',');
std::getline(iss,BasicSalary,',');
std::getline(iss,strpf,',');
std::getline(iss,strEmail,',');
Employee temp;
temp.empId=atoi(strEmpId.c_str());
temp.name=strName;
temp.basicSalary=atof(BasicSalary.c_str());
temp.pf=atof(strpf.c_str());
temp.healthInsAmt=atof(strHealthAmt.c_str());
temp.email=strEmail;
v_emp.push_back(temp);
	}
	fin.close();
}
void printMenu(){
	cout<<"1.Add Employee"<<endl;
	cout<<"2.Print Employee Report"<<endl;
	cout<<"3.Search Employee"<<endl;
	cout<<"4.Delete Employee"<<endl;
	cout<<"5.Save"<<endl;
	cout<<"6.Exit"<<endl;
}
int search(vector<Employee> v_emp,int target){
	for(int i=0;i<v_emp.size();++i){
		if(v_emp[i].empId==target){
			return i;
		}
	}
	return -1;
}
void addEmployee(vector<Employee>& v_emp){
	Employee temp;
	bool duplicateId;
	do{
		cout<<"Emp Id:"<<endl;
		cin>>temp.empId;
		duplicateId=false;
		if(search(v_emp,temp.empId)!=-1){
			duplicateId=true;
			cout<<"Employee id:"<<temp.empId<<"already exists,please input another id!"<<endl;
		}
	}while(duplicateId);
	cout<<"Name:"<<endl;
	cin.clear();
	cin.ignore(INT_MAX,'\n');
	std::getline(cin,temp.name);
	cout<<"Basic Salary($):"<<endl;
	cin>>temp.basicSalary;
	cout<<"PF($):"<<endl;
	cin>>temp.pf;
	cout<<"HealthIns($):"<<endl;
	cin>>temp.healthInsAmt;
	cout<<"Email:"<<endl;
	cin.clear();
	cin.ignore(INT_MAX,'\n');
	std::getline(cin,temp.email);
	v_emp.push_back(temp);
	cout<<"Employee with Id:"<<temp.empId<<"added sucessfully"<<endl;
	cout<<"Total no. of employees: "<<v_emp.size()<<endl;
		
}
double getNetSalary(Employee e){
	return e.basicSalary-(e.pf+e.healthInsAmt);
}
void printEmployee(Employee e){
	cout<<setw(EMP_ID_WIDTH)<<left<<e.empId
	<<setw( EMP_NAME_WIDTH)<<left<<e.name
	<<setw(EMP_EMAIL_WIDTH)<<left<<e.email
	<<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<e.basicSalary
	<<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<e.pf
	<<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<e.healthInsAmt
	<<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<getNetSalary(e)<<endl;
}	
void printEmployee(vector<Employee> v_emp){
	cout<<endl;
	cout<<setw( EMP_ID_WIDTH)<<left<<"Emp_Id"
	<<setw( EMP_NAME_WIDTH)<<left<<"Name"
	<<setw(EMP_EMAIL_WIDTH)<<left<<"Email"
	<<setw(EMP_NUMERIC_WIDTH)<<right<<"Basic($)"
	<<setw(EMP_NUMERIC_WIDTH)<<right<<"PF($)"
	<<setw(EMP_NUMERIC_WIDTH)<<right<<"HealthIns($)"
	<<setw(EMP_NUMERIC_WIDTH)<<right<<"Net($)"
	<<endl;
	cout<<setw(TOTAL_WIDTH)<<setfill('-')<<" "<<endl;
	cout<<setfill(' ');
	double totalBasic=0.0;
	double totalPfDeduction=0.0;
	double totalHealthInsAmt=0.0;
	double totalNetSalary=0.0;
	for(vector<Employee>::iterator it=v_emp.begin();it!=v_emp.end();it++){
		printEmployee(*it);
		totalBasic+=it->basicSalary;
		totalPfDeduction+=it->pf;
		totalHealthInsAmt+=it->healthInsAmt;
		totalNetSalary+=getNetSalary(*it);
	}
	cout<<setw(TOTAL_WIDTH)<<setfill('-')<<" "<<endl;
	cout<<setfill(' ');
	cout<<setw(EMP_ID_WIDTH)<<left<<"Total"
     <<setw(EMP_NAME_WIDTH)<<left<<"In($)"
     <<setw(EMP_EMAIL_WIDTH)<<" "
     <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<totalBasic
     <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<totalPfDeduction
     <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<totalHealthInsAmt
     <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<totalNetSalary
    <<endl;}
    void saveToFile(vector<Employee>v_emp){
    	ofstream fout("emp.txt");
    	if(!fout){
    		cout<<"Unable to open the data file emp.txt"<<endl;
    		return;
		}
		int recCount=0;
		for(vector<Employee>::iterator it=v_emp.begin();it!=v_emp.end();++it){
			fout<<it->empId<<","<<it->name<<","<<it->basicSalary<<","
			<<it->pf<<","<<it->healthInsAmt<<","<<it->email;
			recCount++;
			if(recCount!=v_emp.size()){
				fout<<endl;
			}
		}
		fout.close();
		cout<<"Total of "<<recCount<<"record saved successfully in the file"<<endl;
			}
	bool deleteEmployee(vector<Employee>& v_emp,int target){
		int index=search(v_emp,target);
		if(index==-1){
			return false;
		}
		cout<<"Target Employee with id:"<<target<<"found:"<<endl;
		printEmployee(v_emp[index]);
		cout<<"Are you sure to delete?Input 1 to delete 0 to exit"<<endl;
		int option;
		cin>>option;
		if(option==1){
			v_emp.erase(v_emp.begin()+index);
			return true;
		}
		return false;
	}
void doTask(vector<Employee>& v_emp,int option){
	int target,index;
	switch(option){
		case 1:addEmployee(v_emp);
			break;
		case 2:printEmployee(v_emp);
			break;
		case 3:cout<<"Enter employee id:"<<endl;
		cin>>target;
		index=search(v_emp,target);
		if(index==-1){
			cout<<"Employee with id:"<<target<<" does not exists."<<endl;
		}
		else{
			cout<<"Employee with id:"<<target<<" is found."<<endl;
			printEmployee(v_emp[index]);
		}
			break;
		case 4:cout<<"Enter emp_Id to delete:"<<endl;
		cin>>target;
		if(deleteEmployee(v_emp,target)){
			cout<<"Employee with id "<<target<<" deleted Successfully"<<endl;
			cout<<"As the record is deleted,please press option 5 to save the present state in file"<<endl;
		}
		else{
			cout<<"Employee with id "<<target<<" could not be deleted."<<endl;
		}
			break;
		case 5:saveToFile(v_emp);
		cout<<"Record Saved Successfully"<<endl;
			break;
		default:cout<<"Invalid Option"<<endl;
	}
	
	
}
int main() {
	vector<Employee> v_emp;
	readfile(v_emp);
	cout<<"Total"<<v_emp.size()<<"records read from the data file"<<endl;
	printMenu();
	bool quit=false;
	while(!quit){
		cout<<"Input your option:"<<endl;
		int option;
		cin>>option;
		if(option==6){
			quit=true;
		}
		else{
			doTask(v_emp,option);
		}
	}
	return 0;
}
