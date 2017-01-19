#include "global.h"

int main()
{
    ofstream outfile;
    outfile.open("midcode.txt");
    getCode();
    program();
    if(errorNum!=0){
        exit(1);
    }
    dag();
    killDeadCode();
//    mergeMidCode();
//    killChildExpression(); 该函数已废弃
    for(int i=0;i<codeLength;i++){
        outfile<<midCode[i]->op<<","<<midCode[i]->var1<<","<<midCode[i]->var2<<","<<midCode[i]->var3<<endl;
    }
    outfile.close();
//    cout<<tableLength<<"???"<<endl;
//    for(int i=0;i<tableLength;i++){
//        cout<<symbolTable[i]->name<<","<<symbolTable[i]->kind<<","<<symbolTable[i]->type<<","<<symbolTable[i]->value
//        <<","<<symbolTable[i]->level<<","<<symbolTable[i]->length<<","<<symbolTable[i]->depth<<endl;
//    }
//    for(int i=0;i<procedureNum;i++){
//        cout<<procedureIndex[i]<<endl;
//    }

    generateMIPS();

return 0;
}
