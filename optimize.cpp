#include "global.h"

void mergeMidCode(){
    for(int i=0;i<codeLength;i++){
        if(midCode[i]->op=="+"||
           midCode[i]->op=="-"||
           midCode[i]->op=="*"||
           midCode[i]->op=="/")
            if(midCode[i+1]->op=="="&&midCode[i+1]->var1==midCode[i]->var3){
                midCode[i]->var3=midCode[i+1]->var3;
                deleteMidCode(i+1);
            }
    }
}

void deleteMidCode(int i){
    for(int j=i;j<codeLength-1;j++){
        midCode[j]=midCode[j+1];
    }
    codeLength--;
}

void killChildExpression(){
    int i=0;
    while(midCode[i]->op!="LABEL")
        i++;
    for(int j=i+1;j<codeLength;j++){
        vector<string> replace;

        for(int k=j+1;k<codeLength&&midCode[k]->op!="LABEL";k++){
      //      cout<<k<<"  "<<j<<endl;
            //if(midCode[j]->op==string("=[]"))
            //    cout<<midCode[j]->op<<"  "<<midCode[k]->op<<endl;
            if(midCode[j]->op==midCode[k]->op&&
          (midCode[j]->op=="+"||midCode[j]->op=="-"||
            midCode[j]->op=="*"||midCode[j]->op=="/"||
            midCode[j]->op=="=[]")&&
               midCode[j]->var1==midCode[k]->var1&&
               midCode[j]->var2==midCode[k]->var2 ){
                   replace.push_back(midCode[k]->var3);
                   deleteMidCode(k);
                   k--;
            }
            else{
                vector<string>::iterator it;
                for(it=replace.begin();it!=replace.end();it++){
                    if(*it==midCode[k]->var2){
                        midCode[k]->var2=midCode[j]->var3;
                    }
                    else if(*it==midCode[k]->var1){
                        midCode[k]->var1=midCode[j]->var3;
                    }
                }
            }
            if(midCode[k]->var3==midCode[j]->var2||midCode[k]->var3==midCode[j]->var1)
                break;
        }
    }
}
