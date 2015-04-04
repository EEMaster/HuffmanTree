#ifndef HUFFMANTREEHEAD_H_INCLUDED
#define HUFFMANTREEHEAD_H_INCLUDED
#define CodeLength 100
#define LNumber 94
#define DeCodeLength 200
#define StringLength 100
typedef struct{
unsigned int weight;
unsigned int parent,lchild,rchild;
int IfUsed;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

void FileReader(char* FileName,unsigned int TreeWeight[],int Letter);//从文件中读取字符并贮存在数组中

void Select(HuffmanTree HT,int Number,int* Node1,int* Node2);//在HT[]中选择parent为0且weight最小的两个结点，其序号分别为Node1,Node2

void InitTree(HuffmanTree HT,int Number,unsigned int TreeWeight[]);//初始化树

void HuffmanCoding(HuffmanTree HT,char* HC[],int LetterNumber);//构造Huffman树

int HuffmanDecode(char* HuffCode,HuffmanTree HT,char StrDecode[]);//Huffman解码的函数

void ReCode(char* HuffCode[],int Number);//修改编码

void WriteCode(char* FileName,char* HCode[],int Letters);//将编码写到文件里面去
#endif // HUFFMANTREEHEAD_H_INCLUDED
