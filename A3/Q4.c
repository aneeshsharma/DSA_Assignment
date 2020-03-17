#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    int key;
    int degree;
    struct Node* sibling;
    struct Node* lmchild;
    struct Node* parent;
} Node;

Node* createnewnode(int data)
{
    Node* b;
    b = (Node*) malloc(1*sizeof(Node));
    b->key=data;
    b->degree=0;
    b->sibling=NULL;
    b->lmchild=NULL;
    b->parent=NULL;

    return b;
}

typedef struct Heap{
    Node* root;
} Heap;

Node* Merge(Node* p,Node* q)
{
    if(p == NULL)
        return q;
    else if(q == NULL)
        return p;
    else if(p->degree <= q->degree) {
        p->sibling = Merge(p->sibling, q);
        return p;
    }
    else {
        q->sibling = Merge(q->sibling, p);
        return q;
    }
     
}

Heap* createNewHeap()
{
    Heap* h;
    h = (Heap*) malloc(1*sizeof(Heap));
    h->root = NULL;
}

Node* binomialLink(Node* x, Node* y)
{
    x->sibling=y->lmchild;
    y->lmchild=x;
    x->parent=y;
    (y->degree)++;
    return y;
}

Node* consolidate(Node* p)
{
    if(p==NULL)
        return p;
    else if(p->sibling==NULL)
        return p;
    else
    {
        if(p->sibling->degree>p->degree)
        {
            p->sibling=consolidate(p->sibling);
            return p;
        }
        else
        {
            if(p->sibling->sibling!=NULL && p->sibling->sibling->degree==p->degree)
            {
                p->sibling=consolidate(p->sibling);
                return p;
            }
            else
            {
                Node* z;
                z=p->sibling->sibling;

                if(p->key>p->sibling->key)
                    p=binomialLink(p,p->sibling);
                else
                    p=binomialLink(p->sibling,p);
                
                p->sibling=z;
                p=consolidate(p);
                return p;
                
            }
            
        }
        
    }
    
}

Node* setMin(Heap* h,Node* min)
{
    Node* y;
    y=h->root;

    while(y!=NULL)
    {
        if(min==NULL)
             min=y;

        if(min->key>y->key)
            min=y;
        y=y->sibling;
    }

    return min;
}

Heap* Union(Heap* h1, Heap* h2)
{
    if(h1->root==NULL)
        return h2;
    else if(h2->root==NULL)
        return h1;
    else
    {
        Heap* h;
        h=createNewHeap();
        Node *p, *q;
        p=h1->root;
        q=h2->root;
        free(h1);
        free(h2);
        h->root=Merge(p,q);
        h->root=consolidate(h->root);
        return h;
    }
    
}

Heap* insert(Heap* h1,Node* x)
{
    Heap *h2, *h;
    h2 = createNewHeap();
    h2->root = x;
    h = Union(h1, h2);
    return h;
}

Node* reverse(Node* head) 
{ 
    
    Node* current = head; 
    Node *prev = NULL, *next = NULL; 

    while (current != NULL) { 

        next = current->sibling;
        current->sibling = prev; 
        prev = current; 
        current = next; 
    } 
    head = prev; 

    return head;

}

Heap* extractMin(Heap* h,Node* min)
{
    if(h->root==min)
        h->root=NULL;
    else
    {
        while(h->root->sibling!=min)
        {
             h->root=h->root->sibling;
        }

        h->root->sibling=h->root->sibling->sibling;
    }

    Node *x, *temp;
    x=min->lmchild;
    temp=x;
    while(temp!=NULL)
    {
        temp->parent=NULL;
        temp=temp->sibling;
    }
    Heap *h2, *hr;
    h2=createNewHeap();
    h2->root=reverse(x);
    hr=Union(h,h2);

    return hr;

}

Heap* decreaseKey(Heap* h,Node* x,int k)
{
    if(k > x->key) {   
        printf("-1 \n");
        return h;
    }
    else {
        x->key=x->key-k;

        Node *y, *z;
        y=x;
        z=x->parent;

        while(z!=NULL && z->key>y->key)
        {
           int temp;
           temp=y->key;
           y->key=z->key;
           z->key=temp;

           y=z;
           z=z->parent;


        }
        return h;
    }

}

Heap* delete(Heap* h,Node* x,Node* min )
{
    h = decreaseKey(h, x, x->key);
    min = NULL;
    min = setMin(h, min);
    h=extractMin(h, min);
    return h;
}

int main()
{
    int n;
    scanf("%d", &n);

    Node** arr;
    arr = (Node**) malloc(n*sizeof(Node*));

    for(int i = 0; i<n; i++)
        arr[i] = NULL;

    Heap* h;
    h = (Heap*) malloc(sizeof(Heap));
    h->root = NULL;

    Node* min = NULL;
    
    while (1) {
        char ch[100];
        int j, k;
        scanf("%s", ch);

        if(strcmp(ch, "insr") == 0)
        {
            scanf("%d %d", &j, &k);
            
            if(arr[j] == NULL) {
                Node* x;
                x = createnewnode(k);
                arr[j] = x;
                h = insert(h,x);
                min = setMin(h,min);
            }
            else {
                printf("-1 \n");
            }
        } else if (strcmp(ch, "min") == 0) {
            if(min != NULL)
                printf("%d \n", min->key);
            else {
                printf("-1 \n");
            }
            
        } else if (strcmp(ch, "extr") == 0) {
            if (min != NULL)
            {
                for (int i = 0; i < n; i++) {
                    if(arr[i] == min)
                    arr[i] = NULL;
                }
            
                printf("%d \n", min->key);
                h = extractMin(h, min);
                min = NULL;
                min = setMin(h, min);
            }
            else {
                printf("-1 \n");
            }
        } else if(strcmp(ch, "decr") == 0) {
            scanf("%d %d", &j, &k);
            int temp;

            temp = arr[j]->key - k;
            h = decreaseKey(h, arr[j], k);
            min = NULL;
            min = setMin(h, min);
        } else if(strcmp(ch, "del") == 0) {
            scanf("%d", &j);
            printf("%d \n", arr[j]->key);
            h = delete(h, arr[j], min);
            min = NULL;
            min = setMin(h, min);
            arr[j] = NULL;
            
        } else if(strcmp(ch, "tc") == 0) {
            int count = 0;
            Node* y;
            y = h->root;
            while (y != NULL) {
                count++;
                y = y->sibling;
            }

            printf("%d \n", count);
        } else if(strcmp(ch, "stop") == 0) {
            return 0;
        } else {
            printf("Error!\n");
        }
    }
    return 0;
}