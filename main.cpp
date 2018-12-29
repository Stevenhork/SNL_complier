#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//token�ṹ��
struct Token
{
    Token(string str, int pos)
    {
        this->type = str;
        this->pos = pos;
    }
    string type;
    int pos;
};

vector<string> IdTable;               //ȫ�ֱ������ʷ������õ��ı�ʾ����
vector<int> NbTable;              //ȫ�ֱ������ʷ������õ���INTCֵ��

#define ERROR_INVALID_SYMBOL  1     //�궨����󣺷Ƿ�����
#define NO_ERROR              0     //�궨��   ��û�д���

int error = NO_ERROR;               //ȫ�ֱ�������¼�ʷ������еĴ�������

/*
 *�ж��ַ��ǲ��������ַ�
 */
bool IsOther(char ch)
{
    if (ch >= 'A'&&ch <= 'Z')
        return false;
    if (ch >= 'a'&&ch <= 'z')
        return false;
    if (ch >= '0'&&ch <= '9')
        return false;
    return true;
}
/*
 *�ж��ַ����ǲ��ǹؼ���
 */
bool IsKeyWord(string str)
{
    if (str == "integer")
        return true;
    if (str == "char")
        return true;
    if (str == "program")
        return true;
    if (str == "array")
        return true;
    if (str == "of")
        return true;
    if (str == "record")
        return true;
    if (str == "end")
        return true;
    if (str == "var")
        return true;
    if (str == "procedure")
        return true;
    if (str == "begin")
        return true;
    if (str == "if")
        return true;
    if (str == "then")
        return true;
    if (str == "else")
        return true;
    if (str == "fi")
        return true;
    if (str == "while")
        return true;
    if (str == "do")
        return true;
    if (str == "endwh")
        return true;
    if (str == "read")
        return true;
    if (str == "write")
        return true;
    if (str == "return")
        return true;
    if (str == "type")
        return true;
    return false;
}

/*
 *�����ַ����ڱ��е�λ�ã�û�оͼӵ���󣬲������±�
 */
int AddIdTable(string str)
{
    for (int i = 0; i < IdTable.size(); i++)
    {
        if (str == IdTable[i])
            return i;
    }
    IdTable.push_back(str);
    return IdTable.size()-1;
}

/*
 *���������ڱ��е�λ�ã�û�оͼӵ���󣬲������±�
 */
int AddNbTable(string str)
{
    int num = atoi(str.c_str());
    for (int i = 0; i < NbTable.size(); i++)
    {
        if (num == NbTable[i])
            return i;
    }
    NbTable.push_back(num);
    return NbTable.size() - 1;
}

/*
 *�ʷ�����ɨ�����ÿ�ε��÷���һ��Tokenָ��
 */
Token *Scanner(FILE *pf)
{
    char ch = 0;
    string tmpStr = "";
    Token * pToken = NULL;
LS0://���ݵ�һ���ַ�ȷ����������
    ch = fgetc(pf);
    if (ch != EOF)
    {
        if ((ch >= 'A' &&ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            goto LS1;
        if (ch >= '0' &&ch <= '9')
            goto LS2;
        if (ch == '+')
            goto LS3;
        if (ch == '-')
            goto LS4;
        if (ch == '*')
            goto LS5;
        if (ch == '/')
            goto LS6;
        if (ch == '<')
            goto LS7;
        if (ch == ';')
            goto LS8;
        if (ch == ':')
            goto LS9;
        if (ch == ',')
            goto LS10;
        if (ch == '.')
            goto LS11;
        if (ch == '=')
            goto LS12;
        if (ch == '[')
            goto LS13;
        if (ch == ']')
            goto LS14;
        if (ch == '(')
            goto LS15;
        if (ch == ')')
            goto LS16;
        if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')
            goto LS17;
        goto LS18;
    }
    else
    {
        return NULL;
    }
LS1://��ʾ���͹ؼ���
    {
        tmpStr += ch;
        ch = fgetc(pf);

        if ((ch >= 'A' &&ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' &&ch <= '9'))
            goto LS1;
        if (IsOther(ch))
        {
            ungetc(ch, pf);//�Ѷ������ַ��Żص��ļ�����
            if (IsKeyWord(tmpStr))
            {
                //�ؼ���
                pToken = new Token("$"+tmpStr,-1);
                return pToken;
            }
            else
            {
                //���ǹؼ���,�Ǳ�ʾ��
                int pos = AddIdTable(tmpStr);
                pToken = new Token("$id", pos);
                return pToken;
            }
        }
    }
LS2://����
    {
        tmpStr += ch;
        ch = fgetc(pf);
        if (ch >= '0' &&ch <= '9')
            goto LS2;
        if (IsOther(ch))
        {
            ungetc(ch, pf);
            int pos = AddNbTable(tmpStr);
            pToken = new Token("$INTC", pos);
            return pToken;
        }
    }
LS3://'+'
    {
        pToken = new Token("$+", -1);
        return pToken;
    }
LS4://'-'
    {
        pToken = new Token("$-", -1);
        return pToken;
    }
LS5://'*'
    {
        pToken = new Token("$*", -1);
        return pToken;
    }
LS6://'/'
    {
        pToken = new Token("$/", -1);
        return pToken;
    }
LS7://'<'
    {
        pToken = new Token("$<", -1);
        return pToken;
    }
LS8://';'
    {
        pToken = new Token("$;", -1);
        return pToken;
    }
LS9://':'
    {
        ch = fgetc(pf);
        if (ch == '=')
        {
            pToken = new Token("$:=", -1);
            return pToken;
        }
        if (IsOther(ch))
        {
            error = ERROR_INVALID_SYMBOL;
            printf("����:��:�����ǺϷ��ķ���\n");
            return NULL;
        }
    }
LS10://','
    {
        pToken = new Token("$comma", -1);
        return pToken;
    }
LS11://'.'
    {
        pToken = new Token("$.", -1);
        return pToken;
    }
LS12://'='
    {
        pToken = new Token("$=", -1);
        return pToken;
    }
LS13://'['
    {
        pToken = new Token("$[", -1);
        return pToken;
    }
LS14://']'
    {
        pToken = new Token("$]", -1);
        return pToken;
    }
LS15://'('
    {
        pToken = new Token("$(", -1);
        return pToken;
    }
LS16://')'
    {
        pToken = new Token("$)", -1);
        return pToken;
    }
LS17://�հ׷�
    {
        goto LS0;
    }
LS18://other
    {
        error = ERROR_INVALID_SYMBOL;//����ȫ�ֱ���error
        printf("���󣺺��зǷ�����( %c )\n", ch);//��ӡ������Ϣ
        return NULL;
    }

}

/*
 *������,���argc���ڵ���2,argv[1]ΪԴ�ļ���������Ĭ��Ϊsnl.txt
 */
int main(int argc, char ** argv)
{
    //����Դ�ļ�
    string filename;
    if (argc >= 2)
        filename = argv[1];
    else
        filename = "snl.txt";

    //��Դ�ļ�
    FILE *pf = fopen(filename.c_str(),"r");

    if (!pf)
    {
        printf("���ļ�ʧ��!\n");
        return -1;
    }

    vector <Token> result;
    Token  * pToken =  NULL;
    while ((pToken = Scanner(pf)) != NULL)
    {
        result.push_back(*pToken);
        delete pToken;
        pToken = NULL;
    }

    fclose(pf);

    if (error == NO_ERROR)
    {
        pf = fopen((filename + ".token").c_str(), "w+");

        for (auto &iter : result)
        {
            if (iter.type == "$id" || iter.type == "$INTC")
            {
                printf("(%-10s, [%2d] )\n", iter.type.c_str(), iter.pos);
                fprintf(pf, "(%s,[%d])\n", iter.type.c_str(), iter.pos);
            }
            else
            {
                printf("(%-10s, \"  \" )\n", iter.type.c_str());
                fprintf(pf, "(%s,\"\")\n", iter.type.c_str());
            }
        }
        fclose(pf);

        pf = fopen((filename + ".idtable").c_str(), "w+");
        for (int i = 0; i < IdTable.size(); i++)
        {
            fprintf(pf, "%s\n", IdTable[i].c_str());
        }
        fclose(pf);

        pf = fopen((filename + ".nbtable").c_str(), "w+");
        for (int i = 0; i < NbTable.size(); i++)
        {
            fprintf(pf, "%d\n", NbTable[i]);
        }
        fclose(pf);
    }
    system("pause");
}
