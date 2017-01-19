#include "global.h"
int level=0;

int tempVarCount=0;
string returnType="void";//char int void
int returnNum=0;
string operand;
string expressionType=string("INT");
string termType=string("INT");
string factorType=string("INT");
int labelCount=0;
int errorNum=0;

ofstream compileLog;
void arriveIntCharVoid(){
    while(1){
        nextSym();
        if(symbol=="INT"||symbol=="VOID"||symbol=="CAHR")
            break;
    }
}

void arriveSemi(){
    while(1){
        if(symbol=="SEMI")
            break;
        nextSym();
    }
    nextSym();
}
void arriveAtSemi(){
    while(1){
        if(symbol=="SEMI")
            break;
        nextSym();
    }
}


void arriveRBRACE(){
    while(1){
        if(symbol=="RBRACE")
            break;
        nextSym();
    }
    nextSym();
}

void arriveLBRACE(){
    while(1){
        if(symbol=="LBRACE")
            break;
        nextSym();
    }
}
//RPAR
void arriveRPAR(){
    while(1){
        if(symbol=="RPAR")
            break;
        nextSym();
    }
}

//RPAR
void arriveLPAR(){
    while(1){
        if(symbol=="LPAR")
            break;
        nextSym();
    }
}

void arriveStatement(){
    while(1){
        int la=symbolNum[symbol];
        if(symbolNum[symbol]==9||symbolNum[symbol]==11||
        symbolNum[symbol]==34||symbolNum[symbol]==1||
        symbolNum[symbol]==15||symbolNum[symbol]==16||
        symbolNum[symbol]==29||symbolNum[symbol]==12||
        symbolNum[symbol]==17)
            break;
        nextSym();
    }

}

void program(){

    compileLog.open("log.txt");
    nextSym();
    while(1){
    if(symbol.compare("CONST")==0){
        constDefinition();
    }
    if(symbol.compare("INT")==0||symbol.compare("CHAR")==0){
        nextSym();
        if(symbol.compare("ID")==0){
            nextSym();
            if(symbol.compare("LPAR")==0){
                traceSym();
                traceSym();
                traceSym();
                nextSym();
                functionDefinition();
                mainFunction();
                return;
            }
            else if(symbol.compare("SEMI")==0||
                    symbol.compare("COMMA")==0||
                    symbol.compare("LBRACKET")==0){
                traceSym();
                traceSym();
                traceSym();
                nextSym();
                varDefinition();
                if(symbol.compare("INT")==0||symbol.compare("CHAR")==0){
                    functionDefinition();
                    mainFunction();
                    return;
                }
                else if(symbol.compare("VOID")==0){
                    nextSym();
                    if(symbol.compare("MAIN")==0){
                        traceSym();
                        traceSym();
                        nextSym();
                        mainFunction();
                        return;
                    }
                    else if(symbol.compare("ID")==0){
                        traceSym();
                        traceSym();
                        nextSym();
                        functionDefinition();
                        mainFunction();
                        return;
                    }
                    else
                        error(13);//13 期望一个标识符或者一个main关键字
                    arriveIntCharVoid();
                    continue;
                }
                else
                    error(14);//14 期盼一个类型标识符
                arriveIntCharVoid();
                continue;
            }
            else
                error(15);//15 需要一个;或,或[
            arriveIntCharVoid();
            continue;
        }
        else
            error(13);//13 期望一个标识符或者一个main关键字
        arriveIntCharVoid();
        continue;
    }
    if(symbol.compare("VOID")==0){
        nextSym();

        if(symbol.compare("MAIN")==0){
            traceSym();
            traceSym();
            nextSym();
            mainFunction();
            return;
        }
        else if(symbol.compare("ID")==0){
            traceSym();
            traceSym();
            nextSym();
            functionDefinition();
            mainFunction();
            return;
        }
        else
            error(13);//13 期望一个标识符或者一个main关键字
        arriveIntCharVoid();
        continue;
    }
    error(14);//14 期盼一个类型标识符
arriveIntCharVoid();
    }

}
void constDefinition(){
    while(symbol.compare("CONST")==0){
        nextSym();
        string type;
        if(symbol.compare("INT")==0){
            type=symbol;
            nextSym();
            if(symbol.compare("ID")==0){
                string name(IDName);  //小心指针被修改
                nextSym();
                if(symbol.compare("EQUAL")==0){
                    nextSym();
                    int neg=1;
                    int Num;
                    if(symbol.compare("PLUS")==0||symbol.compare("MINUS")==0){
                        if(symbol.compare("MINUS")==0)
                            neg=-1;
                        nextSym();
                    }
                    if(symbol.compare("NUM")==0&&
                    (*pLast1!='0'||p-pLast1==1)){
                        Num=neg*num;
                    }
                    else{
                        error(16);  //16 不合法的数字!可能含有非数字字符或者前导零
                        arriveSemi();
                        continue;
                    }
                    compileLog<<"const  "<<name<<" "<<type<<" "<<Num<<endl;
                    insertSymbolTable(name,string("CONST"),type,Num,level,0);
                    generateConstCode(string("CONST"),type,Num,name);
                }
                else{
                    error(17);//17 常量的定义缺少=号
                    arriveSemi();
                    continue;
                }
            }
            else{
                error(13);//13 期望一个标识符或者一个main关键字
                arriveSemi();
                continue;
            }
            nextSym();
            int flag=0;
            while(symbol.compare("COMMA")==0){
                nextSym();
                if(symbol.compare("ID")==0){
                   string name(IDName);  //小心指针被修改
                   nextSym();
                    if(symbol.compare("EQUAL")==0){
                        nextSym();
                        int Num=integer();
                        compileLog<<"const  "<<name<<" "<<type<<" "<<Num<<endl;
                        insertSymbolTable(name,string("CONST"),type,Num,level,0);
                        generateConstCode(string("CONST"),type,Num,name);
                  }
                 else{
                        error(17);//17 常量的定义缺少=号
                        flag=1;
                        break;
                 }
             }
            else{
                error(13);//13 期望一个标识符或者一个main关键字
                flag=1;
                break;
            }
            }
            if(flag==1){
                arriveSemi();
                continue;
            }
        }
        else if(symbol.compare("CHAR")==0){
            type=symbol;
            nextSym();
            if(symbol.compare("ID")==0){
                string name(IDName);  //小心指针被修改
                nextSym();
                int value;
                if(symbol.compare("EQUAL")==0){
                    nextSym();
                    if(symbol.compare("CHARVALUE")==0){
                        value=chValue;
                    }
                    else
                        error(18);//18 char类型的常量只能用字符来赋值
                    compileLog<<"const  "<<name<<" "<<type<<endl;
                    insertSymbolTable(name,string("CONST"),type,value-0,level,0);
                    generateConstCode(string("CONST"),type,value-0,name);
                }
                else{
                    error(17);//17 常量的定义缺少=号
                    arriveSemi();
                    continue;
                }
            }
            else{
                error(13);//13 期望一个标识符或者一个main关键字
                arriveSemi();
                continue;
            }
            nextSym();
            int flag=0;
            while(symbol.compare("COMMA")==0){
                nextSym();
                if(symbol.compare("ID")==0){
                   string name(IDName);  //小心指针被修改
                   nextSym();
                   int value;
                   if(symbol.compare("EQUAL")==0){
                       nextSym();
                       if(symbol.compare("CHARVALUE")==0){
                       value=chValue;
                    }
                    else
                        error(16); //16 不合法的数字!可能含有非数字字符或者前导零
                    compileLog<<"const  "<<name<<" "<<type<<endl;
                    insertSymbolTable(name,string("CONST"),type,value-0,level,0);
                    generateConstCode(string("CONST"),type,value-0,name);
                }
                else{
                    error(17);//17 常量的定义缺少=号
                    flag=1;
                    break;
                }
             }
            else{
                error(13);//13 期望一个标识符或者一个main关键字
                flag=1;
                break;
            }
            nextSym();
            }
            if(flag==1){
                arriveSemi();
                continue;
            }
        }
        else{
            error(14);//14 期盼一个类型标识符
            arriveSemi();
            continue;
        }
        if(symbol.compare("SEMI")!=0)
            error(18);//18 缺少;
        nextSym();
    }
}
void varDefinition(){
    while(symbol.compare("INT")==0||symbol.compare("CHAR")==0){
        string type;
        type=symbol;
        nextSym();
        if(symbol.compare("ID")==0){
            string name(IDName);  //小心指针被修改
            
            nextSym();
            if(symbol.compare("LBRACKET")==0){
                nextSym();
                if(symbol.compare("NUM")==0&&(*pLast1)!=0){
                    int length=num;
                    nextSym();
                    if(symbol.compare("RBRACKET")!=0){
                        error(26);//19 需要一个]
                        arriveSemi();
                        continue;
                    }
                compileLog<<"var array"<<name<<" "<<type<<endl;
                insertSymbolTable(name,string("ARRAY"),type,0,level,length);
                generateVarCode(type,length,name);

                nextSym();
                }
                else{
                    error(16);  //16 不合法的数字!可能含有非数字字符或者前导零
                    arriveSemi();
                    continue;
                }
            }
            else if(symbol.compare("LPAR")==0){
                traceSym();
                traceSym();
                traceSym();
                nextSym();
                return;
            }
            else{
                insertSymbolTable(name,string("VAR"),type,0,level,0);
                generateVarCode(type,0,name);
                compileLog<<"var"<<name<<" "<<type<<endl;
            }
        }
        else{
            error(13);//13 期望一个标识符或者一个main关键字
            arriveSemi();
            continue;
        }
        int flag=0;
        while(symbol.compare("COMMA")==0){
            nextSym();
            if(symbol.compare("ID")==0){
            string name(IDName);  //小心指针被修改
            nextSym();
            if(symbol.compare("LBRACKET")==0){
                nextSym();
                if(symbol.compare("NUM")==0&&(*pLast1)!=0){
                    int length=num;
                    nextSym();
                    if(symbol.compare("RBRACKET")!=0){
                        error(26);//19 需要一个]
                        flag=1;
                        break;
                    }
                insertSymbolTable(name,string("ARRAY"),type,0,level,length);
                generateVarCode(type,length,name);
                compileLog<<"var array "<<name<<" "<<type<<endl;
                nextSym();
                }
                else{
                    error(16);   //16 不合法的数字!可能含有非数字字符或者前导零
                    flag=1;
                    break;
                }
            }
            else{
                insertSymbolTable(name,string("VAR"),type,0,level,0);
                generateVarCode(type,0,name);
                compileLog<<"var "<<name<<" "<<type<<endl;
            }
             }
            else{
                error(13);//13 期望一个标识符或者一个main关键字
                flag=1;
                break;
            }
            }
        if(flag==1){
            arriveSemi();
            continue;
        }
        if(symbol.compare("SEMI")!=0)
            error(18);//18 缺少;
        nextSym();
    }
}
void functionDefinition(){

    while(symbol.compare("INT")==0
    ||symbol.compare("CHAR")==0
    ||symbol.compare("VOID")==0){
        level++;
        string type=symbol;
        returnType=type;
        nextSym();
        if(symbol.compare("MAIN")==0){
            traceSym();
            traceSym();
            nextSym();
            level--;
            return;
        }
        if(symbol.compare("ID")==0){
            nextSym();
            string name(IDName);
            if(symbol.compare("LPAR")==0){
                compileLog<<type<<"  "<<name<<endl;
                nextSym();
                generateBeginCode();
                generateFunctionCode(name);//在生成para之前先生成label 方便转换成汇编
                int paraNum=parameterList();
                if(symbol.compare("RPAR")==0){
                    nextSym();
                    insertSymbolTable(name,string("FUNCTION"),type,-1,level-1,paraNum);
//                    generateFunctionCode(name);
                    if(symbol.compare("LBRACE")==0){
                       ;
                    }
                    else{
                        error(21);//21 缺少一个{
                        arriveRBRACE();
                        continue;
                    }
                }
                else
                    error(20);//20 缺少一个)
            }
            else
                error(22);//22 缺少一个(
        }
        else
            error(13);//13 期望一个标识符或者一个main关键字
    arriveLBRACE();
    compoundStatement();//复合语句例外，在进入之前没有预读一个单词，因为它的出现都是确定的
    if(symbol.compare("RBRACE")!=0){
        error(19); //19 缺少一个}
        arriveIntCharVoid();
        continue;
    }
    nextSym();
    deleteFunction();
    generateEndCode();
    level--;
    if(returnNum==0&&returnType!="VOID")
        error(39);
    returnNum=0;
    }
}
void mainFunction(){
    level++;
    if(symbol.compare("VOID")==0){
        
        returnType=symbol;
        nextSym();
        if(symbol.compare("MAIN")==0){
            generateBeginCode();
            generateFunctionCode(string("main"));
            compileLog<<"main function resolved!"<<endl;
            nextSym();
            insertSymbolTable(string("main"),string("FUNCTION"),string("VOID"),-1,level-1,0);
            if(symbol.compare("LPAR")==0){
                nextSym();
                if(symbol.compare("RPAR")==0){
                    nextSym();
                    if(symbol.compare("LBRACE")==0){
                            ;
                    }
                    else
                        error(21);//21 缺少一个{
                }
                else
                    error(20);//20 缺少一个)
            }
            else
                error(22);//22 缺少一个(
        }
        else
            error(13);//13 期望一个标识符
    }
    else
        error(14);//14 期盼一个函数类型标识符
    
    arriveLBRACE();
    compoundStatement();//复合语句例外，在进入之前没有预读一个单词，因为它的出现都是确定的
    
    nextSym();
    if(symbol.compare("RBRACE")!=0)
        error(19);//19 缺少一个}
    deleteFunction();
    generateEndCode();
    
    level--;
}
void compoundStatement(){
    nextSym();
    if(symbol.compare("CONST")==0)
        constDefinition();
    if(symbol.compare("INT")==0||symbol.compare("CHAR")==0)
        varDefinition();
    statementList();
}
void statementList(){//文法中的语句列
    while(symbol.compare("IF")==0||
          symbol.compare("WHILE")==0||
          symbol.compare("LBRACE")==0||
          symbol.compare("ID")==0||
          symbol.compare("SCANF")==0||
          symbol.compare("PRINTF")==0||
          symbol.compare("SEMI")==0||
          symbol.compare("SWITCH")==0||
          symbol.compare("RETURN")==0
          ){
        statement();
        compileLog<<"~~"<<endl;
        compileLog<<symbol<<endl;
    }
}

int parameterList(){
    int count=0;
    if(symbol.compare("RPAR")==0)
        return 0;
    else if(symbol.compare("INT")==0||symbol.compare("CHAR")==0){
        string type=symbol;
        nextSym();
        if(symbol.compare("ID")==0){
            count++;
            string name(IDName);
            compileLog<<"parameter "<<type<<"  "<<name<<endl;
            insertSymbolTable(name,string("PARAMETER"),type,-1,level,0);
            generateParameterCode(type,name);
            nextSym();
            while(symbol.compare("COMMA")==0){
                nextSym();
                if(symbol.compare("INT")==0||symbol.compare("CHAR")==0){
                    string type=symbol;
                    nextSym();
                    if(symbol.compare("ID")==0){
                        count++;
                        string name(IDName);
                        compileLog<<"parameter "<<type<<"  "<<name<<endl;
                        insertSymbolTable(name,string("PARAMETER"),type,-1,level,0);
                        generateParameterCode(type,name);
                        nextSym();
                    }
                    else
                        error(13);//13 期望一个标识符
                }
                else
                    error(14);//14 期盼一个函数类型标识符
            }
        }
        else
            error(13);//13 期望一个标识符
    }
    else
        error(14);//14 期盼一个函数类型标识符
    arriveRPAR();
    return count;
}

void functionCall(int sign){//有返回值和无返回值的函数调用语句 sign=0代表无返回值,sign=1代表有返回值
    if(symbol.compare("ID")==0){
        string name=IDName;
        nextSym();
        if(symbol.compare("LPAR")==0){
            nextSym();
            if(symbol.compare("RPAR")==0){
                nextSym();
                compileLog<<"function "<<name<<"is called"<<endl;
                return;
            }
            int paraNum=0;
            expression();//假定expression将表达式计算出来的值放在temp1里面。
            string paraList[10];
            string para[10];
            paraList[paraNum]=expressionType;
            para[paraNum]=operand;
            paraNum++;
//            generateSetParaCode(operand);
            while(symbol.compare("COMMA")==0){
                nextSym();
                expression();
                paraList[paraNum]=expressionType;
                para[paraNum]=operand;
                paraNum++;
//                generateSetParaCode(operand);
            }

            if(symbol.compare("RPAR")!=0){
                error(5); //5
                arriveAtSemi();
                return;
                }
            int index=getLocation(name,string("FUNCTION"));
            if(index==-1){
                error(7); //7
                index=0;
            }
            if(paraNum!=symbolTable[index]->length){
                error(4);  //4
                compileLog<<"index "<<index<<endl;
                compileLog<<"1~"<<paraNum<<endl;
                compileLog<<"2~"<<symbolTable[index]->name<<endl;
                compileLog<<"3~"<<symbolTable[index]->length<<endl;
                for(int vv=0;vv<paraNum;vv++){
                    compileLog<<para[vv]<<endl;
                }
            }
            if((symbolTable[index]->type).compare("VOID")==0&&sign==1)
                error(8);   //8
            for(int i=0;errorNum==0&&i<symbolTable[index]->length;i++){
                string po=symbolTable[index+i+1]->type;
                generateSetParaCode(para[i]);
                if((po).compare(paraList[i])!=0){
       //             error(6);  不实现参数类型不匹配报错的功能了
                }
            }
            compileLog<<paraNum<<endl;
            paraNum=0;
            nextSym();
            compileLog<<"lllabel  "<<symbol<<endl;
            return;
        }
    }
    else
        error(13);//13 期望一个标识符
    arriveAtSemi();
}

int expression(){
    int result=0;
    expressionType=string("INT");
    string V1,V2,V3;
    if(symbol.compare("PLUS")==0||symbol.compare("MINUS")==0){
        if(symbol.compare("MINUS")==0){
            nextSym();
            term();
            V1=operand;
            char str[20];
            itoa(tempVarCount++,str,10);
            V3="_t"+string(str);
            insertSymbolTable(V3,string("VAR"),string("INT"),0,level,0);
            generateExpressionCode(string("-"),string("0"),V1,V3);
        }
        else{
            nextSym();
            term();
            V3=operand;
        }
    }
    else{
        term();
        V3=operand;
    }
    if(termType.compare("CHAR")==0)
        expressionType=string("CHAR");
    while(symbol.compare("PLUS")==0||symbol.compare("MINUS")==0){
        V1=V3;
        expressionType=string("INT");
        if(symbol.compare("PLUS")==0){
            nextSym();
            term();
            V2=operand;
            char str[20];
            itoa(tempVarCount++,str,10);
            V3="_t"+string(str);
            insertSymbolTable(V3,string("VAR"),string("INT"),0,level,0);
            generateExpressionCode(string("+"),V1,V2,V3);
        }
        else{
            nextSym();
            term();
            V2=operand;
            char str[20];
            itoa(tempVarCount++,str,10);
            V3="_t"+string(str);
            insertSymbolTable(V3,string("VAR"),string("INT"),0,level,0);
            generateExpressionCode(string("-"),V1,V2,V3);
        }
    }
    operand=V3;
    compileLog<<"expression value is"<<result<<endl;
    return result;
}
int term(){
    termType=string("INT");
    string V1,V2,V3;
    factor();
    if(factorType.compare("CHAR")==0)
        termType=string("CHAR");
    V3=operand;
    while(symbol.compare("STAR")==0||symbol.compare("DIVISION")==0){
        termType=string("INT");
        V1=V3;
        if(symbol.compare("STAR")==0){
            nextSym();
            factor();
            V2=operand;
            char str[20];
            itoa(tempVarCount++,str,10);
            V3="_t"+string(str);
            insertSymbolTable(V3,string("VAR"),string("INT"),0,level,0);
            generateExpressionCode(string("*"),V1,V2,V3);
        }
        else{
            nextSym();
            factor();
            V2=operand;
            char str[20];
            itoa(tempVarCount++,str,10);
            V3="_t"+string(str);
            insertSymbolTable(V3,string("VAR"),string("INT"),0,level,0);
            generateExpressionCode(string("/"),V1,V2,V3);
        }
    }
    operand=V3;
    return 0;
}
int factor(){
    factorType=string("INT");
    string V;
    if(symbol.compare("ID")==0){
        string name=IDName;
        nextSym();
        if(symbol.compare("LBRACKET")==0){
            nextSym();
            expression();
            if(symbol.compare("RBRACKET")!=0)
                error(10);//10
            int index=getLocation(name,string("ARRAY"));
            if(index==-1){
                error(7);//7
                index=0;
            }
            factorType=symbolTable[index]->type;
            char str[20];
            itoa(tempVarCount++,str,10);
            V="_t"+string(str);
            insertSymbolTable(V,string("VAR"),symbolTable[index]->type,0,level,0);
            generateExpressionCode(string("=[]"),name,operand,V);
//                compileLog<<"array element index is"<<index<<"array name is"<<name<<endl;
            //return array[index]
            operand=V;
            nextSym();
            return 1;
        }
        else if(symbol.compare("LPAR")==0){
            traceSym();
            traceSym();
            nextSym();
            int index=getLocation(name,string("FUNCTION"));
            if(index==-1){
                error(7);//7
                index=0;
            }
            factorType=symbolTable[index]->type;
            functionCall(1);
            char str[20];
            itoa(tempVarCount++,str,10);
            V="_t"+string(str);
            insertSymbolTable(V,string("VAR"),symbolTable[index]->type,0,level,0);
            generateCallValueFunctionCode(name,V);
            operand=V;
//            compileLog<<"function value"<<endl;
            //get function return value
            return 1;
        }
        else{
            int index=getLocation(name,string("VAR"));
            if(index==-1){
                error(7);//7
                index=0;
            }

//            if(symbolTable[index]->kind.compare("FUNCTION")==0||
//               symbolTable[index]->kind.compare("ARRAY")==0)
//                error(9);//9
            operand=name;
            return 1;
        }//得到标识符的值并返回
    }
    else if(symbol.compare("NUM")==0||symbol.compare("PLUS")==0||symbol.compare("MINUS")==0){
        int te=integer();
        char str[20];
        sprintf(str, "%d", te);
        operand=string(str);
        itoa(tempVarCount++,str,10);
        V="_t"+string(str);
        insertSymbolTable(V,string("VAR"),string("INT"),0,level,0);
        generateAssignmentCode(string("="),operand,string(""),V);
        operand=V;
        //return integer();
        return 0;
    }
    else if (symbol.compare("CHARVALUE")==0){
        nextSym();
        char str[20];
        sprintf(str, "%d", chValue);
        operand="\'"+string(str)+"\'";
        itoa(tempVarCount++,str,10);
        V="_t"+string(str);
        insertSymbolTable(V,string("VAR"),string("CHAR"),0,level,0);
        generateAssignmentCode(string("="),operand,string(""),V);
        operand=V;
        factorType=string("CHAR");
        return chValue-0;
    }
    else if(symbol.compare("LPAR")==0){
        nextSym();
        int value=expression();
        if(symbol.compare("RPAR")!=0)
            error(20);//20 缺少一个)
        nextSym();
        factorType=expressionType;
        return value;
    }
    else
        error(23);//23 不合法的因子
}
void statement(){
    const char* te=symbol.c_str();
    switch (symbolNum[symbol]){
            case 9:conditionStatement();break;
            case 11:recurrentStatement();break;
            case 34:
                  nextSym();
                  statementList();
                  if(symbol.compare("RBRACE")!=0){
                    error(19);//19 缺少一个}
                    traceSym();
                  }
                  nextSym();
                  break;
            case 1:
                {
                  nextSym();
                  string name=IDName;
                  if(symbol.compare("LPAR")==0){
                      traceSym();
                      traceSym();
                      nextSym();
                      functionCall(0);
                      generateCallFunctionCode(name);
                      compileLog<<"function "<<name<<" is called1"<<endl;
                      if(symbol.compare("SEMI")!=0){
                        error(18);//18 缺少;
                        traceSym();
                      }
                      nextSym();
                  }
                  else if(symbol.compare("EQUAL")==0){
                      traceSym();
                      traceSym();
                      nextSym();
                      assignmentStatement();
                      compileLog<<"var "<<name<<" is assigned"<<endl;
                      compileLog<<symbol<<endl;
                      if(symbol.compare("SEMI")!=0){
                        error(18);//18 缺少;
                        traceSym();
                      }
                      nextSym();
                  }
                  else if(symbol.compare("LBRACKET")==0){
                      traceSym();
                      traceSym();
                      nextSym();
                      assignmentStatement();
                      compileLog<<"array "<<name<<" element is assigned"<<endl;
                      if(symbol.compare("SEMI")!=0){
                        error(18);//18 缺少;
                        traceSym();
                      }
                      nextSym();
                  }
              break;
                }
            case 15:
                readStatement();
                if(symbol.compare("SEMI")!=0){
                    error(18);//18 缺少;
                    traceSym();
                }
                nextSym();
                break;
            case 16:
                printStatement();
                if(symbol.compare("SEMI")!=0){
                    error(18);//18 缺少;
                    traceSym();
                    }
                nextSym();
                break;
            case 29:nextSym();  break;
            case 12:switchStatement(); break;
            case 17:
                returnStatement();
                if(symbol.compare("SEMI")!=0){
                    error(18);//18 缺少;
                    traceSym();
                }
                nextSym();
                break;
        }
}
void assignmentStatement(){
    if(symbol.compare("ID")==0){
        string name=IDName;
        nextSym();

        if(symbol.compare("EQUAL")==0){
            int index=getLocation(name,string("VAR"));
            if(index==-1){
              error(7);//7
              index=0;
            }
            if(symbolTable[index]->kind==string("CONST"))
                error(38);
            nextSym();
            int value=expression();
            generateAssignmentCode(string("="),operand,string(""),name);
            compileLog<<"name "<<name<<" value "<<value<<endl;
            return;
        }
        else if(symbol.compare("LBRACKET")==0){
            int index_=getLocation(name,string("ARRAY"));
            if(index_==-1){
               error(7);//7
               index_=0;
            }
            nextSym();
            expression();
            string index=operand;
            if(symbol.compare("RBRACKET")==0){
                nextSym();
                if(symbol.compare("EQUAL")==0){
                    nextSym();
                    int value=expression();
                    generateAssignmentCode(string("[]="),operand,index,name);
                    compileLog<<name<<"is assigned array ele index is "<<index<<"value is"<<value<<endl;
                    return;
                }
                else
                    error(24);//24 期盼一个=
            }
            else
                error(25);//25 缺少一个[
        }
        else
            error(26);//26 缺少一个]
    }
    else
        error(13);//13 期望一个标识符

    arriveAtSemi();
}
void conditionStatement(){
    if(symbol.compare("IF")==0){
        nextSym();
        string label;
        string label_;
        string op1;
        string op2;
        string compare;
        if(symbol.compare("LPAR")==0){
        nextSym();
        expression();
        op1=operand;
        if(symbol.compare("LESS")==0||symbol.compare("LESSEQ")==0||symbol.compare("GREATER")==0||
        symbol.compare("JEQUAL")==0||symbol.compare("NEQUAL")==0||symbol.compare("GREATEREQ")==0){
            compare=symbol;
            nextSym();
            expression();
            op2=operand;
            char str[20];
            itoa(labelCount++,str,10);
            label="label"+string(str);
            switch(symbolNum[compare]){
                case 22:generateJumpCode("JGE",op1,op2,label); break;
                case 23:generateJumpCode("JG",op1,op2,label); break;
                case 26:generateJumpCode("JLE",op1,op2,label);break;
                case 25:generateJumpCode("JNE",op1,op2,label);break;
                case 42:generateJumpCode("JE",op1,op2,label);break;
                case 27:generateJumpCode("JL",op1,op2,label);break;
            }
            compileLog<<op1<<" "<<compare<<" "<<op2<<endl;
        }
        else if(symbol.compare("RPAR")==0){
            char str[20];
            itoa(labelCount++,str,10);
            label="label"+string(str);
            generateJumpCode("JE",op1,string("0"),label);
        }
        else
            error(34);
        if(symbol.compare("RPAR")!=0)
            error(20);
        }
        else
            error(22);//22 缺少一个(
        arriveStatement();
        statement();
        char str[20];
        itoa(labelCount++,str,10);
        label_="label"+string(str);
        generateJumpCode("JMP","","",label_);
        generateLabelCode(label);
        if(symbol.compare("ELSE")==0){
            nextSym();
            statement();
        }
        generateLabelCode(label_);
    }
}

void recurrentStatement(){
    if(symbol.compare("WHILE")==0){
        nextSym();
        string label_;
        string label;
        string op1;
        string op2;
        string compare;
        char str[20];
        itoa(labelCount++,str,10);
        label="label"+string(str);
        itoa(labelCount++,str,10);
        label_="label"+string(str);
        generateLabelCode(label_);
        compileLog<<"while statement"<<endl;
        if(symbol.compare("LPAR")==0){
            nextSym();
            expression();
            op1=operand;
            if(symbol.compare("LESS")==0||symbol.compare("LESSEQ")==0||symbol.compare("GREATER")==0||
            symbol.compare("JEQUAL")==0||symbol.compare("NEQUAL")==0||symbol.compare("GREATEREQ")==0){
                compare=symbol;
                nextSym();
                expression();
                op2=operand;

                switch(symbolNum[compare]){
                    case 22:generateJumpCode("JGE",op1,op2,label); break;
                    case 23:generateJumpCode("JG",op1,op2,label); break;
                    case 26:generateJumpCode("JLE",op1,op2,label);break;
                    case 25:generateJumpCode("JNE",op1,op2,label);break;
                    case 42:generateJumpCode("JE",op1,op2,label);break;
                    case 27:generateJumpCode("JL",op1,op2,label);break;
                }
                compileLog<<op1<<" "<<compare<<" "<<op2<<endl;
            }
            else if(symbol.compare("RPAR")==0){
                char str[20];
                itoa(labelCount++,str,10);
                label="label"+string(str);
                generateJumpCode("JE",op1,string("0"),label);
            }
            else
                error(34);
            if(symbol.compare("RPAR")!=0){
                error(20);
            }
        }
        else
            error(22);
        arriveStatement();
        statement();
        generateJumpCode("JMP","","",label_);
        generateLabelCode(label);
    }
}
void switchStatement(){
    if(symbol.compare("SWITCH")==0){
        char str[20];
        itoa(labelCount++,str,10);
        string labelOut="label"+string(str);
        string op1;
        nextSym();
        if(symbol.compare("LPAR")==0){
            nextSym();
            int value=expression();
            op1=operand;
            if(symbol.compare("RPAR")==0){
                nextSym();
                if(symbol.compare("LBRACE")==0){
                    nextSym();
                    string label1;
                    if(symbol.compare("CASE")!=0)
                        error(35);
                    nextSym();
                    string type;
                    int value;
                    char str[20];
                    itoa(labelCount++,str,10);
                    label1="label"+string(str);
                    if(symbol.compare("PLUS")==0||symbol.compare("MINUS")==0||symbol.compare("NUM")==0){
                        value=integer();
                        type=string("INT");
                        char temp[64];
                        sprintf(temp,"%d", value);
                        string ttt(temp);
                        generateJumpCode(string("JNEI"),op1,ttt,label1);
                    }
                    else if(symbol.compare("CHARVALUE")==0){
                        value=chValue-0;
                        type=string("CHAR");
                        nextSym();
                        stringstream stream;
                        stream << chValue;
                        generateJumpCode(string("JNEC"),op1,stream.str(),label1);
                    }
                    else
                        error(27);//27 case语句必须使用常量做比较
                    if(symbol.compare("COLON")!=0)
                            error(11);//11
                    //nextSym();
                    arriveStatement();
                    statement();
                    generateJumpCode(string("JMP"),string(""),string(""),labelOut);
                    compileLog<<"case judge type "<<type<<"value "<<value<<endl;

                    while(symbol.compare("CASE")==0){
                        generateLabelCode(label1);
                        char str[20];
                        itoa(labelCount++,str,10);
                        label1="label"+string(str);
                        nextSym();
                        string type;
                        int value;
                        if(symbol.compare("PLUS")==0||symbol.compare("MINUS")==0||symbol.compare("NUM")==0){
                            value=integer();
                            type=string("INT");
                            char temp[64];
                            sprintf(temp, "%d", value);
                            string ttt(temp);
                            generateJumpCode(string("JNEI"),op1,ttt,label1);
                        }
                        else if(symbol.compare("CHARVALUE")==0){
                            value=chValue-0;
                            type=string("CHAR");
                            nextSym();
                            stringstream stream;
                            stream << chValue;
                            generateJumpCode(string("JNEC"),op1,stream.str(),label1);
                        }
                        else
                            error(27);//27 case语句必须使用常量做比较
                        if(symbol.compare("COLON")!=0)
                            error(28);//27 期盼一个:
                        //nextSym();
                        arriveStatement();
                        statement();
                        generateJumpCode(string("JMP"),string(""),string(""),labelOut);
                        compileLog<<"case judge type "<<type<<"value "<<value<<endl;
                    }
                    generateLabelCode(label1);
                    if(symbol.compare("DEFAULT")==0){
                        nextSym();
                        if(symbol.compare("COLON")!=0)
                            error(28);//27 期盼一个:
                        arriveStatement();
                        statement();
                        compileLog<<"default statement"<<endl;
                    }
                    if(symbol.compare("RBRACE")!=0){
                        error(19);//19 缺少一个}
                        return;
                    }
                }
                else
                    error(21);
                generateLabelCode(labelOut);
            }
            else
                error(20);
        }
        else
            error(22);
        arriveRBRACE();
    }
}
int integer(){
    int neg=1;
    int Num=0;
    if(symbol.compare("PLUS")==0||symbol.compare("MINUS")==0){
        if(symbol.compare("MINUS")==0)
            neg=-1;
        nextSym();
    }
    if(symbol.compare("NUM")==0&&
        (*pLast1!='0'||p-pLast1==1)){
        Num=neg*num;
        nextSym();
    }
    else
        error(16);//16 不合法的数字!可能含有非数字字符或者前导零

    return Num;
}
void readStatement(){
    if(symbol.compare("SCANF")==0){
        nextSym();
        if(symbol.compare("LPAR")==0){
            nextSym();
            compileLog<<"read  ";
            if(symbol.compare("ID")==0){
                compileLog<<IDName<<" ";
                int index=getLocation(IDName,string("VAR"));
                if(index==-1){
                    error(7);//7
                    index=0;
                }
                generateScanfCode(IDName);
                nextSym();
            }
            else
                error(13);//13 期望一个标识符
            while(symbol.compare("COMMA")==0){
                nextSym();
                if(symbol.compare("ID")==0){
                    compileLog<<IDName<<" ";
                    int index=getLocation(IDName,string("VAR"));
                    if(index==-1){
                        error(7);//7
                        index=0;
                    }
                    generateScanfCode(IDName);
                    nextSym();
                }
                else{
                    error(13);//13 期望一个标识符
                    arriveAtSemi();
                }
            }
            if(symbol.compare("RPAR")!=0){
                error(20);//20 缺少一个)
                arriveAtSemi();
            }
            nextSym();
            compileLog<<endl;
            return;
        }
        else
            error(22);
        arriveAtSemi();
    }
}
void printStatement(){
    if(symbol.compare("PRINTF")==0){
        nextSym();
        int value;
        if(symbol.compare("LPAR")==0){
            nextSym();
            compileLog<<"print  ";
            if(symbol.compare("STRING")!=0){
                value=expression();
                generatePrintCode(string(""),operand);
                compileLog<<value<<endl;
                if(symbol.compare("RPAR")!=0){
                    error(20);//20 缺少一个)
                    arriveAtSemi();
                }
                nextSym();
                return;
            }
            else{
                compileLog<<stringValue<<" ";
                nextSym();
                if(symbol.compare("COMMA")==0){
                    nextSym();
                    value=expression();
                    generatePrintCode(stringValue,operand);
                    compileLog<<value<<endl;
                    if(symbol.compare("RPAR")!=0){
                        error(20);//20 缺少一个)
                        arriveAtSemi();
                    }
                    nextSym();
                    return;
                }
                else if(symbol.compare("RPAR")!=0){
                    error(20);//20 缺少一个)
                    arriveAtSemi();
                }
                generatePrintCode(stringValue,string(""));
                nextSym();
                return;
            }
        }
        else
            error(22);
        arriveAtSemi();
    }
}
void returnStatement(){
    if(symbol.compare("RETURN")==0){
        compileLog<<"return ";
        nextSym();
        if(symbol.compare("LPAR")==0){
            if(returnType=="VOID")
                error(40);
            returnNum++;
            nextSym();
            int value=expression();
            generateReturnCode(operand);
            compileLog<<value<<endl;
            if(symbol.compare("RPAR")!=0)
                error(20);//20 缺少一个)
            nextSym();
        }
        else{
            generateReturnCode(string(""));
            if(returnType!="VOID")
                error(39);
        }
    }
}
