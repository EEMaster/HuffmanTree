#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"HuffmanTreeHead.h"

int main()
{
    unsigned int TreeWeight[LNumber];//保存每个字母出现次数的数组
    HTNode HTree[2*LNumber-1];//最终生成的Huffman树
    char* HCode[LNumber];//保存每个字母的Huffman编码
    char KeyCode[DeCodeLength];
    char Decode[StringLength];
    int DeCodeFlat;
    int i;

    for(i=0;i<LNumber;i++)  TreeWeight[i]=0;
    for(i=0;i<LNumber;i++) HCode[i]=(char*)malloc(CodeLength*(sizeof(char)));


    FileReader("character.txt",TreeWeight,LNumber);//打开文件并把字母出现次数保存在数组中

    InitTree(HTree,LNumber,TreeWeight);
    HuffmanCoding(HTree,HCode,LNumber);

    for(i=0;i<LNumber;i++)
    {
        printf("字母%c的Huffman编码为%s\n",i+33,HCode[i]);
    }

    WriteCode("Huffmancode.txt",HCode,LNumber);
    printf("请输入编码：(输入-1退出)\n");
    gets(KeyCode);
    while(strcmp(KeyCode,"-1")!=0)
    {
        DeCodeFlat=HuffmanDecode(KeyCode,HTree,Decode);
        if(1==DeCodeFlat)
            printf("解码后的字符串为：%s\n",Decode);
        if(0==DeCodeFlat)
            {
                printf("解码后的字符串为：%s\n",Decode);
                printf("输入的编码有误！\n");
            }
        printf("请输入编码：(输入-1退出)\n");
        gets(KeyCode);
    }
    return 0;
}
