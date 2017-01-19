#include "global.h"
MIPSsign* MIPSsymbolTable[1500];
int MIPStableLength=0;
int lev=0;

ofstream MIPSfile;

map<string,string>tRegisterPool;
map<string,string>sRegisterPool;

block* nodeArray[500];
int nodeArrayLength=0;
int killCount=0;
int existInBlock(string name,int num){
    for(int i=num;i<codeLength&&midCode[i]->op!="END";i++){
        if(midCode[i]->var1==name||midCode[i]->var2==name)
            return 1;
        if(midCode[i]->op=="SETPARA"&&midCode[i]->var3==name)
            return 1;
    }
    return 0;
}

int killDeadCode(){//消除死代码
    for(int i=0;i<codeLength;i++){
        if((midCode[i]->op=="+"||
           midCode[i]->op=="-"||
           midCode[i]->op=="*"||
           midCode[i]->op=="/"||
           midCode[i]->op=="="||
           midCode[i]->op=="=[]")&&
           midCode[i]->var3.c_str()[0]=='_'&&
           midCode[i]->var3.c_str()[1]=='t'&&//必须是临时变量
           !existInBlock(midCode[i]->var3,i)){
           for(int k=i;k<codeLength-1;k++){
               midCode[k]=midCode[k+1];
           }
           codeLength--;
        }
    }
}

int existInTree(dagTree* t,dagNode* value){
    for(int i=0;i<t->elements.size();i++){
        if(t->elements[i]==value)
            return 1;
    }
    return 0;
}

int traveseDag(dagTree* tree,string name,dagNode** var ){
    for(int i=0;i<tree->elements.size();i++){
        for(int j=0;j<tree->elements[i]->var.size();j++){
            if(tree->elements[i]->var[j]==name&&
               !(name.c_str()[0]>='0'&&name.c_str()[0]<='9')){
                *var=tree->elements[i];
                return 1;
            }
        }
    }
    return 0;
}

int traveseOpDag(dagTree* tree,string op,string name,dagNode* var1,dagNode* var2,dagNode** var ){
    for(int i=0;i<tree->elements.size();i++){
        if(tree->elements[i]->value==op&&
           tree->elements[i]->lChild==var1&&
           tree->elements[i]->rChild==var2){
            dagNode* killNode;
            if(traveseDag(tree,name,&killNode)){
                for(int xx=0;xx<killNode->var.size();xx++){
                    if(killNode->var[xx]==name){
                        char str[20];
                        itoa(killCount++,str,10);
                        killNode->var[xx]=killNode->var[xx]+"$";
                        if(killNode->father.size()==0)
                            killNode->var.erase(killNode->var.begin()+xx);
                    }
                }
            }//如果和某一个变量被重复赋值，就将原来的节点上的var抹去
            tree->elements[i]->var.push_back(name);
            *var=tree->elements[i];
            return 1;
        }
    }
    return 0;
}

void dag(){//消除公共子表达式
    int blockCount=-1;
    for(int i=0;i<codeLength;i++){
        if(midCode[i]->op=="BEGIN"){
//            dataFlowAnalysis(i);
            blockCount=-1;
        }

        if(midCode[i]->op=="LABEL")
            blockCount++;
        vector<dagTree*> dagArray;
        int codeCount=0;
        for(;midCode[i]->op=="+"||
           midCode[i]->op=="-"||
           midCode[i]->op=="*"||
           midCode[i]->op=="/"||
           midCode[i]->op=="="||
           midCode[i]->op=="=[]"
//           ||midCode[i]->op=="[]="
           ;i++){
               codeCount++;
               if(midCode[i]->op=="+"||
                midCode[i]->op=="-"||
                midCode[i]->op=="*"||
                midCode[i]->op=="/"||
                midCode[i]->op=="=[]"){
                    int flag=0;
                    dagNode* var1;

                    for(int j=0;j<dagArray.size();j++){
                        flag=traveseDag(dagArray[j],midCode[i]->var1,&var1);
                        if(flag==1)
                            break;
                    }
                    if(flag!=1){
                        dagTree* varT=new dagTree;
                        var1=new dagNode;
                        var1->value=midCode[i]->var1;
                        var1->var.push_back(midCode[i]->var1);
                        varT->elements.push_back(var1);
                        dagArray.push_back(varT);
                    }
                    flag=0;
                    dagNode* var2;
                    for(int j=0;j<dagArray.size();j++){
                        flag=traveseDag(dagArray[j],midCode[i]->var2,&var2);
                        if(flag==1)
                            break;
                    }
                    if(flag!=1){
                        dagTree* varT=new dagTree;
                        var2=new dagNode;
                        var2->value=midCode[i]->var2;
                        var2->var.push_back(midCode[i]->var2);
                        varT->elements.push_back(var2);
                        dagArray.push_back(varT);
                    }
                    flag=0;
                    dagNode* var3;
                    for(int j=0;j<dagArray.size();j++){
                        flag=traveseOpDag(dagArray[j],midCode[i]->op,midCode[i]->var3,var1,var2,&var3);
                        if(flag==1)
                            break;
                    }
                    if(flag!=1){
                        var3=new dagNode;
                        dagNode* killNode;

                        for(int vv=0;vv<dagArray.size();vv++)
                            if(traveseDag(dagArray[vv],midCode[i]->var3,&killNode)){
                                for(int xx=0;xx<killNode->var.size();xx++){
                                    if(killNode->var[xx]==midCode[i]->var3){
                                        char str[20];
                   //                     cout<<"didididi"<<endl;
                                        itoa(killCount++,str,10);
                                        killNode->var[xx]=killNode->var[xx]+"$";
                                        if(killNode->father.size()==0)
                                            killNode->var.erase(killNode->var.begin()+xx);
                                    }
                                }
                            }//如果和某一个变量被重复赋值，就将原来的节点上的变量名都加上数字

                        var3->value=midCode[i]->op;
                        var3->var.push_back(midCode[i]->var3);
                        var3->lChild=var1;
                        var3->rChild=var2;
                        var1->father.push_back(var3);
                        var2->father.push_back(var3);
                        int j=0;
                        int k=0;
                        for(;j<dagArray.size();j++){
                            dagNode* tem=new dagNode;
                            if(existInTree(dagArray[j],var1))
                                break;
                        }
                        for(;k<dagArray.size();k++){
                            dagNode* tem=new dagNode;
                            if(existInTree(dagArray[k],var2))
                                break;
                        }
                        if(midCode[i]->var1=="0"){
           //                 cout<<j<<" "<<k<<endl;
           //                 cout<<dagArray.size()<<endl;
                        }
                        dagArray[j]->elements.push_back(var3);
                        if(j!=k&&j<dagArray.size()&&k<dagArray.size()){
        //                    cout<<"j  "<<j<<endl;
        //                    cout<<"size  "<<dagArray[j]->elements.size()<<endl;

                            for(int l=0;l<dagArray[k]->elements.size();l++)
                                dagArray[j]->elements.push_back(dagArray[k]->elements[l]);
                            dagArray.erase(dagArray.begin()+k);
                        }
                    }
                }
                else{
                    int flag=0;
                    dagNode* var1;
                    for(int j=0;j<dagArray.size();j++){
                        flag=traveseDag(dagArray[j],midCode[i]->var1,&var1);
                        if(flag==1)
                            break;
                    }


                    if(flag!=1){
                        dagTree* varT=new dagTree;
                        var1=new dagNode;
                        var1->value=midCode[i]->var1;
                        var1->var.push_back(midCode[i]->var1);
                        varT->elements.push_back(var1);
                        dagArray.push_back(varT);

                    }
                    dagNode* killNode;
                    for(int vv=0;vv<dagArray.size();vv++)
                        if(traveseDag(dagArray[vv],midCode[i]->var3,&killNode)){
                            for(int xx=0;xx<killNode->var.size();xx++){
                                if(killNode->var[xx]==midCode[i]->var3){
                                    char str[20];
               //                     cout<<"didididi"<<endl;
                                    itoa(killCount++,str,10);
                                    killNode->var[xx]=killNode->var[xx]+"$";
                                    if(killNode->father.size()==0)
                                        killNode->var.erase(killNode->var.begin()+xx);
                                }
                            }
                        }//如果和某一个变量被重复赋值，就将原来的节点上的变量名都加上数字
                    var1->var.push_back(midCode[i]->var3);

                }
          }
          /*
           cout<<"`````````````"<<endl;
            for(int j=0;j<dagArray.size();j++){
                cout<<"-------tree-------------"<<endl;
                for(int k=0;k<dagArray[j]->elements.size();k++){
                    cout<<dagArray[j]->elements[k]->value<<endl;
                    if(dagArray[j]->elements[k]->lChild!=NULL&&
                    dagArray[j]->elements[k]->lChild->var.size()>0)
                        cout<<"lChild "<<dagArray[j]->elements[k]->lChild->var[0]<<endl;
                    if(dagArray[j]->elements[k]->rChild!=NULL&&
                    dagArray[j]->elements[k]->rChild->var.size()>0)
                        cout<<"rChild "<<dagArray[j]->elements[k]->rChild->var[0]<<endl;
                    for(int l=0;l<dagArray[j]->elements[k]->var.size();l++)
                        cout<<dagArray[j]->elements[k]->var[l]<<endl;
                    cout<<"----------"<<endl;
                }
            }
            */
/////////////////消dag图
            vector<dagNode*> nodeStack;
            for(int j=0;j<dagArray.size();j++){
                for(int k=dagArray[j]->elements.size()-1;;k=(k==0)?dagArray[j]->elements.size()-1:k-1,k%(dagArray[j]->elements.size())){
                        if(dagArray[j]->elements.size()==0)
                            break;
      //                  cout<<j<<endl;
      //                  cout<<"??"<<k<<endl;

      //                  cout<<dagArray[j]->elements.size()<<endl;
      //                  cout<<dagArray.size()<<endl;
      //                  cout<<"11"<<dagArray[j]->elements[k]->father.size()<<endl;
     //                   for(int z=0;z<dagArray[j]->elements[k]->father.size();z++)
      //                      cout<<dagArray[j]->elements[k]->father[z]->value<<endl;
      //                  cout<<"ffffffff"<<endl;
      //                  cout<<dagArray[j]->elements[k]->value<<endl;
      //                  cout<<dagArray[j]->elements[k]->father.size() <<endl;
       //                 for(int z=0;z<dagArray[j]->elements[k]->var.size();z++){
       //                     cout<<dagArray[j]->elements[k]->var[z]<<endl;
       //                 }

                    if(dagArray[j]->elements[k]->father.size()==0){
                        dagNode* p=dagArray[j]->elements[k];
                        nodeStack.push_back(p);
                        dagArray[j]->elements.erase(dagArray[j]->elements.begin()+k);
                        if(dagArray[j]->elements.size()==0)
                            break;

       //                 cout<<"jiii1"<<endl;
                        if(p->lChild!=NULL){
                            for(vector<dagNode*>::iterator it=p->lChild->father.begin(); it!=p->lChild->father.end();){
                                if((*it)==p)
                                {
                                    it = p->lChild->father.erase(it);
                                }
                                else
                                {
                                    ++it;
                                }
                            }
                        }
       //                 cout<<"jiii"<<endl;
                        if(p->rChild!=NULL){
                            for(vector<dagNode*>::iterator it=p->rChild->father.begin(); it!=p->rChild->father.end();){
                                if((*it)==p)
                                {
                                    it = p->rChild->father.erase(it);
                                }
                                else
                                {
                                    ++it;
                                }
                            }
                        }
                        while(p->lChild!=NULL&&p->lChild->father.size()==0){
                            p=p->lChild;
                            for(vector<dagNode*>::iterator it=dagArray[j]->elements.begin(); it!=dagArray[j]->elements.end();){
                                   if(*it==p){
                                     nodeStack.push_back(p);
                                     dagArray[j]->elements.erase(it);
                                     break;
                                   }
                                    ++it;
                            }
                            if(dagArray[j]->elements.size()==0)
                                break;
                            if(p->lChild!=NULL){
                                for(vector<dagNode*>::iterator it=p->lChild->father.begin(); it!=p->lChild->father.end();){
                                    if((*it)==p)
                                    {
                                        it = p->lChild->father.erase(it);
                                    }
                                    else
                                    {
                                        ++it;
                                    }
                                }
                            }
                            if(p->rChild!=NULL){
                                for(vector<dagNode*>::iterator it=p->rChild->father.begin(); it!=p->rChild->father.end();){
                                    if((*it)==p)
                                    {
                                        it =p->rChild->father.erase(it);
                                    }
                                    else
                                    {
                                        ++it;
                                    }
                                }
                            }
                        }
                        k=dagArray[j]->elements.size();//一旦有节点被消，就让k变为最末尾节点
                    }
                }
            }
            ///////////////////生成代码
            int countFineCode=0;
            for(int k=nodeStack.size()-1;k>=0;k--){
                if(nodeStack[k]->value=="+"||
                   nodeStack[k]->value=="-"||
                   nodeStack[k]->value=="*"||
                   nodeStack[k]->value=="/"||
                   nodeStack[k]->value=="=[]"){
                       for(int l=0;l<nodeStack[k]->var.size();l++){
                           if(l==0){
                               code* c=new code;
                               c->op=nodeStack[k]->value;
                               c->var3=nodeStack[k]->var[l];
                               c->var1=nodeStack[k]->lChild->var[0];
                               c->var2=nodeStack[k]->rChild->var[0];
                               if(c->var3.c_str()[strlen(c->var3.c_str())-1]=='$')
                                    c->var3.erase(strlen(c->var3.c_str())-1,1);
                               if(c->var1.c_str()[strlen(c->var1.c_str())-1]=='$')
                                    c->var1.erase(strlen(c->var1.c_str())-1,1);
                               if(c->var2.c_str()[strlen(c->var2.c_str())-1]=='$')
                                    c->var2.erase(strlen(c->var2.c_str())-1,1);

                               if(c->var1.c_str()[0]=='\''){
                                    c->var1.erase(0,1);
                                    c->var1.erase(strlen(c->var1.c_str())-1,1);
                               }
                               if(c->var2.c_str()[0]=='\''){
                                    c->var2.erase(0,1);
                                    c->var2.erase(strlen(c->var2.c_str())-1,1);
                               }
                               midCode[i-codeCount+countFineCode]=c;
                               countFineCode++;
                           }
                           else if(!(nodeStack[k]->var[l].c_str()[0]=='_'&&
                                    nodeStack[k]->var[l].c_str()[1]=='t')){
                               code* c=new code;
                               c->op=string("=");
                               c->var3=nodeStack[k]->var[l];
                               c->var1=nodeStack[k]->var[0];
                               if(c->var1.c_str()[0]=='\''){
                                    c->var1.erase(0,1);
                                    c->var1.erase(strlen(c->var1.c_str())-1,1);
                               }
                               if(c->var3.c_str()[strlen(c->var3.c_str())-1]=='$')
                                    c->var3.erase(strlen(c->var3.c_str())-1,1);
                               if(c->var1.c_str()[strlen(c->var1.c_str())-1]=='$')
                                    c->var1.erase(strlen(c->var1.c_str())-1,1);

                               midCode[i-codeCount+countFineCode]=c;
                               countFineCode++;
                           }
                       }
                   }
                else{
                    for(int l=1;l<nodeStack[k]->var.size();l++){
                        code* c=new code;
                        c->op=string("=");
                        c->var3=nodeStack[k]->var[l];
                        c->var1=nodeStack[k]->var[0];
                        if(c->var3.c_str()[strlen(c->var3.c_str())-1]=='$')
                            c->var3.erase(strlen(c->var3.c_str())-1,1);
                        if(c->var1.c_str()[strlen(c->var1.c_str())-1]=='$')
                            c->var1.erase(strlen(c->var1.c_str())-1,1);

                        midCode[i-codeCount+countFineCode]=c;
                        countFineCode++;
                    }
                }

            }

            for(int k=i;k<codeLength;k++){
                midCode[k-codeCount+countFineCode]=midCode[k];
            }
            codeLength-=codeCount-countFineCode;
        }
    }

int existInArray(string obj,string arr[],int length){
    for(int i=0;i<length;i++){
        if(arr[i]==obj){
            return 1;
        }
    }
    return 0;
}

int isVariable(string var){
    int ind=getLocation(var,"VAR");
    if(ind>=0&&symbolTable[ind]->level==0)
        return 0;
    if(var.length()>0){
        if(!(var.c_str()[0]>='0'&&var.c_str()[0]<='9')){
            if(var.length()>1){
                if(var.c_str()[0]=='_'&&var.c_str()[1]=='t'||var.c_str()[0]=='-')
                    return 0;
                if(var.c_str()[0]=='\'')
                    return 0;
            }
            return 1;
        }
    }
    return 0;
}

int removeRedundancy(string redundancy[],int length){
    for(int i=0;i<length;i++){
        for(int j=i+1;j<length;j++){
            if(redundancy[i]==redundancy[j]){
                for(int k=j;k<length-1;k++)
                    redundancy[k]=redundancy[k+1];
                j--;
                length--;
            }
        }
    }
    return length;
}

int calculateIn(string in[],
           string use[],
           int useLength,
           string out[],
           int outLength,
           string def[]
           ,int defLength){
    int length_=0;
    for(int i=0;i<outLength;i++){
        int j;
        for(j=0;j<defLength;j++){
            if(out[i]==def[j])
                break;
        }
        if(j==defLength){
            in[length_++]=out[i];
        }
    }
    for(int i=0;i<useLength;i++){
        in[length_++]=use[i];
    }
    return removeRedundancy(in,length_);
}


void dataFlowAnalysis(int start){
    nodeArrayLength=0;
    block* node_p;
    int jLabelCount=0;
    for(int i=start;midCode[i]->op!="END";i++){
        if(midCode[i]->op=="LABEL"){
            node_p=new block;
            node_p->preLength=0;
            node_p->sucLength=0;
            node_p->inChanged=0;
            node_p->defLength=0;
            node_p->useLength=0;
            node_p->inLength=0;
            node_p->outLength=0;
            node_p->label=midCode[i]->var3;
            if(nodeArrayLength>0&&nodeArray[nodeArrayLength-1]->label.substr(0,3)!="jmp"){
                node_p->pre[node_p->preLength++]=nodeArray[nodeArrayLength-1]->label;
                nodeArray[nodeArrayLength-1]->suc[nodeArray[nodeArrayLength-1]->sucLength++]=node_p->label;
            }
            nodeArray[nodeArrayLength++]=node_p;
            continue;
        }
        if(midCode[i]->op=="JG"||
           midCode[i]->op=="JLE"||
           midCode[i]->op=="JGE"||
           midCode[i]->op=="JL"||
           midCode[i]->op=="JE"||
           midCode[i]->op=="JNE"||
           midCode[i]->op=="JNEI"||
           midCode[i]->op=="JNEC"||
           midCode[i]->op=="JMP"
           ){
            if(isVariable(midCode[i]->var1)&&!existInArray(midCode[i]->var1,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var1;
            if(isVariable(midCode[i]->var2)&&!existInArray(midCode[i]->var2,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var2;
            node_p=new block;
            node_p->preLength=0;
            node_p->sucLength=0;
            node_p->inChanged=0;
            node_p->defLength=0;
            node_p->useLength=0;
            node_p->inLength=0;
            node_p->outLength=0;
            char str[20];
            itoa(jLabelCount++,str,10);
            string label_="jLabel"+string(str);
            node_p->label=label_;
            nodeArray[nodeArrayLength-1]->suc[nodeArray[nodeArrayLength-1]->sucLength++]=midCode[i]->var3;
            if(nodeArrayLength>0&&midCode[i]->op!="JMP"){
                node_p->pre[node_p->preLength++]=nodeArray[nodeArrayLength-1]->label;
                nodeArray[nodeArrayLength-1]->suc[nodeArray[nodeArrayLength-1]->sucLength++]=label_;
            }
            nodeArray[nodeArrayLength++]=node_p;
            continue;
           }
        if(midCode[i]->op=="CAllV"||midCode[i]->op=="PARA"){
            node_p->def[node_p->defLength++]=midCode[i]->var3;
        }//常量不分配寄存器

        if(midCode[i]->op=="=[]"){
            if(isVariable(midCode[i]->var2)&&!existInArray(midCode[i]->var2,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var2;
            if(isVariable(midCode[i]->var3)&&!existInArray(midCode[i]->var3,node_p->use,node_p->useLength))
                node_p->def[node_p->defLength++]=midCode[i]->var3;
        }
        if(midCode[i]->op=="[]="){
            if(isVariable(midCode[i]->var1)&&!existInArray(midCode[i]->var1,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var1;
            if(isVariable(midCode[i]->var2)&&!existInArray(midCode[i]->var2,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var2;
        }
        if(midCode[i]->op=="RETURN"||midCode[i]->op=="SETPARA"){
            if(isVariable(midCode[i]->var3)&&!existInArray(midCode[i]->var3,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var3;
        }
        if(midCode[i]->op=="PRINTF"){
            if(isVariable(midCode[i]->var2)&&!existInArray(midCode[i]->var2,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var2;
        }
        if(midCode[i]->op=="+"||
           midCode[i]->op=="-"||
           midCode[i]->op=="*"||
           midCode[i]->op=="/"||
           midCode[i]->op=="="||
           midCode[i]->op=="SCNAF"
           ){

            if(isVariable(midCode[i]->var1)&&!existInArray(midCode[i]->var1,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var1;
            if(isVariable(midCode[i]->var2)&&!existInArray(midCode[i]->var2,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var2;
            if(isVariable(midCode[i]->var3)&&!existInArray(midCode[i]->var3,node_p->use,node_p->useLength))
                node_p->def[node_p->defLength++]=midCode[i]->var3;
           }
        if(midCode[i]->op=="INT"||
           midCode[i]->op=="CHAR"){
            if(isVariable(midCode[i]->var1)&&!existInArray(midCode[i]->var1,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var1;
            if(isVariable(midCode[i]->var2)&&!existInArray(midCode[i]->var2,node_p->def,node_p->defLength))
                node_p->use[node_p->useLength++]=midCode[i]->var2;
           }

    }

//////计算in和out
    while(1){
        for(int i=0;i<nodeArrayLength;i++){
            int len=0;
            for(int j=0;j<nodeArray[i]->sucLength;j++){
                for(int k=0;k<nodeArrayLength;k++){
                    if(nodeArray[k]->label==nodeArray[i]->suc[j]){
                        for(int l=0;l<nodeArray[k]->inLength;l++)
                            nodeArray[i]->out[len++]=nodeArray[k]->in[l];
                    }
                }
            }
            nodeArray[i]->outLength=removeRedundancy(nodeArray[i]->out,len);
            int newLength=calculateIn(
            nodeArray[i]->in,
            nodeArray[i]->use,
            nodeArray[i]->useLength,
            nodeArray[i]->out,
            nodeArray[i]->outLength,
            nodeArray[i]->def,
            nodeArray[i]->defLength);
            if(nodeArray[i]->inLength!=newLength)
                nodeArray[i]->inChanged=1;
            else
                nodeArray[i]->inChanged=0;
            nodeArray[i]->inLength=newLength;
        }
        int i_;
        for(i_=0;i_<nodeArrayLength;i_++){
            if(nodeArray[i_]->inChanged==1){
                break;
            }
        }
        if(i_==nodeArrayLength)
            break;

        }

    return;
}

int indexInArray(string obj,string arr[],int length){
    for(int i=0;i<length;i++){
        if(obj==arr[i])
            return i;
    }
    return -1;
}

void sRegisterAllocation(int start){
    string stack[100];
    int stackTop=0;
    string stackSpill[100];
    int stackSpillTop=0;
    int graph[100][100]={0};
    int graph_b[100][100]={0};
    string varList[100];
    int dimension=0;
    dataFlowAnalysis(start);
/*
    for(int i=0;i<nodeArrayLength;i++){
        cout<<"-------------def--------------"<<endl;
        for(int j=0;j<nodeArray[i]->defLength;j++){
            cout<<nodeArray[i]->def[j]<<endl;
        }
        cout<<"-------------def--------------"<<endl;
            cout<<"-------------use--------------"<<endl;
        for(int j=0;j<nodeArray[i]->useLength;j++){
            cout<<nodeArray[i]->use[j]<<endl;
        }
            cout<<"-------------use--------------"<<endl;
    }
*/
//////////////构建冲突图
    for(int i=0;i<nodeArrayLength;i++){
//        cout<<"-------------in--------------"<<endl;
        for(int j=0;j<nodeArray[i]->inLength;j++){
//            cout<<nodeArray[i]->in[j]<<endl;
            if(!existInArray(nodeArray[i]->in[j],varList,dimension))
                varList[dimension++]=nodeArray[i]->in[j];
        }
//        cout<<"-------------in--------------"<<endl;
        for(int j=0;j<nodeArray[i]->inLength;j++){
            for(int k=j+1;k<nodeArray[i]->inLength;k++){
                int tem1=indexInArray(nodeArray[i]->in[j],varList,dimension);
                int tem2=indexInArray(nodeArray[i]->in[k],varList,dimension);
                if(tem1==-1||tem2==-1){
                    printf("yooooooooooooo");
                    exit(1);
                }
                graph[tem1][tem2]=1;
                graph[tem2][tem1]=1;
                graph_b[tem1][tem2]=1;
                graph_b[tem2][tem1]=1;
            }
        }
 //           cout<<"-------------out--------------"<<endl;
        for(int j=0;j<nodeArray[i]->outLength;j++){
 //           cout<<nodeArray[i]->out[j]<<endl;
            if(!existInArray(nodeArray[i]->out[j],varList,dimension))
                varList[dimension++]=nodeArray[i]->out[j];
        }
  //          cout<<"-------------out--------------"<<endl;
        for(int j=0;j<nodeArray[i]->outLength;j++){
            for(int k=j+1;k<nodeArray[i]->outLength;k++){
                int tem1=indexInArray(nodeArray[i]->out[j],varList,dimension);
                int tem2=indexInArray(nodeArray[i]->out[k],varList,dimension);
                if(tem1==-1||tem2==-1){
                    printf("yooooooooooooo1");
                    exit(1);
                }
                graph[tem1][tem2]=1;
                graph[tem2][tem1]=1;
                graph_b[tem1][tem2]=1;
                graph_b[tem2][tem1]=1;
            }
        }
    }
/////////////////////////图分解

int length=dimension;
int degree[100]={0};
//cout<<dimension<<endl;
for(int i=0;i<dimension;i++){
    for(int j=0;j<dimension;j++){
        if(graph[i][j]==1)
            degree[i]++;
    }
//    cout<<degree[i]<<" ";
//    cout<<endl;
}

for(int i=0,flag=0;dimension!=0;){
    if(i==0)
        flag=0;
    if(degree[i]<8&&!existInArray(varList[i],stack,stackTop)){
        flag=1;
        for(int j=0;j<dimension;j++){
            graph[i][j]=0;
            if(graph[j][i]==1)
                degree[j]--;
            graph[j][i]=0;
        }
        degree[i]=0;
        stack[stackTop++]=varList[i];
        length--;
    }
    i=(i+1)%dimension;
    if(i==0&&flag==0)
        break;

}


while(length!=0){
    int max_=0,maxIndex=0;
    for(int i=0;i<dimension;i++){
        if(degree[i]>max_){
            max_=degree[i];
            maxIndex=max_;
        }
    }
    stackSpill[stackSpillTop++]=varList[maxIndex];
    length--;
    for(int j=0;j<dimension;j++){
        graph[maxIndex][j]=0;
        if(graph[j][maxIndex]==1)
            degree[j]--;
        graph[j][maxIndex]=0;
    }
    degree[maxIndex]=0;

    for(int i=0,flag=0;;){

    if(i==0)
        flag=0;
    if(degree[i]<8&&!existInArray(varList[i],stack,stackTop)
        &&!existInArray(varList[i],stackSpill,stackSpillTop)){
        flag=1;
        for(int j=0;j<dimension;j++){
            graph[i][j]=0;
            if(graph[j][i]==1)
                degree[j]--;
            graph[j][i]=0;
        }
        degree[i]=0;
        stack[stackTop++]=varList[i];
        length--;
    }
    i=(i+1)%dimension;
    if(i==0&&flag==0)
        break;
    }
}
//////////////////图着色
string restoreList[100];
int restoreLength=0;
for(int i=stackTop-1;i>=0;i--){
    int sign_[8]={0};
    for(int j=0;j<restoreLength;j++){
        int tem1=indexInArray(stack[i],varList,dimension);
        int tem2=indexInArray(restoreList[j],varList,dimension);
        if(tem1==-1||tem2==-1){
            printf("yoooooooooooooh!");
            exit(1);
        }
        if(graph_b[tem1][tem2]==1){
            int reNum;
            string te_=sRegisterPool[restoreList[j]];
            sscanf(te_.erase(0,2).c_str(),"%d",&reNum);
            sign_[reNum]=1;
        }
    }
    for(int j=0;j<8;j++){
        if(sign_[j]==0){
            char str[10];
            sprintf(str,"%d",j);
            sRegisterPool.insert(make_pair(stack[i], "$s"+string(str)));

            restoreList[restoreLength++]=stack[i];
        }
    }
}
/*
map<string,string>::iterator  it=sRegisterPool.begin();
  for(;it!=sRegisterPool.end();++it)
            cout<<"key:"<<it->first
                    <<"value:"<<it->second<<endl;
  cout<<"----------------"<<endl;
*/
return;

}

void generateMIPS(){
    MIPSfile.open("test.asm");
    int mainFlag=0;
    int labelCount=0;
    int lastPoint=0;
    MIPSfile<<".data"<<endl;
    for(int i=0;i<codeLength;i++){
         if(midCode[i]->op=="BEGIN"){
            lev++;
            lastPoint=MIPStableLength;
            sRegisterPool.clear();
            sRegisterAllocation(i);
        }
        else if(midCode[i]->op=="END"){
            if(mainFlag==1){
                mainFlag=0;
                MIPSfile<<"EXIT:"<<endl;
            }
            else{
                returnAsm();
                lev--;
                MIPStableLength=lastPoint;
            }
        }
        else if(midCode[i]->op=="CONST"){
            if(sRegisterPool.find(midCode[i]->var3)!=sRegisterPool.end()){
                MIPSfile<<"li "<<sRegisterPool[midCode[i]->var3]<<","<<midCode[i]->var2<<endl;
            }
            if(lev==0){
                insertMIPSsign(midCode[i]->var1,midCode[i]->var3,lev,string("0"));
                definitionGlobalAsm(midCode[i]->var3,midCode[i]->var2,string("0"));
            }
            else{
                insertMIPSsign(midCode[i]->var1,midCode[i]->var3,lev,string("0"));
                definitionAsm(midCode[i]->var3,midCode[i]->var2);
 //               MIPSfile<<"addi $sp,$sp,-4"<<endl;
            }
        }

        else if(midCode[i]->op=="INT"||midCode[i]->op=="CHAR"){
       //     int index=getMIPSLocation(midCode[i]->var3);
       //     string lev=MIPSsymbolTable[index]->level;
            if(lev==0){
                if((midCode[i]->var2).length()!=0){
                    definitionGlobalAsm(midCode[i]->var3,string("0"),midCode[i]->var2);
                    insertMIPSsign(midCode[i]->op,midCode[i]->var3,lev,midCode[i]->var2);
                }
                else{
                    definitionGlobalAsm(midCode[i]->var3,string("0"),string("0"));
                    insertMIPSsign(midCode[i]->op,midCode[i]->var3,lev,string("0"));
                }
            }
            else{
                if((midCode[i]->var2).length()!=0){
                    insertMIPSsign(midCode[i]->op,midCode[i]->var3,lev,midCode[i]->var2);
                }
                else{
                    insertMIPSsign(midCode[i]->op,midCode[i]->var3,lev,string("0"));
   //                 MIPSfile<<"addi $sp,$sp,-4"<<endl;
                }
            }
        }//非全局变量的int a,char b之类的无需生成MIPS代码
        else if(midCode[i]->op=="LABEL"){
            if(labelCount==0){
                MIPSfile<<".text"<<endl;
                MIPSfile<<"addi $fp,$sp,0"<<endl;
                MIPSfile<<"j main"<<endl;
            }
            MIPSfile<<midCode[i]->var3<<":"<<endl;
            labelCount++;
            if(midCode[i-1]->op=="BEGIN"&&midCode[i]->var3!="main"){
                MIPSfile<<"sw $ra,4($sp)"<<endl;
            }
            else if(midCode[i-1]->op=="BEGIN"&&midCode[i]->var3=="main"){
                mainFlag++;
            }

            if(midCode[i-1]->op=="BEGIN"){
                int index=getLocation(midCode[i]->var3,string("FUNCTION"));
                int depth=-symbolTable[index]->depth;//depth为一个负数
                MIPSfile<<"addi $sp,$sp,"<<depth<<endl;
            }
        }

        else if(midCode[i]->op=="+"||midCode[i]->op=="-"||
        midCode[i]->op=="*"||midCode[i]->op=="/"){
            calculateAsm(midCode[i]->op,midCode[i]->var1,midCode[i]->var2,midCode[i]->var3);
        }
        else if(midCode[i]->op=="="){
            assignAsm(midCode[i]->var1,midCode[i]->var3);
        }
        else if(midCode[i]->op=="=[]"){
            getArrayAsm(midCode[i]->var1,midCode[i]->var2,midCode[i]->var3);
        }
        else if(midCode[i]->op=="[]="){
            assignArrayAsm(midCode[i]->var1,midCode[i]->var2,midCode[i]->var3);
        }
        else if(midCode[i]->op=="RETURN"&&mainFlag==0){
            int index=getMIPSLocation(midCode[i]->var1);
            if(index!=-1){
                if(sRegisterPool.find(midCode[i]->var1)!=sRegisterPool.end()){
                    MIPSfile<<"addi $v0,"<<sRegisterPool[midCode[i]->var1]<<",0"<<endl;
                }
                else{
                    if(MIPSsymbolTable[index]->level=="0"){
                        MIPSfile<<"la $t0,"<<MIPSsymbolTable[index]->name<<endl;
                        MIPSfile<<"lw $t0,0($t0)"<<endl;
                    }
                    else{
                        string addr=getAddress(midCode[i]->var1);
                        MIPSfile<<"addi $t0,$fp,-"<<addr<<endl;
                        MIPSfile<<"lw $t0,0($t0)"<<endl;
                    }
                    MIPSfile<<"addi $v0,$t0,0"<<endl;
                }
            }
            returnAsm();
        }
        else if(midCode[i]->op=="RETURN"&&mainFlag==1){
            MIPSfile<<"j "<<"EXIT"<<endl;
        }
        else if(midCode[i]->op=="PRINTF"){
            int l = (midCode[i]->var1).length();
            for(int j = 0 ;j < l ;j++){
                MIPSfile<<"addi $a0,$zero,"<<(midCode[i]->var1)[j]-'0'+48<<endl;
                MIPSfile<<"li $v0,11"<<endl;
                MIPSfile<<"syscall"<<endl;
            }
            int index=getMIPSLocation(midCode[i]->var2);
            if(index!=-1){
                if(sRegisterPool.find(midCode[i]->var2)!=sRegisterPool.end()){
                    MIPSfile<<"add $a0,$zero,"<<sRegisterPool[midCode[i]->var2]<<endl;
                    if(MIPSsymbolTable[index]->type=="CHAR")
                        MIPSfile<<"li $v0,11"<<endl;
                    else
                        MIPSfile<<"li $v0,1"<<endl;
                    MIPSfile<<"syscall"<<endl;
                }
                else{
                    if(MIPSsymbolTable[index]->level=="0"){
                        MIPSfile<<"la $t0,"<<MIPSsymbolTable[index]->name<<endl;
                        MIPSfile<<"lw $t0,0($t0)"<<endl;
                    }
                    else{
                        string addr=getAddress(midCode[i]->var2);
                        MIPSfile<<"addi $t0,$fp,-"<<addr<<endl;
                        MIPSfile<<"lw $t0,0($t0)"<<endl;
                    }
                    MIPSfile<<"add $a0,$zero,$t0"<<endl;
                    if(MIPSsymbolTable[index]->type=="CHAR")
                        MIPSfile<<"li $v0,11"<<endl;
                    else
                        MIPSfile<<"li $v0,1"<<endl;
                    MIPSfile<<"syscall"<<endl;
                }
            }
        }
        else if(midCode[i]->op=="SCANF"){
            int index=getMIPSLocation(midCode[i]->var3);
            if(sRegisterPool.find(midCode[i]->var3)!=sRegisterPool.end()){
                    if(MIPSsymbolTable[index]->type=="CHAR")
                        MIPSfile<<"li $v0,12"<<endl;
                    else
                        MIPSfile<<"li $v0,5"<<endl;
                    MIPSfile<<"syscall"<<endl;
                    MIPSfile<<"addi "<<sRegisterPool[midCode[i]->var3]<<",$v0,0"<<endl;
                }
            else{
                if(MIPSsymbolTable[index]->level=="0"){
                    MIPSfile<<"la $t0,"<<MIPSsymbolTable[index]->name<<endl;
                }
                else{
                    string addr=getAddress(midCode[i]->var3);
                    MIPSfile<<"addi $t0,$fp,-"<<addr<<endl;
                }
                if(MIPSsymbolTable[index]->type=="CHAR")
                    MIPSfile<<"li $v0,12"<<endl;
                else
                    MIPSfile<<"li $v0,5"<<endl;
                MIPSfile<<"syscall"<<endl;
                MIPSfile<<"sw $v0,0($t0)"<<endl;
            }
        }
        else if(midCode[i]->op=="JMP"){
            MIPSfile<<"j "<<midCode[i]->var3<<endl;
        }
        else if(midCode[i]->op=="JG"||midCode[i]->op=="JLE"||
                midCode[i]->op=="JGE"||midCode[i]->op=="JL"||
                midCode[i]->op=="JE"||midCode[i]->op=="JNE"){
                    JVar2VarAsm(midCode[i]->op,midCode[i]->var1,midCode[i]->var2,midCode[i]->var3);
                }
        else if(midCode[i]->op=="JNEI"||midCode[i]->op=="JNEC"){
                    JVar2ConAsm(midCode[i]->op,midCode[i]->var1,midCode[i]->var2,midCode[i]->var3);
        }
        else if(midCode[i]->op=="SETPARA"){
            MIPSfile<<"sw $s0,0($sp)"<<endl;
            MIPSfile<<"sw $s1,-4($sp)"<<endl;
            MIPSfile<<"sw $s2,-8($sp)"<<endl;
            MIPSfile<<"sw $s3,-12($sp)"<<endl;
            MIPSfile<<"sw $s4,-16($sp)"<<endl;
            MIPSfile<<"sw $s5,-20($sp)"<<endl;
            MIPSfile<<"sw $s6,-24($sp)"<<endl;
            MIPSfile<<"sw $s7,-28($sp)"<<endl;
            MIPSfile<<"sw $fp,-32($sp)"<<endl;
            MIPSfile<<"sw $fp,-32($sp)"<<endl;
            MIPSfile<<"addi $sp,$sp,-40"<<endl;
            int count_=0;
            while(midCode[i]->op=="SETPARA"){
            if(sRegisterPool.find(midCode[i]->var3)!=sRegisterPool.end())
                    MIPSfile<<"sw "<<sRegisterPool[midCode[i]->var3]<<","<<-4*count_<<"($sp)"<<endl;
            else{
                int index=getMIPSLocation(midCode[i]->var3);//不是标识符的情况
                if(index==-1){
                    MIPSfile<<"li $t0,"<<midCode[i]->var3<<endl;
                }
                else{
                    if(MIPSsymbolTable[index]->level=="0"){
                        MIPSfile<<"la $t0,"<<MIPSsymbolTable[index]->name<<endl;
                        MIPSfile<<"lw $t0,0($t0)"<<endl;
                    }
                    else{
                        string addr=getAddress(midCode[i]->var3);
                        MIPSfile<<"addi $t0,$fp,-"<<addr<<endl;
                        MIPSfile<<"lw $t0,0($t0)"<<endl;
                    }
                }
                    MIPSfile<<"sw $t0,"<<-4*count_<<"($sp)"<<endl;
                }
                count_++;
                i++;
            }
            MIPSfile<<"addi $fp,$sp,0"<<endl;
            i--;
        }
        else if(midCode[i]->op=="CALL"){


            int index_=getLocation(midCode[i]->var1,"FUNCTION");
            if(symbolTable[index_]->length==0){
                MIPSfile<<"sw $s0,0($sp)"<<endl;
                MIPSfile<<"sw $s1,-4($sp)"<<endl;
                MIPSfile<<"sw $s2,-8($sp)"<<endl;
                MIPSfile<<"sw $s3,-12($sp)"<<endl;
                MIPSfile<<"sw $s4,-16($sp)"<<endl;
                MIPSfile<<"sw $s5,-20($sp)"<<endl;
                MIPSfile<<"sw $s6,-24($sp)"<<endl;
                MIPSfile<<"sw $s7,-28($sp)"<<endl;
                MIPSfile<<"sw $fp,-32($sp)"<<endl;
                MIPSfile<<"addi $sp,$sp,-40"<<endl;
                MIPSfile<<"addi $fp,$sp,0"<<endl;
            }//对于无参数的函数要先做好fp,sp的操作
            MIPSfile<<"jal "<<midCode[i]->var1<<endl;
        }
        else if(midCode[i]->op=="CALLV"){

            int index_=getLocation(midCode[i]->var1,string("FUNCTION"));
            if(symbolTable[index_]->length==0){
                MIPSfile<<"sw $s0,0($sp)"<<endl;
                MIPSfile<<"sw $s1,-4($sp)"<<endl;
                MIPSfile<<"sw $s2,-8($sp)"<<endl;
                MIPSfile<<"sw $s3,-12($sp)"<<endl;
                MIPSfile<<"sw $s4,-16($sp)"<<endl;
                MIPSfile<<"sw $s5,-20($sp)"<<endl;
                MIPSfile<<"sw $s6,-24($sp)"<<endl;
                MIPSfile<<"sw $s7,-28($sp)"<<endl;
                MIPSfile<<"sw $fp,-32($sp)"<<endl;
                MIPSfile<<"addi $sp,$sp,-40"<<endl;
                MIPSfile<<"addi $fp,$sp,0"<<endl;
            }//对于无参数的函数要先做好fp,sp的操作
            MIPSfile<<"jal "<<midCode[i]->var1<<endl;
            if(sRegisterPool.find(midCode[i]->var3)!=sRegisterPool.end())
                    MIPSfile<<"addi "<<sRegisterPool[midCode[i]->var3]<<",$v0,0"<<endl;
            else{
                int index=getMIPSLocation(midCode[i]->var3);
                if(index==-1){
                    int index_=getLocation(midCode[i]->var1,string("FUNCTION"));//这里查语义分析时产生的符号表
                    insertMIPSsign(symbolTable[index_]->type,midCode[i]->var3,lev,string("0"));
                    index=getMIPSLocation(midCode[i]->var3);
                }
                if(MIPSsymbolTable[index]->level=="0"){
                    MIPSfile<<"la $t2,"<<MIPSsymbolTable[index]->name<<endl;
                }
                else{
                    string addr=getAddress(midCode[i]->var3);
                    MIPSfile<<"addi $t2,$fp,-"<<addr<<endl;
                }
                MIPSfile<<"sw $v0,0($t2)"<<endl;
            }
        }
        else if(midCode[i]->op=="PARA"){
            insertMIPSsign(midCode[i]->var1,midCode[i]->var3,lev,string("0"));
            if(sRegisterPool.find(midCode[i]->var3)!=sRegisterPool.end()){
                string addr1=getAddress(midCode[i]->var3);
                MIPSfile<<"addi $t0,$fp,-"<<addr1<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
                MIPSfile<<"addi "<<sRegisterPool[midCode[i]->var3]<<",$t0,0"<<endl;
            }
        }

    }

//        outfile<<midCode[i]->op<<","<<midCode[i]->var1<<","<<midCode[i]->var2<<","<<midCode[i]->var3<<endl;
}

void insertMIPSsign(string type,string name,int level,string length){
    if(MIPStableLength<1500){
        MIPSsign* c=new MIPSsign;
        c->name=name;
        c->type=type;
        char temp[64];
        sprintf(temp, "%d", level);
        string ttt(temp);
        c->level=ttt;
        c->length=length;
        MIPSsymbolTable[MIPStableLength++]=c;
    }
    else
        error(12);//12
}
int getMIPSLocation(string name){
    int i;
    for(i=MIPStableLength-1;i>=0;i--){
//       MIPSfile<<MIPSsymbolTable[i]->name<<"  "<<name.c_str();
        if(stricmp((MIPSsymbolTable[i]->name).c_str(),name.c_str())==0){
            break;
        }
    }
    return i;
}


/*
sRegister s0-s7
------
lastfp
-------
ret addres
-------
para1        fp
-------
paraX
...
-------
             sp
-------
*/

void returnAsm(){
    MIPSfile<<"addi $sp,$fp,40"<<endl;
    MIPSfile<<"lw $fp,-32($sp)"<<endl;
    MIPSfile<<"addi $t0,$sp,-36"<<endl;
    MIPSfile<<"lw $ra,0($t0)"<<endl;

    MIPSfile<<"lw $s0,0($sp)"<<endl;
    MIPSfile<<"lw $s1,-4($sp)"<<endl;
    MIPSfile<<"lw $s2,-8($sp)"<<endl;
    MIPSfile<<"lw $s3,-12($sp)"<<endl;
    MIPSfile<<"lw $s4,-16($sp)"<<endl;
    MIPSfile<<"lw $s5,-20($sp)"<<endl;
    MIPSfile<<"lw $s6,-24($sp)"<<endl;
    MIPSfile<<"lw $s7,-28($sp)"<<endl;

    MIPSfile<<"jr $ra"<<endl;
}
void getArrayAsm(string var1,string var2,string var3){
    if(sRegisterPool.find(var2)!=sRegisterPool.end()){
        MIPSfile<<"li $t1,4"<<endl;
        MIPSfile<<"mult "<<sRegisterPool[var2]<<",$t1"<<endl;
        MIPSfile<<"mflo $t0"<<endl;
    }
    else{
        int index2=getMIPSLocation(var2);//可能不是标识符
        if(index2==-1){
            MIPSfile<<"li $t0,"<<var2<<endl;
            MIPSfile<<"li $t1,4"<<endl;
            MIPSfile<<"mult $t0,$t1"<<endl;
            MIPSfile<<"mflo $t0"<<endl;
        }
        else{
            if(MIPSsymbolTable[index2]->level=="0"){
                MIPSfile<<"la $t0,"<<MIPSsymbolTable[index2]->name<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
                MIPSfile<<"li $t1,4"<<endl;
                MIPSfile<<"mult $t0,$t1"<<endl;
                MIPSfile<<"mflo $t0"<<endl;
            }
            else{
                string addr2=getAddress(var2);
                MIPSfile<<"addi $t0,$fp,-"<<addr2<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
                MIPSfile<<"li $t1,4"<<endl;
                MIPSfile<<"mult $t0,$t1"<<endl;
                MIPSfile<<"mflo $t0"<<endl;
            }
        }
    }

    int index1=getMIPSLocation(var1);  //var为数组名
    if(MIPSsymbolTable[index1]->level=="0"){
        MIPSfile<<"la $t1,"<<MIPSsymbolTable[index1]->name<<endl;
        MIPSfile<<"add $t0,$t1,$t0"<<endl;
        MIPSfile<<"lw $t0,0($t0)"<<endl;
    }
    else{
        string addr1=getAddress(var1);
        MIPSfile<<"addi $t1,$fp,-"<<addr1<<endl;
        MIPSfile<<"sub $t0,$t1,$t0"<<endl;
        MIPSfile<<"lw $t0,0($t0)"<<endl;
    }

    if(sRegisterPool.find(var3)!=sRegisterPool.end())
        MIPSfile<<"addi "<<sRegisterPool[var3]<<",$t0,0"<<endl;
    else{
        int index3=getMIPSLocation(var3);
        if(index3==-1){
            insertMIPSsign(MIPSsymbolTable[index1]->type,var3,lev,string("0"));
            index3=getMIPSLocation(var3);
        }
        if(MIPSsymbolTable[index3]->level=="0"){
            MIPSfile<<"la $t1,"<<MIPSsymbolTable[index3]->name<<endl;
        }
        else{
            string addr=getAddress(var3);
            MIPSfile<<"addi $t1,$fp,-"<<addr<<endl;
        }
        MIPSfile<<"sw $t0,0($t1)"<<endl;
    }
}
void assignAsm(string var1,string var3){
    string var3type="INT";
    if(sRegisterPool.find(var1)!=sRegisterPool.end()&&
       sRegisterPool.find(var3)!=sRegisterPool.end())
        MIPSfile<<"addi "<<sRegisterPool[var3]<<","<<sRegisterPool[var1]<<",0"<<endl;
    else if(sRegisterPool.find(var1)==sRegisterPool.end()&&
            sRegisterPool.find(var3)!=sRegisterPool.end()){
        int index1=getMIPSLocation(var1);//可能不是标识符
        if(index1==-1){
            if(var1.c_str()[0]=='\''){
                var1.erase(0,1);
                var1.erase(var1.length()-1,1);
                var3type="CHAR";
            }
            MIPSfile<<"li $t0,"<<var1<<endl;
        }
        else{
            if(MIPSsymbolTable[index1]->level=="0"){
                MIPSfile<<"la $t0,"<<MIPSsymbolTable[index1]->name<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
            }
            else{
                string addr1=getAddress(var1);
                MIPSfile<<"addi $t0,$fp,-"<<addr1<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
            }
            var3type=MIPSsymbolTable[index1]->type;
        }
        MIPSfile<<"addi "<<sRegisterPool[var3]<<",$t0,0"<<endl;
    }
    else if(sRegisterPool.find(var1)!=sRegisterPool.end()&&
            sRegisterPool.find(var3)==sRegisterPool.end()){
        int index3=getMIPSLocation(var3);
        var3type=MIPSsymbolTable[index3]->type;
        if(index3==-1){
            insertMIPSsign(var3type,var3,lev,string("0"));
            index3=getMIPSLocation(var3);
        }
        if(MIPSsymbolTable[index3]->level=="0"){
            MIPSfile<<"la $t1,"<<MIPSsymbolTable[index3]->name<<endl;
        }
        else{
            string addr=getAddress(var3);
            MIPSfile<<"addi $t1,$fp,-"<<addr<<endl;
        }
        MIPSfile<<"sw "<<sRegisterPool[var1]<<",0($t1)"<<endl;
    }
    else{
        int index1=getMIPSLocation(var1);//可能不是标识符
        if(index1==-1){
            if(var1.c_str()[0]=='\''){
                var1.erase(0,1);
                var1.erase(var1.length()-1,1);
                var3type="CHAR";
            }
            MIPSfile<<"li $t0,"<<var1<<endl;
        }
        else{
            if(MIPSsymbolTable[index1]->level=="0"){
                MIPSfile<<"la $t0,"<<MIPSsymbolTable[index1]->name<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
            }
            else{
                string addr1=getAddress(var1);
                MIPSfile<<"addi $t0,$fp,-"<<addr1<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
            }
            var3type=MIPSsymbolTable[index1]->type;
        }
        int index3=getMIPSLocation(var3);
        if(index3==-1){
            insertMIPSsign(var3type,var3,lev,string("0"));
            index3=getMIPSLocation(var3);
        }
        if(MIPSsymbolTable[index3]->level=="0"){
            MIPSfile<<"la $t1,"<<MIPSsymbolTable[index3]->name<<endl;
        }
        else{
            string addr=getAddress(var3);
            MIPSfile<<"addi $t1,$fp,-"<<addr<<endl;
        }
        MIPSfile<<"sw $t0,0($t1)"<<endl;
    }
}
void assignArrayAsm(string var3,string var2,string var1){
    if(sRegisterPool.find(var2)!=sRegisterPool.end()){
        MIPSfile<<"li $t1,4"<<endl;
        MIPSfile<<"mult "<<sRegisterPool[var2]<<",$t1"<<endl;
        MIPSfile<<"mflo $t0"<<endl;
    }
    else{
        int index2=getMIPSLocation(var2);//可能不是标识符
        if(index2==-1){
            MIPSfile<<"li $t0,"<<var2<<endl;
            MIPSfile<<"li $t1,4"<<endl;
            MIPSfile<<"mult $t0,$t1"<<endl;
            MIPSfile<<"mflo $t0"<<endl;
            }
        else{
            if(MIPSsymbolTable[index2]->level=="0"){
                MIPSfile<<"la $t0,"<<MIPSsymbolTable[index2]->name<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
                MIPSfile<<"li $t1,4"<<endl;
                MIPSfile<<"mult $t0,$t1"<<endl;
                MIPSfile<<"mflo $t0"<<endl;
            }
            else{
                string addr2=getAddress(var2);
                MIPSfile<<"addi $t0,$fp,-"<<addr2<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
                MIPSfile<<"li $t1,4"<<endl;
                MIPSfile<<"mult $t0,$t1"<<endl;
                MIPSfile<<"mflo $t0"<<endl;
            }
        }
    }
    int index1=getMIPSLocation(var1);
    if(MIPSsymbolTable[index1]->level=="0"){
        MIPSfile<<"la $t1,"<<MIPSsymbolTable[index1]->name<<endl;
        MIPSfile<<"add $t0,$t1,$t0"<<endl;
    }
    else{
        string addr1=getAddress(var1);
        MIPSfile<<"addi $t1,$fp,-"<<addr1<<endl;
        MIPSfile<<"sub $t0,$t1,$t0"<<endl;
    }

    if(sRegisterPool.find(var3)!=sRegisterPool.end()){
        MIPSfile<<"sw "<<sRegisterPool[var3]<<",0($t0)"<<endl;
    }
    else{
        int index3=getMIPSLocation(var3);
        if(index3==-1){
            MIPSfile<<"li $t1,"<<var3<<endl;
        }
        else{
            if(MIPSsymbolTable[index3]->level=="0"){
                MIPSfile<<"la $t1,"<<MIPSsymbolTable[index3]->name<<endl;
                MIPSfile<<"lw $t1,0($t1)"<<endl;
            }
            else{
                string addr=getAddress(var3);
                MIPSfile<<"addi $t1,$fp,-"<<addr<<endl;
                MIPSfile<<"lw $t1,0($t1)"<<endl;
            }
        }
        MIPSfile<<"sw $t1,0($t0)"<<endl;
    }
}
void definitionGlobalAsm(string name,string value,string length){
    if(length=="0"){
        MIPSfile<<name<<":.word "<<value<<endl;
    }
    else{
        MIPSfile<<name<<":.word 0:"<<length<<endl;
    }
}
string getAddress(string name){
    int index=getMIPSLocation(name);
    string lev1;
    char x=lev1[0];
    int i;
    int len=0;
    for(i=index-1;i>=0;i--){
        lev1=MIPSsymbolTable[i]->level;
        if(lev1!="1")
            break;
        if(MIPSsymbolTable[i]->length=="0")
            len++;
        len+=atoi((MIPSsymbolTable[i]->length).c_str());
    }
    int addr=len*4;
    char temp[64];
    sprintf(temp, "%d", addr);
    string ttt(temp);
    return ttt;
}
void definitionAsm(string name,string value){
    MIPSfile<<"li $t0,"<<value<<endl;
    string addr=getAddress(name);
    MIPSfile<<"addi $t1,$fp,-"<<addr<<endl;
    MIPSfile<<"sw $t0,0($t1)"<<endl;
}
void calculateAsm(string op,string var1,string var2,string var3){
    string comp1,comp2,comp3;
    int index;
    if(sRegisterPool.find(var1)!=sRegisterPool.end())
        comp1=sRegisterPool[var1];
    else{
        index=getMIPSLocation(var1);//可能不是标识符
        if(index==-1){
            MIPSfile<<"li $t0,"<<var1<<endl;
        }
        else{
            string lev1=MIPSsymbolTable[index]->level;
            if(lev1=="0"){
                MIPSfile<<"la $t0,"<<MIPSsymbolTable[index]->name<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
            }
            else{
                string addr=getAddress(var1);
                MIPSfile<<"addi $t0,$fp,-"<<addr<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
            }
        }
        comp1=string("$t0");
    }

    if(sRegisterPool.find(var2)!=sRegisterPool.end())
        comp2=sRegisterPool[var2];
    else{
        index=getMIPSLocation(var2);//可能不是标识符
        if(index==-1){
            MIPSfile<<"li $t1,"<<var2<<endl;
        }
        else{
            string lev1=MIPSsymbolTable[index]->level;
            if(lev1=="0"){
                MIPSfile<<"la $t1,"<<MIPSsymbolTable[index]->name<<endl;
                MIPSfile<<"lw $t1,0($t1)"<<endl;
            }
            else{
                string addr=getAddress(var2);
                MIPSfile<<"addi $t1,$fp,-"<<addr<<endl;
                MIPSfile<<"lw $t1,0($t1)"<<endl;
            }
        }
        comp2=string("$t1");
    }

    if(sRegisterPool.find(var3)!=sRegisterPool.end())
        comp3=sRegisterPool[var3];
    else{
        index=getMIPSLocation(var3);
        if(index==-1){
            insertMIPSsign(string("INT"),var3,lev,string("0"));
            index=getMIPSLocation(var3);
        }
        if(MIPSsymbolTable[index]->level=="0"){
            MIPSfile<<"la $t2,"<<MIPSsymbolTable[index]->name<<endl;
        }
        else{
            string addr=getAddress(var3);
            MIPSfile<<"addi $t2,$fp,-"<<addr<<endl;
        }
        comp3="$t0";
    }
    if(op=="+"){
        MIPSfile<<"add "<<comp3<<","<<comp1<<","<<comp2<<endl;
    }
    else if(op=="-"){
        MIPSfile<<"sub "<<comp3<<","<<comp1<<","<<comp2<<endl;
    }
    else if(op=="*"){
        MIPSfile<<"mult "<<comp1<<","<<comp2<<endl;
        MIPSfile<<"mflo "<<comp3<<endl;
    }
    else{
        MIPSfile<<"div "<<comp1<<","<<comp2<<endl;
        MIPSfile<<"mflo "<<comp3<<endl;
    }
    if(sRegisterPool.find(var3)==sRegisterPool.end())
        MIPSfile<<"sw $t0,0($t2)"<<endl;
}
void JVar2VarAsm(string op,string a,string b,string c){
    string comp1,comp2;
    int index;
    if(sRegisterPool.find(a)!=sRegisterPool.end())
        comp1=sRegisterPool[a];
    else{
        index=getMIPSLocation(a);//可能不是标识符
        if(index==-1){
            MIPSfile<<"li $t0,"<<a<<endl;
        }
        else{
            string lev1=MIPSsymbolTable[index]->level;
            if(lev1=="0"){
                MIPSfile<<"la $t0,"<<MIPSsymbolTable[index]->name<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
            }
            else{
                string addr=getAddress(a);
                MIPSfile<<"addi $t0,$fp,-"<<addr<<endl;
                MIPSfile<<"lw $t0,0($t0)"<<endl;
            }
        }
        comp1=string("$t0");
    }
    if(sRegisterPool.find(b)!=sRegisterPool.end())
        comp2=sRegisterPool[b];
    else{
        index=getMIPSLocation(b);//可能不是标识符
        if(index==-1){
            MIPSfile<<"li $t1,"<<b<<endl;
            }
        else{
            string lev1=MIPSsymbolTable[index]->level;
            if(lev1=="0"){
                MIPSfile<<"la $t1,"<<MIPSsymbolTable[index]->name<<endl;
                MIPSfile<<"lw $t1,0($t1)"<<endl;
            }
            else{
                string addr=getAddress(b);
                MIPSfile<<"addi $t1,$fp,-"<<addr<<endl;
                MIPSfile<<"lw $t1,0($t1)"<<endl;
            }
        }
        comp2=string("$t1");
    }
    if(op=="JG"){
        MIPSfile<<"sub $t2,"<<comp1<<","<<comp2<<endl;
        MIPSfile<<"bgtz $t2,"<<c<<endl;
    }
    else if(op=="JLE"){
        MIPSfile<<"sub $t2,"<<comp1<<","<<comp2<<endl;
        MIPSfile<<"blez $t2,"<<c<<endl;
    }
    else if(op=="JGE"){
        MIPSfile<<"sub $t2,"<<comp1<<","<<comp2<<endl;
        MIPSfile<<"bgez $t2,"<<c<<endl;
    }
    else if(op=="JL"){
        MIPSfile<<"sub $t2,"<<comp1<<","<<comp2<<endl;
        MIPSfile<<"bltz $t2,"<<c<<endl;
    }
    else if(op=="JE")
        MIPSfile<<"beq "<<comp1<<","<<comp2<<","<<c<<endl;
    else//op==JNE
        MIPSfile<<"bne "<<comp1<<","<<comp2<<","<<c<<endl;
}
void JVar2ConAsm(string op,string a,string b,string c){
    string comp0;
    if(sRegisterPool.find(a)!=sRegisterPool.end())
        comp0=sRegisterPool[a];
    else{
        int index=getMIPSLocation(a);
        string lev1=MIPSsymbolTable[index]->level;
        if(lev1=="0"){
            MIPSfile<<"la $t0,"<<MIPSsymbolTable[index]->name<<endl;
            MIPSfile<<"lw $t0,0($t0)"<<endl;
        }
        else{
            string addr=getAddress(a);
            MIPSfile<<"addi $t0,$fp,-"<<addr<<endl;
            MIPSfile<<"lw $t0,0($t0)"<<endl;
        }
        comp0=string("$t0");
    }
    if(op=="JNEI"){
        MIPSfile<<"addi $t1,$zero,"<<b<<endl;//小心多位数字
        MIPSfile<<"bne "<<comp0<<",$t1,"<<c<<endl;
    }
    else if(op=="JNEC"){
        MIPSfile<<"addi $t1,$zero,"<<b[0]-'0'+48<<endl;
        MIPSfile<<"bne "<<comp0<<",$t1,"<<c<<endl;
    }
}
