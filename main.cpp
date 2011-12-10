// rbt.cpp: ®ЇаҐ¤Ґ«пҐв в®зЄг ўе®¤  ¤«п Є®­б®«м­®Ј® ЇаЁ«®¦Ґ­Ёп.
//

#include <stdio.h>
#include <string.h>
#define RED 0
#define BLACK 1
#define INSERT 100
#define DELETE 500

class RBT
{
private:
	struct Node;
	Node *pRoot;
	void LeftRotate(Node *pX);
	void RightRotate(Node *pX);
	void FixAfterInsert(Node *pX);
	void FixAfterDelete(Node *pX);
	void Removing(Node *pX);
public:
	RBT();
	~RBT();
	int Insert(int data);
	int Delete(int data);
	void Print(Node *pX, int level);
};

struct RBT::Node
{	int color;
	int data;
	Node *pLeft;
	Node *pRight;
	Node *pParent;
};

RBT::RBT()
{	pRoot=0;
};

RBT::~RBT()
{	Removing(pRoot);
};

void RBT::Removing(Node *pX)
{	if (pX!=0 && pX->pLeft!=0) Removing(pX->pLeft);
	else if (pX!=0 && pX->pRight!=0) Removing(pX->pRight);
	     else delete pX;
};

void RBT::LeftRotate(Node *pX)
{	//ЋЇҐа жЁп ­Ґў®§¬®¦­ , Ґб«Ё г н«Ґ¬Ґ­в  Їа ўл© бл­ ®вбгвбвўгҐв
	if (pX->pRight==0) return;

	//“бв ­ ў«Ёў Ґ¬ Y - Їа ўл© бл­
	Node *pY=pX->pRight;

	//‹Ґў®Ґ Ї®¤¤ҐаҐў® Їа ў®Ј® бл­  § ¬Ґй Ґв Їа ў®Ј® бл­ 
	pX->pRight=pY->pLeft;
	if (pX->pRight!=0) pX->pRight->pParent=pX;

	//Љ®аҐ­м ЇҐаҐ­ Їа ў«пҐвбп ®в X Є Y
	if (pX->pParent==0) pRoot=pY;
	else if (pX==pX->pParent->pLeft) pX->pParent->pLeft=pY;
		 else pX->pParent->pRight=pY;

	//X бв ­®ўЁвбп «Ґўл¬ бл­®¬ Y
	pY->pLeft=pX;
	pX->pParent=pY;
};

void RBT::RightRotate(Node *pX)
{	//ЋЇҐа жЁп ­Ґў®§¬®¦­ , Ґб«Ё г н«Ґ¬Ґ­в  «Ґўл© бл­ ®вбгвбвўгҐв
	if (pX->pLeft==0) return;

	//“бв ­ ў«Ёў Ґ¬ Y - «Ґўл© бл­
	Node *pY=pX->pLeft;

	//Џа ў®Ґ Ї®¤¤ҐаҐў® «Ґў®Ј® бл­  § ¬Ґй Ґв «Ґў®Ј® бл­ 
	pX->pLeft=pY->pRight;
	if (pX->pLeft!=0) pX->pLeft->pParent=pX;

	//Љ®аҐ­м ЇҐаҐ­ Їа ў«пҐвбп ®в X Є Y
	if (pX->pParent==0) pRoot=pY;
	else if (pX==pX->pParent->pLeft) pX->pParent->pLeft=pY;
		 else pX->pParent->pRight=pY;

	//X бв ­®ўЁвбп Їа ўл¬ бл­®¬ Y
	pY->pRight=pX;
	pX->pParent=pY;
};

int RBT::Insert(int data)
{	//Џ®ЁбЄ
	Node *pX, *pPred;
	pX=pRoot;
	pPred=0;
	while (pX!=0)
	{	if (data==pX->data)
		{	printf("Node is extist.\n");
			return 0;
		};
		pPred=pX;
		if (data<pX->data) pX=pX->pLeft;
		else pX=pX->pRight;
	};
	//pPred -  ¤аҐб а®¤ЁвҐ«п, г Є®в®а®Ј® Ўг¤Ґв бл­

	//ўл¤Ґ«пҐ¬ ¬Ґбв® Ї®¤ ­®ўл© г§Ґ«
	pX=new Node;
	pX->pParent=pPred;
	pX->pLeft=0;
	pX->pRight=0;
	pX->data=data;
	pX->color=RED;

	//Џ®¬Ґй Ґ¬ г§Ґ« ў ¤ҐаҐў®
	if (pPred==0) pRoot=pX;
	else if (data<pPred->data) pPred->pLeft=pX;
		 else pPred->pRight=pX;

	FixAfterInsert(pX);

	return 1;
};

void RBT::FixAfterInsert(Node *pX)
{	//‚®ббв ­®ў«Ґ­ЁҐ Єа б­®-зса­ле бў®©бвў ¤ҐаҐў 
	/* check Red-Black properties */
    while (pX!=pRoot && pX->pParent->color==RED)
	{	/* we have a violation */
        if (pX->pParent == pX->pParent->pParent->pLeft)
		{	Node *pY = pX->pParent->pParent->pRight;
            if (pY!=0 && pY->color == RED)
			{	/* uncle is RED */
                pX->pParent->color = BLACK;
                pY->color = BLACK;
                pX->pParent->pParent->color = RED;
                pX = pX->pParent->pParent;
            } else {
				/* uncle is BLACK */
                if (pX == pX->pParent->pRight)
				{	/* make x a left child */
                    pX = pX->pParent;
                    LeftRotate(pX);
                }

                /* recolor and rotate */
                pX->pParent->color = BLACK;
                pX->pParent->pParent->color = RED;
                RightRotate(pX->pParent->pParent);
            }
        } else {
            /* mirror image of above code */
            Node *pY = pX->pParent->pParent->pLeft;
            if (pY!=0 && pY->color == RED)
			{	/* uncle is RED */
                pX->pParent->color = BLACK;
                pY->color = BLACK;
                pX->pParent->pParent->color = RED;
                pX = pX->pParent->pParent;
            } else {
                /* uncle is BLACK */
                if (pX == pX->pParent->pLeft)
				{   pX = pX->pParent;
                    RightRotate(pX);
                }
                pX->pParent->color = BLACK;
                pX->pParent->pParent->color = RED;
                LeftRotate(pX->pParent->pParent);
            }
        }
    }
    pRoot->color = BLACK;
	Print(pRoot, 0);
};

int RBT::Delete(int data)
{	//Џ®ЁбЄ
	Node *pZ, *pPred;
	bool found=false;
	pZ=pRoot;
	pPred=0;
	while (pZ!=0)
	{	if (data==pZ->data)
		{	found=true;
			break;
		};
		pPred=pZ;
		if (data<pZ->data) pZ=pZ->pLeft;
		else pZ=pZ->pRight;
	};

	if (!found)
	{	printf("This node is not exists\n");
		return 0;
	}

	Node *pX, *pY;

	if (pZ!=0)
	{	//delete node z from tree

		if (pZ->pLeft == 0 || pZ->pRight == 0) {
			/* y has a NIL node as a child */
			pY = pZ;
		} else {
			/* find tree successor with a NIL node as a child */
			pY = pZ->pRight;
			while (pY->pLeft != 0) pY = pY->pLeft;
		}

		/* x is y's only child */
		if (pY->pLeft != 0)
			pX = pY->pLeft;
		else
			pX = pY->pRight;

		/* remove y from the parent chain */
		if (pX) pX->pParent = pY->pParent;
		if (pY->pParent)
			if (pY == pY->pParent->pLeft)
				pY->pParent->pLeft = pX;
			else
				pY->pParent->pRight = pX;
		else
			pRoot = pX;

		if (pY != pZ) pZ->data = pY->data;


		if (pY->color == BLACK)
			FixAfterDelete(pX);



		Print(pRoot,0);
	};

	return 1;
}

void RBT::FixAfterDelete(Node *pX)
{	while (pX != pRoot && pX->color == BLACK) {
        if (pX == pX->pParent->pLeft) {
            Node *pW = pX->pParent->pRight;
            if (pW->color == RED) {
                pW->color = BLACK;
                pX->pParent->color = RED;
                LeftRotate(pX->pParent);
                pW = pX->pParent->pRight;
            }
            if (pW->pLeft->color == BLACK && pW->pRight->color == BLACK) {
                pW->color = RED;
                pX = pX->pParent;
            } else {
                if (pW->pRight->color == BLACK) {
                    pW->pLeft->color = BLACK;
                    pW->color = RED;
                    RightRotate(pW);
                    pW = pX->pParent->pRight;
                }
                pW->color = pX->pParent->color;
                pX->pParent->color = BLACK;
                pW->pRight->color = BLACK;
                LeftRotate(pX->pParent);
                pX = pRoot;
            }
        } else {
            Node *pW = pX->pParent->pLeft;
            if (pW->color == RED) {
                pW->color = BLACK;
                pX->pParent->color = RED;
                RightRotate(pX->pParent);
                pW = pX->pParent->pLeft;
            }
            if (pW->pRight->color == BLACK && pW->pLeft->color == BLACK) {
                pW->color = RED;
                pX = pX->pParent;
            } else {
                if (pW->pLeft->color == BLACK) {
                    pW->pRight->color = BLACK;
                    pW->color = RED;
                    LeftRotate(pW);
                    pW = pX->pParent->pLeft;
                }
                pW->color = pX->pParent->color;
                pX->pParent->color = BLACK;
                pW->pLeft->color = BLACK;
                RightRotate(pX->pParent);
                pX = pRoot;
            }
        }
    }
    pX->color = BLACK;
};

void RBT::Print(Node* pX, int level)
{	if (pX->pLeft!=0) Print(pX->pLeft, level+1);
	for (int i=0; i<level; i++)	printf("     ");

	printf("%5i", pX->data);
	if (pX->color==RED) printf("*");
	printf("\n");

	if (pX->pRight!=0) Print(pX->pRight, level+1);
};

bool StrToNum(char *s, int& A){
	int i;
	for(i=0,A=0;s[i]!='\0'&&(s[i]>47&&s[i]<58);i++)
		(A*=10)+=s[i]-48;
	return s[i]=='\0';
}

int main()
{	printf("RED-BLACK TREE\n");
	printf("print 'i' to switch into insert mode\n");
	printf("print 'd' to switch into delete mode\n");
	printf("print 'r' to remove all tree\n");
	printf("print 'e' to exit\n\n");

	RBT *Tree=new RBT;
	int data, mode=INSERT;
	bool stop=false;
	char s[255];
	for(;;)
	{	switch(mode)
		{	case INSERT: printf("insert >> "); break;
			case DELETE: printf("delete >> "); break;
		}

		gets(s);

		switch(s[0])
		{	case 'i': mode=INSERT; break;
			case 'd': mode=DELETE; break;
			case 'r': delete Tree; Tree=new RBT; break;
			case 'e': stop=true; break;
			default:
				if (StrToNum(s,data))
					switch(mode)
					{	case INSERT: Tree->Insert(data); break;
						case DELETE: Tree->Delete(data); break;
					};
		};
		if (stop) break;
	};

	delete Tree;
}

