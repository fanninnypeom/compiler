#include "global.h"
int tableLength=0;
int procedureNum=0;
int procedureIndex[50];
sign symbolTable[300];

void insertSymbolTable(string name,string kind,string type,int value,int level,int length){
    for(int i=tableLength-1;i>=0;i--){
        if(symbolTable[i]->level==level&&symbolTable[i]->name==name){
            error(36);//36
            break;
        }
    }//同层不能有同名变量，数组，函数
    if(tableLength<300){//需要判断同层是否有同名变量
        sign s=new node;
        s->name=name;
        s->kind=kind;
        s->type=type;
        s->value=value;
        s->level=level;
        s->length=length;
        if(kind.compare("FUNCTION")==0){
            for(int i=0;i<length;i++){
                symbolTable[tableLength-i]=symbolTable[tableLength-i-1];
            }
            symbolTable[tableLength-length]=s;
            tableLength++;
            if(procedureNum<50)
                procedureIndex[procedureNum++]=tableLength-length;
            else
                error(2);//2
            return;
        }
        else{
            symbolTable[tableLength++]=s;
        }
    }
    else{
        error(1);//1
    }
}
int getLocation(string name,string kind){
    int i;
    if(kind==string("FUNCTION"))
        for(i=tableLength-1;i>=0;i--){
            if(stricmp((symbolTable[i]->name).c_str(),name.c_str())==0
            &&symbolTable[i]->kind==kind)
                return i;
            }
    else if(kind==string("VAR")){
        for(i=tableLength-1;i>=0;i--){
            if(stricmp((symbolTable[i]->name).c_str(),name.c_str())==0){
            if((symbolTable[i]->kind==string("CONST")||
             symbolTable[i]->kind==string("VAR")||
             symbolTable[i]->kind==string("PARAMETER")
             )
             )
              //          error(37);
             return i;
            }
        }
    }
    else
        for(i=tableLength-1;i>=0;i--){
            if(stricmp((symbolTable[i]->name).c_str(),name.c_str())==0){
            if(symbolTable[i]->kind==string("ARRAY"))
  //              error(37);
                 return i;
            }
        }
        return -1;
}



void deleteFunction(){
    int length=procedureIndex[procedureNum-1];
    procedureNum--;
    int depth=0;
    for(int i=length;i<tableLength;i++){
        if(symbolTable[i]->length==0)
            depth+=1;
        else
            depth+=symbolTable[i]->length;
    }
    depth*=4;

    symbolTable[length-1]->depth=depth;
    tableLength=length;
}



