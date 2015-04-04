#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"HuffmanTreeHead.h"

int main()
{
    unsigned int TreeWeight[LNumber];//����ÿ����ĸ���ִ���������
    HTNode HTree[2*LNumber-1];//�������ɵ�Huffman��
    char* HCode[LNumber];//����ÿ����ĸ��Huffman����
    char KeyCode[DeCodeLength];
    char Decode[StringLength];
    int DeCodeFlat;
    int i;

    for(i=0;i<LNumber;i++)  TreeWeight[i]=0;
    for(i=0;i<LNumber;i++) HCode[i]=(char*)malloc(CodeLength*(sizeof(char)));


    FileReader("character.txt",TreeWeight,LNumber);//���ļ�������ĸ���ִ���������������

    InitTree(HTree,LNumber,TreeWeight);
    HuffmanCoding(HTree,HCode,LNumber);

    for(i=0;i<LNumber;i++)
    {
        printf("��ĸ%c��Huffman����Ϊ%s\n",i+33,HCode[i]);
    }

    WriteCode("Huffmancode.txt",HCode,LNumber);
    printf("��������룺(����-1�˳�)\n");
    gets(KeyCode);
    while(strcmp(KeyCode,"-1")!=0)
    {
        DeCodeFlat=HuffmanDecode(KeyCode,HTree,Decode);
        if(1==DeCodeFlat)
            printf("�������ַ���Ϊ��%s\n",Decode);
        if(0==DeCodeFlat)
            {
                printf("�������ַ���Ϊ��%s\n",Decode);
                printf("����ı�������\n");
            }
        printf("��������룺(����-1�˳�)\n");
        gets(KeyCode);
    }
    return 0;
}
