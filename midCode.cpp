#include "global.h"
int codeLength=0;
code* midCode[1000];

void generateConstCode(string op,string var1,int num,string var3){
    if(codeLength<1000){
        code* c=new code;
        c->op=op;
        c->var1=var1;
        char temp[64];
        sprintf(temp, "%d", num);
        string ttt(temp);
        c->var2=ttt;
        c->var3=var3;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}
void generateVarCode(string type,int length,string name){
    if(codeLength<1000){
        code* c=new code;
        c->op=type;
        c->var1="";
        if(length!=0){
            char temp[64];
            sprintf(temp, "%d", length);
            string ttt(temp);
            c->var2=ttt;
        }
        else
            c->var2="";
        c->var3=name;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}
void generateFunctionCode(string name){
    if(codeLength<1000){
        code* c=new code;
        c->op="LABEL";
        c->var1="";
        c->var2="";
        c->var3=name;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}
void generateParameterCode(string type,string name){
    if(codeLength<1000){
        code* c=new code;
        c->op="PARA";
        c->var1=type;
        c->var2="";
        c->var3=name;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}
void generateSetParaCode(string t){
    if(codeLength<1000){
        code* c=new code;
        c->op="SETPARA";
        c->var1="";
        c->var2="";
        c->var3=t;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}//表达式计算之后的值固定保存在operand中
void generateCallValueFunctionCode(string name,string V){
    if(codeLength<1000){
        code* c=new code;
        c->op="CALLV";
        c->var1=name;
        c->var2="";
        c->var3=V;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}

void generateCallFunctionCode(string name){
    if(codeLength<1000){
        code* c=new code;
        c->op="CALL";
        c->var1=name;
        c->var2="";
        c->var3="";
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}

void generateExpressionCode(string op,string var1,string var2,string var3){
    if(codeLength<1000){
        code* c=new code;
        c->op=op;
        c->var1=var1;
        c->var2=var2;
        c->var3=var3;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}

void generateAssignmentCode(string op,string var1,string var2,string var3){
    if(codeLength<1000){
        code* c=new code;
        c->op=op;
        c->var1=var1;
        c->var2=var2;
        c->var3=var3;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}
void generateJumpCode(string jump,string a,string b,string c){
    if(codeLength<1000){
        code* c1=new code;
        c1->op=jump;
        c1->var1=a;
        c1->var2=b;
        c1->var3=c;
        midCode[codeLength++]=c1;
    }
    else
        error(3);//3
}
void generateLabelCode(string labelName){
    if(codeLength<1000){
        code* c=new code;
        c->op="LABEL";
        c->var1="";
        c->var2="";
        c->var3=labelName;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}
void generateScanfCode(string name){
    if(codeLength<1000){
        code* c=new code;
        c->op="SCANF";
        c->var1="";
        c->var2="";
        c->var3=name;
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}

void generatePrintCode(string str,string name){
    if(codeLength<1000){
        code* c=new code;
        c->op="PRINTF";
        c->var1=str;
        c->var2=name;
        c->var3="";
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}


void generateReturnCode(string name){
    if(codeLength<1000){
        code* c=new code;
        c->op="RETURN";
        c->var1=name;
        c->var2="";
        c->var3="";
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}

void generateBeginCode(){
    if(codeLength<1000){
        code* c=new code;
        c->op="BEGIN";
        c->var1="";
        c->var2="";
        c->var3="";
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}
void generateEndCode(){
    if(codeLength<1000){
        code* c=new code;
        c->op="END";
        c->var1="";
        c->var2="";
        c->var3="";
        midCode[codeLength++]=c;
    }
    else
        error(3);//3
}


