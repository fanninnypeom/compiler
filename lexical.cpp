
/*
a-z A-Z ID
0-9 NUM
?????????????'??'?????????????'??'???????'??'???????' CHARVALUE
"???????????32,33,35-126??ASCII?????" STRING
const  CONST 1
int  INT  2
char CHAR 3
void VOID 4
main MAIN 5
if  IF 6
else ELSE 7
while WHILE  8
switch SWITCH 9
case CASE 10
default DEFAULT 11
scanf SCANF 12
printf PRINTF 13
return RETURN 14
+ PLUS
- MINUS
* STAR/MULTIPLY
/ DIVISION
< LESS
<= LESSEQ
=  EQUAL
== JEQUAL
!= NEQUAL
> GREATER
>= GREATEREQ
_ UNDERLINE
; SEMI ???
, COMMA ????
. DOT ????
( LPAR
) RPAR
{ LBRACE
} RBRACE
' SINGLEQUOTE
" QUOTE
[ LBRACKET
] RBRACKET
  SPACE?????
: COLON ???

*/

#include "global.h"

char* p;
char* pLast1;
char* pLast2;
char* pLast3;


char Token[100];
int TokenCount=0;
string symbol=string("null");
int num;
char chValue;
char stringValue[100];
char* IDName;
int End=0;
map<string,int>symbolNum;
int lineNum=1;
char tempLine[100];
int lineCount=0;
int endNum=0;

char t[10000];

int clearToken()
{
    TokenCount = 0;
    return 0;
}
int GetChar()
{
    p++;
    if(*p=='\n'){
        
        char* p_r=p+1;
        while(!(*p_r=='\n'||*p_r=='\0'))
            tempLine[lineCount++]=*(p_r++);
        tempLine[lineCount]='\0';
        lineCount=0;
    }
    
    return 0;
}
int isSpace()
{
    if (*p == ' ')
        return 1;
    else
        return 0;
}
int isNewline()
{
    if (*p == '\n'){
        lineNum++;
        return 1;
    }
    else
        return 0;
}
int isTab()
{
    if (*p == '\t')
        return 1;
    else
        return 0;
}
int isLetter()
{
    if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z'))
        return 1;
    else
        return 0;
}
int isCharInString()
{
    if ((int)*p >= 32 && (int)*p <= 126 && (int)*p != 34)
        return 1;
    else
        return 0;
}
int isDigit()
{
    if (*p >= '0' && *p <= '9')
        return 1;
    else
        return 0;
}
int isExclamation(){
    if (*p =='!')
        return 1;
    else
        return 0;
}
int catToken()
{
    Token[TokenCount] = *p;
    Token[TokenCount + 1] = '\0';
    TokenCount++;
    return 0;
}
int retract()
{
    p--;
    return 0;
}
int reserver()
{
    if (strcmp(Token, "const") == 0)
    {
        symbol = "CONST";
        return 1;
    }
    else if (strcmp(Token, "int") == 0)
    {
        symbol = "INT";
        return 2;
    }
    else if (strcmp(Token, "char") == 0)
    {
        symbol = "CHAR";
        return 3;
    }
    else if (strcmp(Token, "void") == 0)
    {
        symbol = "VOID";
        return 4;
    }
    else if (strcmp(Token, "main") == 0)
    {
        symbol = "MAIN";
        return 5;
    }
    else if (strcmp(Token, "if") == 0)
    {
        symbol = "IF";
        return 6;
    }
    else if (strcmp(Token, "else") == 0)
    {
        symbol = "ELSE";
        return 7;
    }
    else if (strcmp(Token, "while") == 0)
    {
        symbol = "WHILE";
        return 8;
    }
    else if (strcmp(Token, "switch") == 0)
    {
        symbol = "SWITCH";
        return 9;
    }
    else if (strcmp(Token, "case") == 0)
    {
        symbol = "CASE";
        return 10;
    }
    else if (strcmp(Token, "default") == 0)
    {
        symbol = "DEFAULT";
        return 11;
    }
    else if (strcmp(Token, "scanf") == 0)
    {
        symbol = "SCANF";
        return 12;
    }
    else if (strcmp(Token, "printf") == 0)
    {
        symbol = "PRINTF";
        return 13;
    }
    else if (strcmp(Token, "return") == 0)
    {
        symbol = "RETURN";
        return 14;
    }
    else
        return 0;
}
int transNum()
{
    return atoi(Token);
}
int isColon()
{
    if (*p == ':')
        return 1;
    return 0;
}
int isEqu()
{
    if (*p == '=')
        return 1;
    return 0;
}
int isPlus()
{
    if (*p == '+')
        return 1;
    return 0;
}
int isMinus()
{
    if (*p == '-')
        return 1;
    return 0;
}
int isStar()
{
    if (*p == '*')
        return 1;
    return 0;
}
int isLpar()
{
    if (*p == '(')
        return 1;
    return 0;
}
int isRpar()
{
    if (*p == ')')
        return 1;
    return 0;
}
int isComma()
{
    if (*p == ',')
        return 1;
    return 0;
}
int isSemi()
{
    if (*p == ';')
        return 1;
    return 0;
}
int isDivi()
{
    if (*p == '/')
        return 1;
    return 0;
}
int isLess()
{
    if (*p == '<')
        return 1;
    return 0;
}

int isGreater()
{
    if (*p == '>')
        return 1;
    return 0;
}

int isUnderline()
{
    if (*p == '_')
        return 1;
    return 0;
}
int isDot()
{
    if (*p == '.')
        return 1;
    return 0;
}

int isLbrace()
{
    if (*p == '{')
        return 1;
    return 0;
}
int isRbrace()
{
    if (*p == '}')
        return 1;
    return 0;
}

int isSinglequote()
{
    if (*p == '\'')
        return 1;
    return 0;
}
int isQuote()
{
    if (*p == '\"')
        return 1;
    return 0;
}

int isLbracket()
{
    if (*p == '[')
        return 1;
    return 0;
}
int isRbracket()
{
    if (*p == ']')
        return 1;
    return 0;
}

/*
1 ���ű�����
2 �ֳ���������
3 �м�����̫��
4 ���ú����Ĳ�������
5 ȱ��������
6 �����������Ͳ�ƥ��
7 δ�����ı�ʶ��
8 ����û�з���ֵ
9 ���������������ܲ�������
10 ȱ����������
11 ȱ��ð��
12 �м�������������
13 ����һ����ʶ��
14 ����һ���������ͱ�ʶ��
15 ��Ҫһ��;��,��[
16 ���Ϸ�������!���ܺ��з������ַ�����ǰ����
17 �����Ķ���ȱ��=��
18 ȱ��;
19 ȱ��һ��}
20 ȱ��һ��)
21 ȱ��һ��{
22 ȱ��һ��(
23 ���Ϸ�������
24 ����һ��=
25 ȱ��һ��[
26 ȱ��һ��]
27 case��������ʹ�ó������Ƚ�
28 ����һ��:
29 ȱ��һ��'
30 ���Ϸ����ַ�
31 �ַ���û��˫����
32 �ǲ��ǻ��������ֵ��ַ�
33 ������!�ǲ��Ϸ���
34 ���Ϸ��ıȽ�������
35 ����һ��case�ؼ���
*/

int error(int e)
{
    if(endNum>5)
        exit(1);
    switch(e){
        case 1:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   symbolTable overFlow"<<endl;break;
        case 2:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   procedureTable overFlow"<<endl;break;
        case 3:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   too much mid code"<<endl;break;
        case 4:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   number of parameters not match"<<endl;break;
        case 5:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   ecpect )"<<endl;break;
        case 6:cout<<"Compile warning: The "<<lineNum<<" line:  "<<symbol<<"   parameter type not match"<<endl;break;
        case 7:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   undefined identifier"<<endl;break;
        case 8:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   function don't have return value"<<endl;break;
        case 9:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   funtion and array can't be a factor'"<<endl;break;
        case 10:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect ["<<endl;break;
        case 11:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   ecpect :"<<endl;break;
        case 12:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   too much temp var"<<endl;break;
        case 13:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect a identifier"<<endl;break;
        case 14:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect a type identifier"<<endl;break;
        case 15:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect  ; , [ "<<endl;break;
        case 16:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   illegal number!contain character or leading zero"<<endl;break;
        case 17:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   const definition expect ="<<endl;break;
        case 18:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect ;"<<endl;break;
        case 19:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect }"<<endl;break;
        case 20:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect )"<<endl;break;
        case 21:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect {"<<endl;break;
        case 22:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect ("<<endl;break;
        case 23:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   illegal factor"<<endl;break;
        case 24:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect ="<<endl;break;
        case 25:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect ["<<endl;break;
        case 26:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect ]"<<endl;break;
        case 27:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   case must use number or char to compare"<<endl;break;
        case 28:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect :"<<endl;break;
        case 29:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect '"<<endl;break;
        case 30:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   illegal character"<<endl;break;
        case 31:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect \""<<endl;break;
        case 32:cout<<"Compile finished"<<endl;break;
        case 33:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   single ! is illegal"<<endl;break;
        case 34:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   illegal compare operator"<<endl;break;
        case 35:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   expect a case"<<endl;break;
        case 36:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   var redefined!"<<endl;break;
        case 37:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   kind unmatch! var? array? or function?"<<endl;break;
        case 38:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   const can't be assigned!"<<endl;break;
        case 39:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   function no return value!"<<endl;break;
        case 40:cout<<"Compile error: The "<<lineNum<<" line:  "<<symbol<<"   function should't hava return value!"<<endl;break;
    }
    if(e!=32)
        errorNum++;
    else
        endNum++;
    cout<<tempLine<<endl;
}
int getsym()
{
    clearToken();
    while (isSpace() || isNewline() || isTab())
        GetChar();
    if (isLetter() || isUnderline())
    {
        while (isLetter() || isDigit() || isUnderline())
        {
            catToken();
            GetChar();
        }
        retract();
        int resultValue = reserver();
        if (resultValue == 0)
        {
            symbol = "ID";
            for(int z=0;Token[z]!='\0';z++)
                if(Token[z]>='A'&&Token[z]<='Z'){
                    Token[z]+=32;
                }
            IDName = Token;
        }
    }
    else if (isDigit())
    {
        while (isDigit())
        {
            catToken();
            GetChar();
        }
        retract();
        num = transNum();
        symbol = "NUM";
    }
    else if (isColon())
        symbol = "COLON";
    else if (isEqu())
    {
        GetChar();
        if (isEqu())
            symbol = "JEQUAL";
        else
        {
            retract();
            symbol = "EQUAL";
        }
    }
    else if (isLess())
    {
        GetChar();
        if (isEqu())
            symbol = "LESSEQ";
        else
        {
            retract();
            symbol = "LESS";
        }
    }
    else if(isExclamation()){
        GetChar();
        if(isEqu())
            symbol="NEQUAL";
        else{
            error(33);
        }
    }
    else if (isGreater())
    {
        GetChar();
        if (isEqu())
            symbol = "GREATEREQ";
        else
        {
            retract();
            symbol = "GREATER";
        }
    }
    else if (isUnderline())
        symbol = "UNDERLINE";
    else if (isPlus())
        symbol = "PLUS";
    else if (isMinus())
        symbol = "MINUS";
    else if (isStar())
        symbol = "STAR";
    else if (isLpar())
        symbol = "LPAR";
    else if (isRpar())
        symbol = "RPAR";
    else if (isComma())
        symbol = "COMMA";
    else if (isSemi())
        symbol = "SEMI";
    else if (isDot())
        symbol = "DOT";
    else if (isLbrace())
        symbol = "LBRACE";
    else if (isRbrace())
        symbol = "RBRACE";
    else if (isLbracket())
        symbol = "LBRACKET";
    else if (isRbracket())
        symbol = "RBRACKET";
    else if (isSinglequote())
    {
        GetChar();
        if (isPlus() || isStar() || isDivi() || isMinus() || isLetter() || isUnderline() || isDigit())
        {
            chValue = *p;
            GetChar();
            if (isSinglequote())
                symbol = "CHARVALUE";
            else{
                error(29);
                symbol = "CHARVALUE";
            }
        }
        else{
            error(30);
            chValue = *p;
            symbol = "CHARVALUE";
        }
    }
    else if (isQuote())
    {
        GetChar();
        int count = 0;
        while (isCharInString())
        {
            stringValue[count] = *p;
            count++;
            GetChar();
        }
        stringValue[count] = '\0';
        if (isQuote())
            symbol = "STRING";
        else{
            error(31);
            symbol = "STRING";
        }
    }
    else if (isEqu())
        symbol = "EQUAL";
    else if (isDivi())
    {
        GetChar();
        if (isStar())
        {
            do
            {
                do
                {
                    GetChar();
                } while (!isStar());
                do
                {
                    GetChar();
                    if (isDivi())
                        return 0;
                } while (isStar());
            } while (!isStar());
        }
        retract();
        symbol = "DIVISION";
    }
    else
        error(32);
    return 0;
}

void nextSym()
{
    pLast3 = pLast2;
    pLast2 = pLast1;
    pLast1 = p;
    getsym();
    GetChar();
//    cout<<symbol<<endl;
}

void traceSym(){
    char* omg=p;
    p= pLast1;
    pLast1 = pLast2;
    pLast2 = pLast3;
    for(char* om=p;om<omg;om++){
        if(*om=='\n'){
            lineNum--;
        }
    }
}

int getCode()
{
    symbolNum.insert(map<string, int>::value_type("ID", 1));
    symbolNum.insert(make_pair("NUM", 2));
    symbolNum.insert(make_pair("CHARVALUE", 3));
    symbolNum.insert(make_pair("STRING", 4));
    symbolNum.insert(make_pair("CONST", 5));
    symbolNum.insert(make_pair("INT", 6));
    symbolNum.insert(make_pair("CHAR", 7));
    symbolNum.insert(make_pair("MAIN", 8));
    symbolNum.insert(make_pair("IF", 9));
    symbolNum.insert(make_pair("ELSE", 10));
    symbolNum.insert(make_pair("WHILE", 11));
    symbolNum.insert(make_pair("SWITCH", 12));
    symbolNum.insert(make_pair("CASE", 13));
    symbolNum.insert(make_pair("DEFAULT", 14));
    symbolNum.insert(make_pair("SCANF", 15));
    symbolNum.insert(make_pair("PRINTF", 16));
    symbolNum.insert(make_pair("RETURN", 17));
    symbolNum.insert(make_pair("PLUS", 18));
    symbolNum.insert(make_pair("MINUS", 19));
    symbolNum.insert(make_pair("STAR", 20));
    symbolNum.insert(make_pair("DIVISION", 21));
    symbolNum.insert(make_pair("LESS", 22));
    symbolNum.insert(make_pair("LESSEQ", 23));
    symbolNum.insert(make_pair("EQUAL", 24));
    symbolNum.insert(make_pair("JEQUAL", 25));
    symbolNum.insert(make_pair("GREATER", 26));
    symbolNum.insert(make_pair("GREATEREQ", 27));
    symbolNum.insert(make_pair("UNDERLINE", 28));
    symbolNum.insert(make_pair("SEMI", 29));
    symbolNum.insert(make_pair("COMMA", 30));
    symbolNum.insert(make_pair("DOT", 31));
    symbolNum.insert(make_pair("LPAR", 32));
    symbolNum.insert(make_pair("RPAR", 33));
    symbolNum.insert(make_pair("LBRACE", 34));
    symbolNum.insert(make_pair("RBRACE", 35));
    symbolNum.insert(make_pair("SINGLEQUOTE", 36));
    symbolNum.insert(make_pair("QUOTE", 37));
    symbolNum.insert(make_pair("LBRACKET", 38));
    symbolNum.insert(make_pair("RBRACKET", 39));
    symbolNum.insert(make_pair("VOID", 40));
    symbolNum.insert(make_pair("COLON", 41));
    symbolNum.insert(make_pair("NEQUAL", 42));


    ifstream iFile;
    ofstream oFile;
    char s[50];
    cout<<"Please input file name"<<endl;
    cin>>s;
  //  iFile.open("14061081_test.txt");
    iFile.open(s);
    if(iFile.fail()) {
         cout<<"file not exist!"<<endl; exit(1);
         }
    int count = 0;
    p = t;
    pLast1 = t;
    pLast2 = t;
    pLast3 = t;

    char ch;
    while (iFile.get(ch))
    {
        t[count] = ch;
        count++;
    }
    t[count] = '\0';

    return 0;
}
