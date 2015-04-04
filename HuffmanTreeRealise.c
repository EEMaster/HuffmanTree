#include"HuffmanTreeHead.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*TreeWeight[]数组保存了每个字母出现的次数*/
/*0~25号元素分别保存A~Z字母出现次数*/
void FileReader(char* FileName,unsigned int TreeWeight[],int LetterNumber)
{
    FILE* fp;
    char TempLetter;
    int i;
    fp=fopen(FileName,"r");
    if(fp==NULL)
        printf("文件打开失败！\n");
    else
    {
        printf("open successfully!\n");
        for(i=0;i<LetterNumber;i++)
            TreeWeight[i]=0;
        TempLetter=getc(fp);
        while(TempLetter!=EOF)
        {
            TreeWeight[TempLetter-33]++;
            TempLetter=getc(fp);
        }
        fclose(fp);

    }
}

void Select(HuffmanTree HT,int Number,int* Node1,int* Node2)
{
    HuffmanTree SelectTree;
    unsigned int MinWeight;
    int i;
    SelectTree=HT;
    for(i=0;i<Number;i++)     //将MinWeight设置为第一个可用的最小值
        if(SelectTree[i].IfUsed==0)
            {
                MinWeight=SelectTree[i].weight;
                *Node1=i;
                break;
            }

    for(;i<Number;i++)
    {
        if((MinWeight>SelectTree[i].weight)&&(SelectTree[i].IfUsed!=1))
        {
            *Node1=i;
            MinWeight=SelectTree[i].weight;
        }
    }
    (HT+*Node1)->IfUsed=1;//将选中的元素设置为已用
    for(i=0;i<Number;i++)//将MinWeight设置为第一个可用的最小值
        if(SelectTree[i].IfUsed==0)
            {
                MinWeight=SelectTree[i].weight;
                *Node2=i;
                break;
            }
    for(;i<Number;i++)
    {
            if((MinWeight>SelectTree[i].weight)&&(SelectTree[i].IfUsed!=1))
            {
                *Node2=i;
                MinWeight=SelectTree[i].weight;
            }
    }
    (HT+*Node2)->IfUsed=1;//将选中的元素设置为已用
}


/*编号为i的结点保存了第i个字母的信息（使用情况，孩子，权）*/
void InitTree(HuffmanTree HT,int Number,unsigned int TreeWeight[])
{
    int i;
    int NodeNumber;
    NodeNumber=2*Number-1;
    for(i=0;i<Number;i++)
    {

        (HT+i)->IfUsed=0;
        (HT+i)->lchild=0;
        (HT+i)->parent=0;
        (HT+i)->rchild=0;
        (HT+i)->weight=TreeWeight[i];
    }
    for(;i<NodeNumber;i++)
    {
        (HT+i)->IfUsed=0;
        (HT+i)->lchild=0;
        (HT+i)->parent=0;
        (HT+i)->rchild=0;
        (HT+i)->weight=0;
    }
}

void HuffmanCoding(HuffmanTree HT,char* HC[],int LetterNumber)
{
    int NodeNumber;//LetterNumber为字母数，即为叶子结点，总结点为NodeNumber,满足关系为NodeNumber=2*LetterNumber-1
    int i,j;
    char TempCode[CodeLength];
    int TempNode;
    int ForwardNode;
    int StartPossition;
    int NodeSelected1,NodeSelected2;//记录选出来的权最小的两个结点

    NodeNumber=2*LetterNumber-1;
    for(i=LetterNumber;i<NodeNumber;i++)//建立树
    {

        Select(HT,i,&NodeSelected1,&NodeSelected2);
        (HT+NodeSelected1)->parent=i;
        (HT+NodeSelected2)->parent=i;
        (HT+i)->lchild=NodeSelected1;
        (HT+i)->rchild=NodeSelected2;
        (HT+i)->weight=(HT+NodeSelected1)->weight+(HT+NodeSelected2)->weight;
        //printf("i=%d  Node1=%d  HT%d.weight=%u  Node2=%d  HT%d.weight=%u\n",i,NodeSelected1,NodeSelected1,(HT+NodeSelected1)->weight,NodeSelected2,NodeSelected2,(HT+NodeSelected2)->weight);
    }
    /*打印树*/
    //printf("Print the whole tree\n");
    //for(i=0;i<NodeNumber;i++)
    //{
    //    printf("(HT+%d)->weight=%u  parent=%u  lchild=%u  rchild=%u\n",i,(HT+i)->weight,(HT+i)->parent,(HT+i)->lchild,(HT+i)->rchild);
    //}

    for(i=0;i<LetterNumber;i++)
    {
        StartPossition=0;
        for(j=0;j<CodeLength;j++) TempCode[j]='\0';
        for(TempNode=i,ForwardNode=((HT+i)->parent);ForwardNode!=0;TempNode=ForwardNode,ForwardNode=((HT+TempNode)->parent))
            {
                if(((HT+ForwardNode)->lchild)==TempNode)
                {
                    TempCode[StartPossition]='0';
                    StartPossition++;
                }
                else
                {
                    TempCode[StartPossition]='1';
                    StartPossition++;
                }
            }
        HC[i]=(char*)malloc((strlen(TempCode))*sizeof(char));
        strcpy(HC[i],TempCode);
    }
    ReCode(HC,LetterNumber);
}

int HuffmanDecode(char* HuffCode,HuffmanTree HT,char StrDecode[])
{
    int TempPointer;//用来移动的指针
    int LetterPossiton;
    char* CodePointer;
    CodePointer=(char*)malloc(CodeLength*sizeof(char));
    LetterPossiton=0;
    CodePointer=HuffCode;
    TempPointer=2*LNumber-2;//从根结点开始
    while((*CodePointer)!='\0')
    {
        if(((HT+TempPointer)->lchild)==0&&((HT+TempPointer)->rchild)==0)
            TempPointer=2*LNumber-2;
        if((*CodePointer)=='0')
            TempPointer=(HT+TempPointer)->lchild;
        else
            TempPointer=(HT+TempPointer)->rchild;
        if(((HT+TempPointer)->lchild)==0&&((HT+TempPointer)->rchild)==0)
        {
            StrDecode[LetterPossiton]=TempPointer+33;
            LetterPossiton++;
        }
        CodePointer++;
    }
    StrDecode[LetterPossiton]='\0';
    if(((HT+TempPointer)->lchild!=0)||((HT+TempPointer)->rchild)!=0)
        return 0;
    else
        return 1;
}

void ReCode(char* HuffCode[],int Number)
{
    int i,j;
    int Length;
    char TempChar;
    for(i=0;i<Number;i++)
    {
        Length=strlen(HuffCode[i]);
        for(j=0;j<Length/2;j++)
        {
            TempChar=*(HuffCode[i]+j);
            *(HuffCode[i]+j)=*(HuffCode[i]+Length-j-1);
            *(HuffCode[i]+Length-j-1)=TempChar;
        }
    }
}


void WriteCode(char* FileName,char* HCode[],int Letters)
{
    FILE* fp;
    int i;
    fp=fopen(FileName,"w");
    if(fp==NULL)
        printf("文件打开失败！\n");
    else
    {
        for(i=0;i<Letters;i++)
            fprintf(fp,"字母%c的Huffman编码为%s\n",i+33,HCode[i]);
    }
    fclose(fp);
}
