#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>
#include <string.h>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<map>
#include<string.h>
#include<stdlib.h>
#include<sstream>
#include<vector>
#include <algorithm>
using namespace std;
extern char* p;
extern char* pLast1;
extern char* pLast2;
extern char* pLast3;


extern char Token[100];
extern int TokenCount;
extern string symbol;
extern int num;
extern char chValue;
extern char stringValue[100];
extern char* IDName;
extern int End;
extern map<string,int>symbolNum;
extern int lineNum;
extern int errorNum;


int getsym();
void nextSym();
int getCode();
void traceSym();
int error(int e);

void program();
void constDefinition();
void varDefinition();
void functionDefinition();
void mainFunction();
void compoundStatement();
int parameterList();
int expression();
int term();
int factor();
void statement();
void statementList();
void assignmentStatement();
void conditionStatement();
void recurrentStatement();
void switchStatement();
void readStatement();
void printStatement();
void returnStatement();
int integer();
extern int level;
extern string expressionType;//计算表达式之后得到的表达式类型
extern string termType;//计算表达式之后得到的表达式类型
extern string factorType;//计算表达式之后得到的表达式类型

extern int paraNum;
extern int tempVarCount;
extern int labelCount;
extern string operand;

typedef struct node{
    string name;
    string kind;//var,const etc..
    string type;//char int void
    int value;
    int level;
    int length;//包括函数的参数个数
    int depth;//该函数运行栈的深度
}*sign;

extern sign symbolTable[300];
extern int tableLength;
extern int procedureIndex[50];
extern int procedureNum;
void deleteFunction();
int getLocation(string name,string kind);
void insertSymbolTable(string name,string kind,string type,int value,int level,int length);


typedef struct Node{
    string op;
    string var1;
    string var2;
    string var3;
}code;

extern code* midCode[1000];
extern int codeLength;
void generateConstCode(string op,string var1,int num,string var3);
void generateVarCode(string type,int length,string name);
void generateFunctionCode(string name);
void generateParameterCode(string type,string name);
void generateSetParaCode(string t);
void generateCallValueFunctionCode(string name,string V);
void generateCallFunctionCode(string name);
void generateExpressionCode(string op,string var1,string var2,string var3);
void generateAssignmentCode(string op,string var1,string var2,string var3);
void generateJumpCode(string jump,string a,string b,string c);
void generateLabelCode(string labelName);
void generateScanfCode(string name);
void generatePrintCode(string str,string name);
void generateReturnCode(string name);
void generateBeginCode();
void generateEndCode();

void insertSymbolTable(string name,string kind,string type,int value,int level,int length);


typedef struct node_{
    string name;
    string type;//char int
    string level;
    string length;
}MIPSsign;

extern MIPSsign* MIPSsymbolTable[1500];
extern int MIPStableLength;

void dag();
void generateMIPS();
void insertMIPSsign(string type,string name,int level,string length);
int getMIPSLocation(string name);
void returnAsm();
void getArrayAsm(string var1,string var2,string var3);
void assignAsm(string var1,string var3);
void assignArrayAsm(string var3,string var2,string var1);
void definitionGlobalAsm(string name,string value,string length);
string getAddress(string name);
void definitionAsm(string name,string value);
void calculateAsm(string op,string var1,string var2,string var3);
void JVar2VarAsm(string op,string a,string b,string c);
void JVar2ConAsm(string op,string a,string b,string c);

int killDeadCode();
void killChildExpression();
void mergeMidCode();
void deleteMidCode(int i);

#define blockVarNum 50

typedef struct node_1{
    string pre[10];
    string suc[10];
    int preLength;
    int sucLength;
    string label;
    string def[blockVarNum];
    string use[blockVarNum];
    string in[blockVarNum];
    string out[blockVarNum];
    int inChanged;
    int defLength;
    int useLength;
    int inLength;
    int outLength;

}block;

int calculateIn(string in[],
           string use[],
           int useLength,
           string out[],
           int outLength,
           string def[]
           ,int defLength);


typedef struct node_2{
    vector<string> var;
    vector<node_2*> father; 
    string value;  
    struct node_2* lChild=NULL;
    struct node_2* rChild=NULL;
}dagNode;

typedef struct node_3{
    vector<struct node_2*> elements;
}dagTree;



#endif
