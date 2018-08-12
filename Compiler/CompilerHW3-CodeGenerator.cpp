
#include<iostream>
#include<conio.h>
#include<string>
#include<fstream>
#include <vector>
#include <queue>
#include <Windows.h>
using namespace std;
class token {
public:
	string type;
	string name;
	int line;
	int ID;
	token(string s=""){
		type = "";
		name = s;
		ID = 0;
	}
	bool isDataType(){
		string allDatatypes[] = { "int", "double", "bool", "float", "char" };
		for (int i = 0; i < 5; i++)
			if (this->name == allDatatypes[i])
				return true;
		return false;
	}
};
queue<token>lookahead;

string logicalOp[11] ={"!","==",">","<",">=","<=","||","&&","|","&","!="};
string operators[11] ={"+","*","/","-","%","=","++","--","-=","--","+="};
string op[9]={"{","}",";",",","(",")","<<",">>",":"};
 bool keycheck(string s)
{
     string keyword[] ={"int","main()","float","if","double","for","static","else","auto","break","case","char","const","continue","void","while","volatile",
						"unsigned","union","typedef","switch","struct","static","sizeof","signed","short","return","long"};
     int d=0;
     if(!(s[0]>=97 && s[0]<=122))
                     return false;
      for(int i=0;i<28;i++)
      {
             if(s == keyword[i])
              {     
                     d = 1;
                     break;
              }
      }
     if(d == 1)
             return true;
     else
             return false;
} 
string opcheck(string s)
{
    
     int f1=0,f2=0,f=0;
    for(int i=0;i<9;i++)
    { 
		if(s == op[i])
        {  
			f = 1;
            break; 
		}
    }
    if(f == 1)
    { 
		if(s==op[0]||s==op[1])
			return "prace Op";
		if(s==op[2])
			return "semicolone";
		if(s==op[3])
			return "common";
		if(s==op[4])
			return "left paran";
		if(s==op[5])
			return "right paran";
		if(s==op[6])
			return "out operator";
		if(s==op[7])
			return "in operator";
		if(s==op[8])
			return "colone Op";
	}
    else
    { 
		for(int i=0;i<11;i++)
         {       
             if(s == logicalOp[i])
             {
                    f1 = 1;
                    break;
             }
         }
         if(f1 == 1)
         {
			 return "logicalOperator"; 
		 }
		 else
         {
			for(int i=0;i<11;i++)
			 {       
				 if(s == operators[i])
				 {
				        f2 =1;
				        break;  
				 }
			 }
          
			  if(f2 == 1) 
				  return "mathOperator";
			  else  
				  return "error";
		}
    }
}
int contrain ( string* s,char ch, int size)
{
	char * c=&ch;
	
	string search=c;
	for ( int i=0;i<size;i++)
		if(s[i]==search)
			return 1;
	return 0;
}         
int ischar(char c)
{
     if((c>=65 && c<=90) || (c>=97 && c<=122))
		return 1;
    else
		return 0; 
}          
int isnum(char c)
{
    if(c>=48 && c<=57)
		return 1;
    else
		return 0;
}   
int isnums(string str)
{
    int flag=0;
    for(int i = 0;i<str.length();i++)
    {
         if(!isnum(str[i]))
         {
            if(str[i] != 46) 
            {
                flag=1;
                break;
            }
         }
    }
    
    if(flag == 1)
            return 0;
    else
            return 1;
}
int isidentifier(string s)
{
	int f =0;
	for(int i=1;i<s.length();i++)
	{
		if(!ischar(s[i]))
		{
			if(!isnum(s[i]))
			{
				if(s[i] != 95)
				{
					if(s[i] == 91)
					{
						i++;
						for(;s[i]!= 93;i++)
						{
							if(!isnum(s[i]))
							{
								f =1;   
								break;
							}
						}
					}
					else
					{
						f = 1;
					}
					if(f ==1)
						break;
				}
			}
		
		}
	}
      
   return f;
}
void makeSpace ( string & s)
{
	string withSpace="";

	for ( int i=0;i<s.length()-1;i++)
	{
		
		while(s[i]!=' ' &&!contrain(op,s[i],9)&&!contrain(operators,s[i],11)&&!contrain(logicalOp,s[i],11))
		{
			withSpace+=s[i++];
		}
		char c1[3];
		if(i+1<s.size())
		{
			 c1[0]=s[i];
			 c1[1]=s[i+1];
			 c1[2]=NULL;
		}
		else
		{
			 c1[0]=NULL;
		}
		string two=c1;
		if(i+1<s.length()&&(two=="=="||two==">="||two=="<="||two=="++"||two=="--"||two=="-="||two=="+="||two=="<<"||two==">>"||two=="+="||two=="!="))
		{
			withSpace+=" ";
			withSpace+=two;
			withSpace+=" ";
			i++;
			continue;
		}
		else if(two=="//")
		{
			s=withSpace;
			return;
		}

		withSpace+=" ";
		if(s[i]!=' ')
		{
			withSpace+=s[i];
			withSpace+=" ";
		}
	}
	s=withSpace;
}                                                   
int lexical(string input,string output)
{ 
	ifstream ifs(input.c_str());
	ofstream ofs(output.c_str());
    int q=0,f=0;
    bool check;
    string str="",strch,strline;
	 ofs<<"Token\t\t\t" << "Token Type\t\t\t"<<"start\t\t"<<"length\t\t\t"<<"Line\n"; 
	    ofs<<"----------------------------------------------------------------------------------------------------------------\n";
    while(!ifs.eof())
    {
		getline(ifs,strline);
		q++;//line
 
		int start;
		strline = strline + " ";
		makeSpace(strline);
		strline = strline + " ";
	
		for(int j=0;j<strline.length();j++)
		{       
			if(strline[j] ==' ' || strline[j]=='\t'||strline[j]=='\"')
			{     
				if(strline[j]=='\"')
				{
					str+=strline[j++];
					while(strline[j++]!='\"')
					str+=strline[j];
					ofs<<str<<"\t\t\tstring\t\t\t"<<abs((int)str.size()-j)+1<<"\t\t\t"<<str.size()<<"\t\t\t"<<q<<"\n";
					str="";
					token t(str);
					t.line=q;
					lookahead.push(t);

				}
				if(str != "")
				{
					if(ischar(str[0]))
					{
						check = keycheck(str);
						if(check)
						{
							ofs<<str<<"\t\t\tkey word\t\t\t"<<abs((int)str.size()-j)+1<<"\t\t\t"<<str.size()<<"\t\t\t"<<q<<"\n";  
							token t(str);
							t.line=q;
							t.type="identifier";
							lookahead.push(t);
						}        
						else
						{
                                      
							f = isidentifier(str);
                                        
							if(f == 1)
							{
									ofs<<str<<"\t\t\terror\t\t\t"<<abs((int)str.size()-j)+1<<"\t\t\t"<<str.size()<<"\t\t\t"<<q<<"\n";  
									f = 0;
							}
							else
							{
								ofs<<str<<"\t\t\tidentifier\t\t\t"<<abs((int)str.size()-j)+1<<"\t\t\t"<<str.size()<<"\t\t\t"<<q<<"\n";
								token t(str);
								t.line=q;
								t.type="identifier";
								lookahead.push(t);
							}
						}
					}
					else
					{
						if(isnum(str[0]))
						{
							if(isnums(str))
							{
								ofs<<str<<"\t\t\tnumber\t\t\t\t"<<abs((int)str.size()-j)+1<<"\t\t\t"<<str.size()<<"\t\t\t"<<q<<"\n";  
								token t(str);
								t.line=q;
								t.type="number";
								lookahead.push(t);
							}
							else
								ofs<<str<<"\t\t\terror\t\t\t"<<abs((int)str.size()-j)+1<<"\t\t\t"<<str.size()<<"\t\t\t"<<q<<"\n";  
						}
						else
						{
							strch = opcheck(str);
							if(strch == "error")
									ofs<<str<<"\t\t\t"<<strch<<"\t\t\t"<<abs((int)str.size()-j)+1<<"\t\t\t"<<str.size()<<"\t\t\t"<<q<<"\n";  
							else
							{
								ofs<<str<<"\t\t\t"<<strch<<"\t\t\t"<<abs((int)str.size()-j)+1<<"\t\t\t"<<str.size()<<"\t\t\t"<<q<<"\n";  
								token t(str);
								t.line=q;
								t.type="";
								lookahead.push(t);
							}
						}
					} 
                      
				}
                      
				str="";  
			}
			else
			{
				str=str+strline[j];    
			}    
		}       
    }
    return 0;
}
class Parser
{
	public:

	token loAh;
	int error;
	int nbLabels;
	void updateLabel()
	{
		cout << "lb" << ++nbLabels << endl;

	}
	int Lexical()
	{
		if (lookahead.empty()||lookahead.size()==1)
			return -1;
		lookahead.pop();
		loAh = lookahead.front();
		return 1;
	}

	Parser(){
		error=0;
		nbLabels=0;
		loAh = lookahead.front(); // loAh stands for look Ahead.
		MainNFun();
	}

	void MainNFun()
	{
		if (loAh.name == "void")
		{
			Lexical();
			if (loAh.name == "main")
			{
				Lexical();
				if (loAh.name == "(")
				{
					Lexical();
					if (loAh.name == ")")
					{
						Lexical();
						compoundStFun(); // fun begins here :)
						if (Lexical() != -1)
						{
							cerr << "Line (" << loAh.line << ") , error : you are writing out of range\n";
							cout << "Not Valid\n";
							system("pause");
							exit(1);
						}
					}
					else 
					{ 
						cerr << "Line (" << loAh.line << ") , error : expected right parentheses\n";
						cout << "Not Valid\n"; 
						system("pause");
						exit(1); 
					}
				}
				else 
				{ 
					cerr << "Line (" << loAh.line << ") , error : expected left parentheses\n"; 
					cout << "Not Valid\n";
					system("pause"); 
					exit(1); 
				}
			}
			else 
			{ 
				cerr << "Line (" << loAh.line << ") , error : expected main\n";
				cout << "Not Valid\n"; 
				system("pause");
				exit(1);
			}


		}
	}
	void compoundStFun(){
		if (loAh.name == "{")
		{
			Lexical();
			moreStmtFun();
			if (loAh.name == "}")
				Lexical();
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected a }\n";
				cout << "Not Valid\n"; 
				system("pause");
				exit(1);
			}
		}
		else 
		{ 
			cerr << "Line (" << loAh.line << ") , error : expected left brace\n";
			cout << "Not Valid\n"; 
			system("pause");
			exit(1);
		}
	}


	void expFun()
	{
		int flag=-1;
		string id;
		if(loAh.name=="break")
		{
			Lexical();
			return;
		}
		if (keycheck(loAh.name) || loAh.type=="identifier"|| loAh.type=="number")
		{
			if(keycheck(loAh.name))
				Lexical();
			if(loAh.type=="identifier")
			{
				flag=0;
				id=loAh.name;
			}
			else
				cout << "push " << loAh.name << " \n";

			
		
			if (loAh.type == "identifier"||loAh.type == "number")
			{
				string tempOfID = loAh.name;
				Lexical();
				if(flag==0&&(loAh.name != "="&&loAh.name != "++"&&loAh.name != "+="&&loAh.name != "*="&&loAh.name != "-="&&loAh.name != "--"&&loAh.name != "/="))
					cout << "rvalue " << id << " \n";
				else if(flag==0)
					cout << "lvalue " << id << " \n";
				if (loAh.name == "+")
				{
					Lexical();
					expFun();
					cout << "+\n";
				
				}
				else if (loAh.name == "-")
				{
					Lexical();
					expFun();
					cout << "-\n";
				}
				else if (loAh.name == "*")
				{
					Lexical();
					expFun();
					cout << "*\n";
				}
				else if (loAh.name == "/")
				{
					Lexical();
					expFun();
					cout << "/\n";
				}
				else if (loAh.name == "%")
				{
					Lexical();
					expFun();
					cout << "%\n";
				}
				else // as an assignment statement
				{
					if (loAh.name == "=")
					{
						Lexical();
						expFun();
						cout << "=\n";
									
					}
					else if (loAh.name == "++")
					{
						Lexical();
						cout << "rvalue " << tempOfID <<" \n";
						cout << "push 1 \n+\n=\n";
					}
					else if (loAh.name == "--")
					{
						Lexical();
						cout << "rvalue " << tempOfID << "\n";
						cout << "push 1 \n-\n=\n";
					}

					else if (loAh.name == "*=")
					{
						cout << "rvalue " << tempOfID << " \n";
						Lexical();
						expFun();
						cout << "*\n";
						cout << "=\n";
					}
					else if (loAh.name == "/=")
					{					
						cout << "rvalue" << tempOfID << "\n";
						Lexical();
						expFun();
						cout << "/\n";
						cout << "=\n";
					}
					else if (loAh.name == "+=")
					{				
						cout << "rvalue " << tempOfID << " \n";
						Lexical();
						expFun();
						cout << "+\n";
						cout << "=\n";
					}
					else if (loAh.name == "-=")
					{
						cout << "rvalue " << tempOfID << " \n";
						Lexical();
						expFun();
						cout << "-\n";
						cout << "=\n";
					}

				}
				return;
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expression must start with identifier or any atomic data\n";
				cout << "Not Valid\n"; 
				system("pause");
				exit(1);
			}
			
			if (loAh.name == "+")
			{
				Lexical();
				expFun();
			}
			else if ( loAh.type=="identifier")
			{
				Lexical();
				expFun();
			}
			else if (loAh.name == "-")
			{
				Lexical();
				expFun();
			}
			else if (loAh.name == "*")
			{
				Lexical();
				expFun();
			}
			else if (loAh.name == "/")
			{
				Lexical();
				expFun();
			}
			else if (loAh.name == "%")
			{
				Lexical();
				expFun();
			}
			return;
		}

		if (loAh.name == "(")
		{
			Lexical();
			expFun();
			if (loAh.name == ")")
				Lexical();
			else 
			{
				cout << "Error: line " << loAh.line << ", Expected a closing paranthesese.\nNot Valid\n";
				system("pause");
				exit(1);
			}
			if (loAh.name == "+")
			{
				Lexical();
				expFun();

			}
			else
				if (loAh.name == "-")
				{
					Lexical();
					expFun();
				}
			else if (loAh.name == "*")
			{
				Lexical();
				expFun();
			}
			else if (loAh.name == "/")
			{
				Lexical();
				expFun();
			}
			else if (loAh.name == "%")
			{
				Lexical();
				expFun();	
			}
			return;
		}

		if (loAh.type == "charecter")
		{
			Lexical();
			//simply get the integer from the char.
			if (loAh.name == "+")
			{
				Lexical();
				expFun();
			}
			else
				if (loAh.name == "-")
				{
					Lexical();
					expFun();
				}
				else if (loAh.name == "*")
				{
					Lexical();
					expFun();
				}
				else if (loAh.name == "/")
				{
					Lexical();
					expFun();
				}
				else if (loAh.name == "%")
				{
					Lexical();
					expFun();
				}
			return;
		}
	}//function
	void stmtFun()
	{
		if (loAh.name == "if")
			ifStmtFun();
		else if (loAh.name == "while")
			whileStmtFun();
		else if (loAh.name == "switch")
			switchStmtFun();
		else if (loAh.name == "do")
			doStmtFun();
		else if (loAh.name == "for")
			forStmtFun();
		else if (loAh.type == "identifier")
		{						
			expFun();
			if (loAh.name == ";")
				Lexical();
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected a ;\n"; 
				cout << "Not Valid\n"; 
				system("pause");
				exit(1);
			}
		}
		else if (loAh.name == ";")
			Lexical();
		else if (loAh.name == "{")
			compoundStFun();
		else
		{

			cerr << "Line (" << loAh.line << ") , error : expected a statement\n";
			cout << "Not Valid\n";
			system("pause"); 
			exit(1);
		}

	}
	void preList(){
		if (loAh.type == "identifier")
		{
			cout << "lvalue " << loAh.name << " \n";
			Lexical();
			if (loAh.name == "=")
			{
				Lexical();
				expFun();
				cout << "=\n";
				if (loAh.name == ",")
				{
					Lexical();
					if (loAh.name == "int")
					{
						Lexical();
						preList();
					}
					else
					{
						cerr << "Line (" << loAh.line << ") , error : for loop must start with int in first statement \n"; 
						cout << "Not Valid\n"; 
						system("pause");
						exit(1);
					}
				}
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error\n : expected an identifier";
			cout << "Not Valid\n"; 
			system("pause");
			exit(1);
		}
	}


	void postList()
	{
		expFun();
		if (loAh.name == ",")
		{
			Lexical();
			postList();

		}
	}


	void forStmtFun()
	{
		if (loAh.name == "for")
		{
			Lexical();
			if (loAh.name == "(")
			{
				Lexical();
				if (loAh.name == "int")
				{
					Lexical();
					preList();
				}
				else if (loAh.type == "identifier")
				{
					preList();
				}
				else
				{
					cerr << "Line (" << loAh.line << ") , error : for loop must start with int data type in first segement\n";
					cout << "Not Valid\n";
					system("pause");
					exit(1);
				}
					if (loAh.name == ";")
					{
						Lexical();
						cout << "label "; updateLabel();
						int topLb = nbLabels;
						condFunction();
						cout << "gofalse "; updateLabel();
						int falsLb = nbLabels;
						if (loAh.name == ";")
						{
							Lexical();
							cout << "goto "; 
							updateLabel();
							int stmtBegining = nbLabels;
							cout << "label "; 
							updateLabel();
							int postListStarting = nbLabels;
							postList();
							cout << "goto lb" << topLb << endl;
							if (loAh.name == ")")
							{
								Lexical();
								cout << "label lb" << stmtBegining << endl;
								stmtFun();
								cout << "goto lb" << postListStarting << endl;
								cout << "label lb" << falsLb << endl;
							}
							else
							{
								cerr << "Line (" << loAh.line << ") , error : expected a right parentheses\n";
								cout << "Not Valid\n";
								system("pause");
								exit(1);
							}
						}
						else
						{
							cerr << "Line (" << loAh.line << ") , error : expected a ;\n"; 
							cout << "Not Valid\n"; 
							system("pause");
							exit(1);
						}
					}
					else
					{
						cerr << "Line (" << loAh.line << ") , error : expected a ;\n"; 
						cout << "Not Valid\n"; 
						system("pause");
						exit(1);
					}
				
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected a left parentheses\n"; 
				cout << "Not Valid\n";
				system("pause");
				exit(1);
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error : expected for in for loop\n"; 
			cout << "Not Valid\n"; 
			system("pause");
			exit(1);
		}

	}
	void doStmtFun(){
		cout << "label "; updateLabel();
		int doLable = nbLabels;
		if (loAh.name == "do")
		{
			Lexical();
			stmtFun();
			if (loAh.name == "while")
			{
				Lexical();
				if (loAh.name == "(")
				{
					Lexical();
					condFunction();
					if (loAh.name == ")")
					{
						cout << "gotrue lb" << doLable << endl;
						Lexical();
						if (loAh.name == ";")
							Lexical();
						else
						{
							cerr << "Line (" << loAh.line << ") , error : expected a ;\n";
							cout << "Not Valid\n";
							system("pause");
							exit(1);
						}
					}
					else
					{
						cerr << "Line (" << loAh.line << ") , error\n : expected a )";
						cout << "Not Valid\n";
						system("pause");
						exit(1);
					}

				}
				else
				{
					cerr << "Line (" << loAh.line << ") , error : expected a (\n";
					cout << "Not Valid\n";
					system("pause");
					exit(1);
				}
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : do statement must end up with while part\n";
				cout << "Not Valid\n";
				system("pause");
				exit(1);
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error : expected do in do statement\n";
			cout << "Not Valid\n";
			system("pause");
			exit(1);
		}

	}
	void switchStmtFun(){
		if (loAh.name == "switch")
		{
			Lexical();
			if (loAh.name == "(")
			{
				Lexical();
				expFun();
				if (loAh.name == ")")
				{
					Lexical();
					bracedCasesFun();
				}
				else
				{
					cerr << "Line (" << loAh.line << ") , error : expected a )\n"; 
					cout << "Not Valid\n"; 
					system("pause");
					exit(1);
				}
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected a (\n";
				cout << "Not Valid\n";
				system("pause");
				exit(1);
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error : expected switch in switch statement\n";
			cout << "Not Valid\n"; 
			system("pause");
			exit(1);
		}
	}
	void bracedCasesFun()
	{
		if (loAh.name == "{")
		{
			Lexical();
			casesFun();
			if (loAh.name == "}")
			{
				Lexical();
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected a }\n"; 
				cout << "Not Valid\n";
				system("pause");
				exit(1);
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error : expected a {\n";
			cout << "Not Valid\n";
			system("pause");
			exit(1);
		}
	}

	
	void casesFun()
	{
		if (loAh.name == "case")
		{
			caseFun();
			casesFun();
		}
		if (loAh.name == "default")
		{
			defaultFun();
			casesFun();
		}
	}
	void defaultFun()
	{

		if (loAh.name == "default")
		{
			Lexical();
			if (loAh.name == ":")
			{
				Lexical();
				if (loAh.name != "}" && loAh.name != "case")
					stmtFun();
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected a :\n";
				cout << "Not Valid\n";
				system("pause");
				exit(1);
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error\n"; 
			cout << "Not Valid\n"; 
			system("pause");
			exit(1);
		}
	}

	void orderedStmtFun()
	{
		if (loAh.name != "}" && loAh.name != "case" && loAh.name != "default")
		{
			stmtFun();
			orderedStmtFun();
		}
	}
	void caseFun(){

		if (loAh.name == "case")
		{
			Lexical();
			//cout << "dup\n";
			expFun();
			cout << "==\n";
			cout << "goFalse "; updateLabel();
			int nextCaseLabel = nbLabels;

			if (loAh.name == ":")
			{
				Lexical();
				orderedStmtFun();
				cout << "label lb" << nextCaseLabel << endl;
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected a :\n";
				cout << "Not Valid\n";
				exit(1);
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error\n";
			cout << "Not Valid\n"; 
			exit(1);
		}
	}


	void whileStmtFun()
	{
		cout << "label ";
		updateLabel();
		int beforeWhileLb = nbLabels;
		if (loAh.name == "while")
		{
			Lexical();
			if (loAh.name == "(")
			{
				Lexical();
				condFunction();
				if (loAh.name == ")")
				{
					Lexical();
					cout << "goFalse ";
					updateLabel();
					int toFalseLabel = nbLabels;
					stmtFun();
					cout << "goto  lb" << beforeWhileLb << endl << "label lb" << toFalseLabel << endl;
				}
				else
				{
					cerr << "Line (" << loAh.line << ") , error : expected a )\n";
					cout << "Not Valid\n"; 
					system("pause");
					exit(1);
				}
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected a (\n"; 
				cout << "Not Valid\n"; 
				system("pause");
				exit(1);
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error\n"; 
			cout << "Not Valid\n"; 
			system("pause");
			exit(1);
		}
	}

	void ifStmtFun(){
		if (loAh.name == "if")
		{
			Lexical();
			if (loAh.name == "(")
			{
				Lexical();
				condFunction();
				if (loAh.name == ")")
				{
					Lexical();
					cout << "gofalse "; 
					updateLabel();
					int falseLabel = nbLabels;
					stmtFun();
					cout << "goto ";
					updateLabel();
					int afterElseLabel = nbLabels;
					cout << "label lb" << falseLabel << endl;

					if (loAh.name == "else")
					{
						elseFun();
					}
					cout << "label lb" << afterElseLabel << endl;
				}
				else
				{
					cerr << "Line (" << loAh.line << ") , error : expected a )\n";
					cout << "Not Valid\n"; 
					system("pause");
					exit(1);
				}
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected a (\n";
				cout << "Not Valid\n"; 
				system("pause");
				exit(1);
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error\n";
			cout << "Not Valid\n";
			system("pause");
			exit(1);
		}
	}
	void elseFun()
	{
		if (loAh.name == "else")
		{
			Lexical();
			stmtFun();
		}

	}

	void condFunction()
	{
		if (loAh.type == "identifier" || loAh.type == "number" )
		{
			token current = loAh;
			if (loAh.type == "identifier")
			{
				cout << "rvalue " << loAh.name <<" \n";
			}
			else
				cout << "push " << loAh.name << " \n";
			Lexical();
			if(loAh.name!=")")
				smPrFun(current);
			else
			{
				cout<<"push 0\n";
				cout<<"!=\n";
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error : expected an identifier or a number.\n";
			cout << "Not Valid\n"; 
			system("pause");
			exit(1);
		}
	}
	bool isLogicalOperator(){
		string logicalOperator[] = { "<", ">", "==", "<=", ">=", "!=", "||", "&&" };
		for (int i = 0; i < 7; i++)
			if (loAh.name == logicalOperator[i])
				return true;
		return false;
	}
	
	void smPrFun(token &leftP)
	{
		if (isLogicalOperator())
		{
			string logOp = loAh.name;
			Lexical();
			if (loAh.type == "identifier" || loAh.type == "charecter" || loAh.type == "integer" || loAh.type == "number")
			{

				if (loAh.type == "identifier")
					cout << "rvalue " << loAh.name << " \n";
				else
					cout << "push " << loAh.name << " \n";

				cout << logOp << endl;
				Lexical();
			}
			else
			{
				cerr << "Line (" << loAh.line << ") , error : expected an identifier or a number.\n";
				cout << "Not Valid\n";
				system("pause");
				exit(1);
			}
		}
		else
		{
			cerr << "Line (" << loAh.line << ") , error : expected logical operator.\n";
			cout << "Not Valid\n";
			system("pause");
			exit(1);
		}

	}

	void moreStmtFun()
	{
		if (loAh.name == "}")
			return;

	stmtFun();
	moreStmtFun();

	}
};
void main(){
	string input;
	string output;
	cout<<"enter input filename/path , i.e: input.txt\nfilename: ";
	cin>>input;
	cout<<"enter output filename/path , i.e: output.txt\nfilename: ";
	cin>>output;
	lexical(input,output);
	for ( int i=0;i<12;i++)
	{
		system("cls");
		cout<<"lexical:\n\nplease wait";
		if(i%3==0)
			cout<<".";
		else if (i%3==1)
			cout<<"..";
		else
			cout<<"...";
		Sleep(400);
	}
	for ( int i=0;i<12;i++)
	{
		system("cls");
		cout<<"lexical:\n\nplease wait";
		cout<<"...";
		cout<<endl<<endl;
		cout<<"file of token has been completed.. "<<endl;
		cout<<"parsing:\n\nplease wait";
		if(i%3==0)
			cout<<".";
		else if (i%3==1)
			cout<<"..";
		else
			cout<<"...";
		Sleep(400);
	}
	cout<<endl;
	Parser p;
	
	
	cout<<"\nparse done successfully (Valid)"<<endl;
    system("pause");

}