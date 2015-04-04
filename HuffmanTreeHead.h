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

void FileReader(char* FileName,unsigned int TreeWeight[],int Letter);//���ļ��ж�ȡ�ַ���������������

void Select(HuffmanTree HT,int Number,int* Node1,int* Node2);//��HT[]��ѡ��parentΪ0��weight��С��������㣬����ŷֱ�ΪNode1,Node2

void InitTree(HuffmanTree HT,int Number,unsigned int TreeWeight[]);//��ʼ����

void HuffmanCoding(HuffmanTree HT,char* HC[],int LetterNumber);//����Huffman��

int HuffmanDecode(char* HuffCode,HuffmanTree HT,char StrDecode[]);//Huffman����ĺ���

void ReCode(char* HuffCode[],int Number);//�޸ı���

void WriteCode(char* FileName,char* HCode[],int Letters);//������д���ļ�����ȥ
#endif // HUFFMANTREEHEAD_H_INCLUDED
