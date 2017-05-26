//BTREE ASSIGNMNT//delete//update facility
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define MAX 4

typedef struct database
	{
		int lib_num;
		char book[100];
		char author[100];
		int ISBN;
		char pub[100];
		int price;
	}data;

typedef struct B_tree_type
	{
		data key[MAX];
		struct B_tree_type* branches[MAX];
		struct B_tree_type* parent;
		int count;
		int leaf;
		
	}B_node;
	
//DISPLAY FUNCTION
void display(B_node *ptr, int blanks)
{
	if (ptr)
	{
		int i;
		for(i=1;i<=blanks;i++)
			printf(" ");
		for (i=0; i < ptr->count; i++)
		{
			if(i<ptr->count)
			{
				printf("\n");
				printf("----------------------------------------------------");
				printf("\nAuthor:%s",ptr->key[i].author);
				printf("\nBook:%s",ptr->key[i].book);
				printf("\nISBN:%d",ptr->key[i].ISBN);
				printf("\nLib Num:%d",ptr->key[i].lib_num);
				printf("\nBook price%d",ptr->key[i].price);
				printf("\nPublication:%s",ptr->key[i].pub);	
				printf("\n");
			//	printf("----------------------------------------------------");
			}
			
		}
		printf("\n");
		for (i=0; i <= ptr->count; i++)
			display(ptr->branches[i], blanks+10);
	}
}//End of display()
	
//SPLIT FUNCTION OF B_TREE NODE
data split(B_node* sptr, data k, B_node* nn2)
{
	int i=0, p, j;
	data temp[MAX], t;
	for(i=0;i<sptr->count;i++)
	{
		temp[i]=sptr->key[i];
	}//end of for loop
	temp[sptr->count]=k;
	for(i=sptr->count;i>0;i--)
	{
		if(temp[i].lib_num<temp[i-1].lib_num)
		{
			t=temp[i];
			temp[i]=temp[i-1];
			temp[i-1]=t;
		}
		
	}//end of for loop
	p=2;
		//index to be promoted
	for(i=0;i<p;i++)
	{
		sptr->key[i]=temp[i];
	}
	for(i=p+1, j=0;i<=sptr->count;i++, j++)
	{
		nn2->key[j]=temp[i];
	}
	
	nn2->leaf=sptr->leaf;
	nn2->count=1;
	sptr->count=2;
//	for(i=0;i<4;i++)
//	{
//		printf("\ntemp:%d",temp[i]);
//	}
//	printf("\nsptr keys:%d,%d\n",sptr->key[0],sptr->key[1]);
	return temp[2];
}//end of split()

	
//INSERTION FUNCTION
B_node* Insertion(data k, B_node* root)
{
	int done=0, visit=0, found_place=0, f=0, i, j;
	B_node *ptr, *nn1, *nn2, *nn3,  *temp2[MAX] ;
	data temp1;
	
	
	if(root==NULL)
	{
		nn1=(B_node*)malloc(sizeof(B_node));
		nn1->key[0]=k;
		nn1->count=1;
		nn1->leaf=1;
		root=nn1;
		nn1->parent=NULL;		
	}
	else  //root!=null
	{
		ptr=root;
		int duplicate=0;
		visit=0;
		if(ptr->leaf!=1)
		{
			
			while(ptr->leaf!=1)
			{	//check for right node to insert element
				duplicate=0;
				for(i=0;i<ptr->count&&duplicate==0;i++)
				{
					if(ptr->key[i].lib_num==k.lib_num)
					{
						duplicate=1;
					}
				}
				if(duplicate==0)
				{
					if(k.lib_num<ptr->key[0].lib_num)
					{
						found_place=1;
						f=0;	
					}
					else if(k.lib_num>ptr->key[ptr->count-1].lib_num)
					{
						found_place=1;
						f=ptr->count;	
					}	
					else
					{
						f=1;
						while((f<ptr->count)&&(found_place=0))
						{
							if((k.lib_num>ptr->key[f-1].lib_num)&&(k.lib_num<ptr->key[f].lib_num))
							{
								found_place=1;
							}						
							else
							{
								f++;
							}
						}
					}
					ptr=ptr->branches[f];
				}//end of if(duplicate==0)
				else	//if(duplicate==1)
				{
					ptr->key[i]=k;
				}
			
				
			}//end of while(leaf!=1)
		}//end of if(leaf!=1)
		while(done==0)
		{	//check for count
		
				if(visit!=0)
				{
					for(i=0,j=0;j<ptr->count+1;j++)
					{
						if(i==f)
						{
							temp2[i]=ptr->branches[j];
							i++;
							temp2[i]=nn2;
							i++;
													
						}
						else
						{
							temp2[i]=ptr->branches[j];
							i++;
						}
					}
					for(i=0;i<ptr->count+2;i++)
					{
						ptr->branches[i]=temp2[i];
					
					}
				
				}
		
			if(ptr->count<MAX-1)
			{
				duplicate=0;
				for(i=0;i<ptr->count&&duplicate==0;i++)
				{
					if(ptr->key[i].lib_num==k.lib_num)
					{
						duplicate=1;
					}
				}
				if(duplicate==0)
				{				
					ptr->key[ptr->count]=k;
					for(i=ptr->count;i>0;i--)
					{
						if(ptr->key[i].lib_num<ptr->key[i-1].lib_num)
						{
									
							temp1=ptr->key[i];
							ptr->key[i]=ptr->key[i-1];
							ptr->key[i-1]=temp1;
						}
					}
					ptr->count=ptr->count+1;
				}
				else	//if duplicate==1
				{
					printf("purana");
					ptr->key[i]=k;
				}
				done=1;
			}	
			
			else 	//if(ptr->count==MAX-1)
			{
				nn2=(B_node*)malloc(sizeof(B_node));
				k=split(ptr, k, nn2);
				//to adjust branches if ptr is not leaf node
				if(ptr->leaf!=1)
				{
					nn2->branches[0]=ptr->branches[ptr->count+1];
					ptr->branches[ptr->count+1]=NULL;	
				}
				//to adjust branches if ptr is not leaf node
				if(ptr->parent!=NULL)
				{
					
					nn2->parent=ptr->parent;
					ptr=ptr->parent;
					visit++;
					
				}
				else 	//ptr->parent==NULL
				{
					nn3=(B_node*)malloc(sizeof(B_node));
					nn3->leaf=0;
					nn3->key[0]=k;
					nn3->key[0]=k;
					nn3->count=1;
					nn3->branches[0]=ptr;
					nn3->branches[1]=nn2;
					nn3->parent=NULL;
					root=nn3;
					ptr->parent=nn3;
					nn2->parent=nn3;
					done=1;
				}
			}
			
		}
		
		
	}

	return root;
}//end of insertion


//SEARCH FUNCTION
B_node* Search(B_node* root, int Lib_access_num)
{
	B_node* ptr;
	int found=0,i, index=0,found_place=0;
	
	ptr=root;
	if(ptr!=NULL)
	{
		while((ptr!=NULL)&&(found==0))
		{
			for(i=0;i<ptr->count&&found==0;i++)
			{
				if(ptr->key[i].lib_num==Lib_access_num)
				{
					found=1;
				}
			}
			if(found==0)
			{
				if(Lib_access_num<ptr->key[0].lib_num)
				{
					index=0;
				}
				else if(Lib_access_num>ptr->key[ptr->count-1].lib_num)
				{
					index=ptr->count;
				}
				else
				{
					index=1;
					while((index<ptr->count)&&(found_place=0))
					{
						if((Lib_access_num>ptr->key[index-1].lib_num)&&(Lib_access_num<ptr->key[index].lib_num))
						{
							found_place=1;
						}
						else
						{
							index++;
						}
					}
				}
				ptr=ptr->branches[index];
			}
				
		}//end of while loop
	}//end of if(ptr!=NULL)
	else	//if(ptr==NULL)i.e. root==NULL
	{
		printf("Database is empty!!!");
	}
	if(found==1)
	{
		i=i-1;
		printf("\nSearched entry:");
		printf("----------------------------------------------------");
		printf("\nAuthor:%s",ptr->key[i].author);
		printf("\nBook:%s",ptr->key[i].book);
		printf("\nISBN:%d",ptr->key[i].ISBN);
		printf("\nLib Num:%d",ptr->key[i].lib_num);
		printf("\nBook price%d",ptr->key[i].price);
		printf("\nPublication:%s",ptr->key[i].pub);	
		printf("\n");
		
	}
	else	//found==0
	{
		printf("The entry not found!!!");
	}
	return ptr;
}//end of search()

static int records=0;
//GET_NUM RECORDS
int get_num(B_node* root)
{
	B_node* ptr;
	ptr=root;
	int i;
	if(ptr!=NULL)
	{
		for(i=0;i<=ptr->count;i++)
		{
			get_num(ptr->branches[i]);
			if(i<ptr->count)
			{
				records++;
			}
		}
	}
	return records;
}//end get_num records

//HEIGHT FUNCTION
int height(B_node* root)
{
	int height=0;
	B_node* ptr;
	ptr=root;
	if(ptr!=NULL)
	{
		while(ptr!=NULL)
		{
			ptr=ptr->branches[0];
			height++;	
		}	
	}	
	return height;
}//end of height function

//RANGE FUNCTION
void range(B_node* pos1,B_node* pos2, B_node* root)
{
	B_node* ptr=NULL;
	int i=0;
		ptr=pos1;
		if(ptr!=pos2)
		{
			for(i=0;i<=ptr->count;i++)
			{
				pos1=ptr;
				range(ptr->branches[i], pos1, pos2);
				if(i<ptr->count)
				{
					printf("\n");
					printf("----------------------------------------------------");
					printf("\nAuthor:%s",ptr->key[i].author);
					printf("\nBook:%s",ptr->key[i].book);
					printf("\nISBN:%d",ptr->key[i].ISBN);
					printf("\nLib Num:%d",ptr->key[i].lib_num);
					printf("\nBook price%d",ptr->key[i].price);
					printf("\nPublication:%s",ptr->key[i].pub);	
					printf("\n");
				//	printf("----------------------------------------------------");
				}
			}
		}
	
}//end of range


//RANGE SEARCH
void Range_search(B_node *root, int k1, int k2)
{
	int i=0, j=0, found1=0, found2=0;
	B_node *pos1=NULL, *pos2=NULL;
	B_node*ptr;
	ptr=root;
	if(ptr!=NULL)
	{	//for pos1
		while((ptr!=NULL)&&(found1==0))
		{
			while((i<ptr->count)&&(found1==0))
			{
				if(ptr->key[i].lib_num>=k1)
				{
					found1=1;				
				}
				else
				{
					i++;
				}
			}//end of while loop
			if(found1==0)
			{
				if(i==ptr->count)
				{
					ptr=ptr->branches[ptr->count];
				}
			}
			else
			{
				pos1=ptr;
			}
		}//end of while for pos1
		//for pos2
		while((ptr!=NULL)&&(found1==0))
		{
			while((i<ptr->count)&&(found1==0))
			{
				if(ptr->key[i].lib_num>k2)
				{
					found2=1;				
				}
				else
				{
					i++;
				}
			}//end of while loop
			if(found2==0)
			{
				if(i==ptr->count)
				{
					ptr=ptr->branches[ptr->count];
				}
			}
			else
			{
				pos2=ptr;
			}
		}//end of while for pos2
	
	}
	range(pos1,pos2,root);
}//enf of range-search

//BORROW FROM BROTHER
int borrow_from_brother(B_node* root, int k,B_node* ptr)
{
	int flag=0, done=0, deficient_prev=0, deficient_next=0;
	B_node *parent_ptr=NULL, *prev, *next;
	parent_ptr=ptr->parent;
	data t;
	//find the index of the current child
	int i=0;
	while(i<=parent_ptr->count&&flag==0)
	{
		if(parent_ptr->branches[i]==ptr)
		{
			flag=1;
		}
		else
		{
			i++;
		}
	}
	printf("\n---in brrw frm bbro:%d\n", i);
	if(i!=0)
	{
		prev=parent_ptr->branches[i-1];
		if(prev->count<=1)
		{
			deficient_prev=1;
		}
	
	}
	
	if(i!=parent_ptr->count)
	{
		next=parent_ptr->branches[i+1];
		if(next->count<=1)
		{
			deficient_next=1;
		}
	}
	
	if((deficient_prev==0)&&(i!=0))
	{
		//brrow from prev_brother
		t=parent_ptr->key[i-1];
		parent_ptr->key[i-1]=prev->key[prev->count-1];
		ptr->key[0]=t;
		prev->count--;
		done=1;
		
	}
	else if((deficient_next==0)&&(i!=parent_ptr->count))
	{	//borrow from next brother
		t=parent_ptr->key[i];
		parent_ptr->key[i]=next->key[0];
		for(i=1;i<next->count;i++)
		{
			next->key[i-1]=next->key[i];
		}
		next->count--;
		ptr->key[0]=t;
		done=1;
	}
	return done;
}//end of borrow from brother

//BORROW FROM PARENT
B_node* borrow_from_parent(B_node* tree, int k, B_node* ptr, int *q)
{
	int flag=0, done=0, j=0;
	B_node *parent_ptr=NULL, *prev, *next;
	parent_ptr=ptr->parent;
	data t;
	//find the index of ptr
	int i=0;
	while(i<=parent_ptr->count&&flag==0)
	{
		if(parent_ptr->branches[i]==ptr)
		{
			flag=1;
		}
		else
		{
			i++;
		}
	}

	//merging with next brother
	if(i!=parent_ptr->count)
	{
		t=parent_ptr->key[i];
		next=parent_ptr->branches[i+1];
		ptr->key[0]=t;
		ptr->key[1]=next->key[0];
		free(next);
	   
	}
	else	//if(i==parent_ptr->count)	//merging with prev brother
	{
		t=parent_ptr->key[i-1];
		prev=parent_ptr->branches[i-1];
		ptr->key[0]=prev->key[0];
		ptr->key[1]=t;
		ptr->count=ptr->count+1;
		free(prev);	
		for(j=i;j<=parent_ptr->count;j++)
		{
			parent_ptr->branches[j-1]=parent_ptr->branches[j];
		}
	
	}
	*q=i;
return parent_ptr;
	
} 

//BORROW FROM LEAF
B_node* borrow_from_leaf(B_node* root, int k, B_node* ptr)
{
	int flag=0, done=0, i;
	B_node *tptr=NULL;
	tptr=ptr;
	//find the index of 'k' in 'ptr'
	i=0;
	while(i<ptr->count&&flag==0)
	{
		if(ptr->key[i].lib_num==k)
		{
			flag=1;
		}
		else
		{
			i++;
		}
	}
	//to find data in the leaf to replace with
	while(tptr->leaf!=1)
	{
		tptr=tptr->branches[i];
		i=tptr->count;
	}
	ptr->key[i]=tptr->key[tptr->count-1];
	return tptr;
	
}//end of borrow from leaf

//DELETE FUNCTION
void Delete(B_node* root, int k)
{
	int flag=0, done=0, i=0, j=0;
	B_node* ptr;
	ptr=root;
	ptr=Search(root, k);
	if(ptr==NULL)
	{
		printf("Entry not found!!");
	}
	else	//if entry is found
	{
		while(done==0)
		{
			if(ptr->leaf==1)	//if ptr is leaf node
			{
				while(done==0)
				{	
					if(ptr->count>1)		//check deficiency
					{
						i=0;
						while(i<ptr->count&&flag==0)
						{
							if(ptr->key[i].lib_num==k)
							{
								flag=1;
								//deleted
							}
							else
							{
								i++;
							}
						}
						if(flag==1)
						{
							for(j=i+1;j<ptr->count;j++)
							{
								ptr->key[j-1]=ptr->key[j];
							}
						}
						ptr->count=ptr->count-1;
						done=1;
					}
					else 	//if leaf is deficient
					{
						int q=0;
						done=borrow_from_brother(root, k, ptr);
						if(done==0)
						{
							if(ptr->parent!=NULL)
							{
								ptr=borrow_from_parent(root,k,ptr,&q);
								k=ptr->key[q].lib_num;
							}
							else	//if ptr has no parent
							{
								root=ptr->branches[0];
								done=1;
								
							}
						}
					}//leaf deficiency case handeled
				}//while(done==0)
			}//end if
			else		//if ptr is internal node
			{
				i=0;
				while(i<ptr->count&&flag==0)	//find index of the key in ptr
				{
					if(ptr->key[i].lib_num==k)
					{
						flag=1;
					}
					else
					{
						i++;
					}
				}
				ptr=borrow_from_leaf(root, k, ptr);
				k=ptr->key[ptr->count-1].lib_num;
			
			}
		}//end of while
	}
}//end of delete
//try

//READFILE FUNCTION
B_node* ReadFile(B_node* tree)
{
	FILE *fp;
	data k;
	int Lib_Access_Num,ISBN_Number,book_price;
	char book_name[100],author_name[100],publisher[100]; 
	fp=fopen("input.txt","r");
		if(fp==NULL)
		{
			printf("\n File is empty");	
		}
						
		while(fscanf(fp, "%d", &Lib_Access_Num)!=EOF)
		{
			//fscanf(fp, "%d", &Library_Access_Num);
			fscanf(fp, "%s",book_name);
			fscanf(fp, "%s",author_name);
			fscanf(fp, "%d",&ISBN_Number);
			fscanf(fp, "%s",publisher);
			fscanf(fp, "%d",&book_price);
			
			k.lib_num=Lib_Access_Num;
			strcpy(k.author,author_name);
			strcpy(k.book,book_name);
			k.ISBN=ISBN_Number;
			strcpy(k.pub, publisher);
			k.price=book_price;
			tree=Insertion(k, tree);
			
		}
return tree;
}

//MAIN FUNCTION
main()
{
	B_node *tree, *ptr=NULL;
	tree=NULL;
	int i=0, n, num, k1=0,k2=0, choice;
	data k;
	FILE *fp;

	printf("LIBRARY DATABASE!!!");
    printf("Enter the operation to be executed\n");
    printf("Please select one from the options given below:\n");
	printf("1  - Insert a entry into the record.\n");
	printf("2  - Delete a entry from the record.\n");
	printf("3  - To get the number of active record.\n");
	printf("4  - To check the height of tree\n");
	printf("5  - To Search a record.\n");
	printf("6  - To do range search\n");
	printf("7  - To read from input file\n");
	printf("8  - To Print database \n");
	printf("100 -To exit the program.\n");
    scanf("%d", &choice);
    while(choice!=100)
	{
		switch(choice)
		{
			case 1:	//insert function
			{
				printf("Enter no. of entries:");
				scanf("%d", &n);
				for(i=0;i<n;i++)
				{
					printf("\nEntry num:%d\n",i+1);
					printf("enter the author:");
					getchar();
					gets(k.author);
					printf("enter the book:");
					gets(k.book);
					printf("enter the ISBN:");
					scanf("%d", &k.ISBN);
					printf("enter the Lib Num:");
					scanf("%d", &k.lib_num);
					printf("enter the Pub:");
					getchar();
					gets(k.pub);
					printf("enter the book price:");
					scanf("%d", &k.price);
					tree=Insertion(k, tree);
	
				}

			break;	
			}
			
			case2:	//delete function
			{
				printf("Enter the lib access num of the record to be deleted:");
				scanf("%d",&num);
				Delete(tree, num);
				break;
			}
			
			case 3:	//get num records
			{
				num=get_num(tree);
				printf("The active records:%d", num);
				break;
			}
			
			case 4:	//height of the tree
			{
				num=height(tree);
				printf("Height of the tree:%d", num);
				break;
			}
			
			case 5:	//search function
			{
				printf("Enter the lib access num of the record to be searched:");
				scanf("%d",&num);
				ptr=Search(tree, num);
				break;
			}
			
			case 6:	//range search
			{
				printf("Enter two keys:");
				scanf("%d %d", k1, k2);
				Range_search(tree, k1, k2);
				break;
				
			}
			
			case 7:
				{
					tree=ReadFile(tree);
					break;
				}
			
			case8:	//print database
			{
				display(tree,0);
				break;
				
			}
		}
	}
}
	
				


