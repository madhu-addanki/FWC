//Creating a structure Node1
typedef struct Node1
{
	int row,col;
	struct Node1 *right,*down;
	double data;
}Node1;

//Crreating a structure Node
typedef struct Node {
    int value;
    int row;
    int col;
    struct Node* next;
} Node;

Node* createNode(int value, int row, int col); 
double power(double base,int exp);
double knowans(Node1 *newd,int row1,int col1);
double know1(Node1 *newd,int row1,int col1);

//Function to find rank of the maix
int rank(Node1 *mat,int m,int n)
{
	int ra=m,row1,col1,count=0;
	double b,val;
	Node1 *rp,*dp,*newd,*newd1,*rpp,*update=mat;
	rp=mat;
	dp=rp;
	newd=mat;
	newd1=mat;
	col1=rp->col;
	rpp=mat;
	//Loop through each row
	while(dp)
	{
		row1=dp->row;
		val=knowans(newd,row1,row1);
		newd=mat;
		if(val)
		{	
			//Loop through each column
			while(rp)
			{

				col1=rp->col;
				if(col1!=row1)
				{
					double k1;
					k1=know1(newd,row1,col1);
					newd=mat;
					b=k1/val;
					//printf("%f\n",b);
					while(update)
					{
						while(update->row!=col1)
						{
							update=update->down;
						}
						int c=update->col;
						update->data-=b*know1(newd,c,row1);
						if(update->data==0)
						{
							count++;
						}
						update=update->right;
					
				}
					update=mat;
					if(count==2)
					{
						ra-=1;
					}

				}

					rp=rp->right;
			}
			rp=mat;
		}
		
		dp=dp->down;
	}
	return ra;
}

	
double know1(Node1 *newd,int row1,int col1)
{
	double value;
	while(newd->row!=col1)
	{
		newd=newd->down;
	}

	while(newd->col!=row1)
	{
		newd=newd->right;
	}
	value=newd->data;
	return value;
}

double knowans(Node1 *newd,int row1,int col1)
{
	double value;
	while(newd->row!=row1)
	{
		newd=newd->down;
	}

	while(newd->col!=col1)
	{
		newd=newd->right;
	}
	while(newd)
	{
		if(newd->col==newd->row)
		{
			value=newd->data;
			break;
		}
		newd=newd->right;
	}
	return value;
}

//Creating a newnode in doubly linked list
Node1* newNode(double d)
{
	Node1* temp=(Node1*)malloc(sizeof(Node1));
	temp->data=d;
	temp->right=temp->down=NULL;	
	return temp;
}

//Printing a doubly linked list
void print(Node1* head)
{
	Node1 *rp,*dp=head;
	while(dp)
	{
		rp=dp;
		while(rp)
		{
			printf("%f",rp->data);
			rp=rp->right;
		}
		printf("\n");
		dp=dp->down;
	}
}

//Reading values for doubly linked list from .dat files
Node1* constructVec(char *mat,int m,int n)
{
	FILE *fp=fopen(mat,"r");
	Node1* mainhead=NULL;
	Node1* head[m];
	Node1 *righttemp,*newptr;
	for(int i=0;i<m;i++)
	{
		head[i]=NULL;
		for(int j=0;j<n;j++)
		{
			float value;
			fscanf(fp,"%f",&value);
			newptr=newNode(value);
			newptr->row=i;
			newptr->col=j;

			if(!mainhead)
				mainhead=newptr;

			if(!head[i])
				head[i]=newptr;
			else
				righttemp->right=newptr;

			righttemp=newptr;
		}
	}

	for(int i=0;i<m-1;i++)
	{
		Node1 *temp1=head[i],*temp2=head[i+1];
		while(temp1&&temp2)
		{
			temp1->down=temp2;
			temp1=temp1->right;
			temp2=temp2->right;
		}
	}
	return mainhead;

}

//Reading values for single linked list from .dat files
Node* loadtxt(char *str) {
    FILE *fp = fopen(str, "r");
    Node* head = NULL;
    Node* currentRow = NULL;

    int numRows = 3;
    int numCols = 1;

    // Loop through each row
    for (int i = 0; i < numRows; i++) {
        Node* newRow = NULL;
        Node* currentCol = NULL;

        // Loop through each column in the current row
        for (int j = 0; j < numCols; j++) {
            int value;
            fscanf(fp,"%d", &value);

            if (value != 0) {
                Node* newNode = createNode(value, i, j);
                if (newRow == NULL) {
                    newRow = newNode;
                    currentCol = newNode;
                } else {
                    currentCol->next = newNode;
                    currentCol = newNode;
                }
            }
        }

        if (newRow != NULL) {
            if (head == NULL) {
                head = newRow;
                currentRow = newRow;
            } else {
                currentRow->next = newRow;
                currentRow = newRow;
            }
        }
    }

    fclose(fp);
    return head;
}

//Creating newnode for single linked list
Node* createNode(int value, int row, int col) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;
    return newNode;
}


//Printing values of Singe Linked list
void display(Node* head) {

    int numRows = 0, numCols = 0;
    for (Node* curr = head; curr != NULL; curr = curr->next) {
        if (curr->row >= numRows) {
            numRows = curr->row + 1;
        }
        if (curr->col >= numCols) {
            numCols = curr->col + 1;
        }
    }
    if (numCols == 1) {
        numRows = 3;
    }

    // Loop through each row in the matrix
    for (int i = 0; i < numRows; i++) {
        // Loop through each column in the matrix
        for (int j = 0; j < numCols; j++) {

            Node* curr = head;
            while (curr != NULL && (curr->row < i || (curr->row == i && curr->col < j))) {
                curr = curr->next;
            }
            if (curr != NULL && curr->row == i && curr->col == j) {
                printf("%d ", curr->value);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

//Inserting nodes into single linked list
void insert_node(Node **head, int row, int col, int val) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->row = row;
    new_node->col = col;
    new_node->value = val;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
}

//Subtracting 2 matrices
Node *linalg_sub(Node *a, Node *b) {
    Node *result = NULL;

    while (a != NULL && b != NULL) {
        if (a->row < b->row || (a->row == b->row && a->col < b->col)) {
            insert_node(&result, a->row, a->col, a->value);
            a = a->next;
        } else if (a->row == b->row && a->col == b->col) {
            int val = a->value - b->value;
            if (val != 0) {
                insert_node(&result, a->row, a->col, val);
            }
            a = a->next;
            b = b->next;
        } else {
            insert_node(&result, b->row, b->col, -b->value);
            b = b->next;
        }
    }

    while (a != NULL) {
        insert_node(&result, a->row, a->col, a->value);
        a = a->next;
    }

    while (b != NULL) {
        insert_node(&result, b->row, b->col, -b->value);
        b = b->next;
    }

   return result;

}

//Function for transpose of a matrix
Node* transpose(Node* head) {
    Node* transposeHead = NULL;
    
    // Loop through each node in the original linked list
    for (Node* curr = head; curr != NULL; curr = curr->next) {
        // Create a new node with its row and column positions swapped
        Node* newNode = createNode(curr->value, curr->col, curr->row);
        
        if (transposeHead == NULL) {
            transposeHead = newNode;
        } else {
            Node* currTranspose = transposeHead;
            while (currTranspose->next != NULL) {
                currTranspose = currTranspose->next;
            }
            currTranspose->next = newNode;
        }
    }
    
    return transposeHead;
}


//Function for matrix multiplication 
Node* matmul(Node* A, Node* B, int numRowsA, int numColsB) {
    // Create a new empty linked list for the result
    Node* resultHead = NULL;
    
    // Loop through each row in A
    for (int i = 0; i < numRowsA; i++) {
        // Loop through each column in B
        for (int j = 0; j < numColsB; j++) {
            int dotProduct = 0;
        
            for (Node* currA = A; currA != NULL && currA->row == i; currA = currA->next) {
                for (Node* currB = B; currB != NULL && currB->col == j; currB = currB->next) {
                    if (currA->col == currB->row) {
                        dotProduct += currA->value * currB->value;
                    }
                }
            }
            if (dotProduct != 0) {
                Node* newNode = createNode(dotProduct, i, j);
                if (resultHead == NULL) {
                    resultHead = newNode;
                } else {
                    Node* prev = NULL;
                    Node* currR = resultHead;
                    while (currR != NULL && (currR->row < newNode->row || (currR->row == newNode->row && currR->col < newNode->col))) {
                        prev = currR;
                        currR = currR->next;
                    }
                    if (prev == NULL) {
                        resultHead = newNode;
                    } else {
                        prev->next = newNode;
                    }
                    newNode->next = currR;
                }
            }
        }
    }
    
    
    return resultHead;
}

//Function for fnding matrix magnitude
double linalg_norm(Node* head, int numRows, int numCols)
{
    double sumOfSquares = 0;

    // Loop through each columnent in the column
    while(head)
    {
	    sumOfSquares+=pow(head->value,2);
	    head=head->next;
    }
    return sumOfSquares;
}

void save(double a) {
  FILE *fp;
  fp = fopen("result.dat", "w");
  fprintf(fp, "%lf", a);
  fprintf(fp, "\n");
  fclose(fp);
}
