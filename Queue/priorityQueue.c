#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_PATIENTS 100

// <-----Patient structure ----->
typedef struct{
    int id;
    int priority;
    char name[50];
} Patient;

// <-----BST Node structure ----->
typedef struct BSTNode{
    int id;     // patient id
    int handle; //internal array index
    struct BSTNode *left;
    struct BSTNode *right;

} BSTNode;
BSTNode *root = NULL;

// <-----Global variables ----->
Patient *patients[MAX_PATIENTS]; //array of patient (handle->Patient*)
int heap[MAX_PATIENTS + 1 ]; // Max heap: heap[pos] = handle;
int QP[MAX_PATIENTS];  // QP[handle] = position in heap
int heapSize = 0; // current number of patient in heap
int nextHandle = 0; // next handle 


void init(){
    heapSize = 0;
    nextHandle = 0;
    for(int i=0; i< MAX_PATIENTS; i++){
        patients[i] = NULL;
        QP[i] = -1;  // -1 --> Not in heap;
    }
    root = NULL;    // empty BST
}


// <------------------------------------ Binary Tree functions -------------------------------->

BSTNode* createNode(int id, int handle){
    BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
    node->id = id;
    node->handle = handle;
    node->left = NULL;
    node->right = NULL;
    return node;
}
BSTNode* insertBST(BSTNode *node, int id, int handle){
    if(node==NULL){
        return createNode(id, handle);
    }

    if(id < node->id){
        node->left = insertBST(node->left, id, handle);
    }else if(id>node->id){
        node->right = insertBST(node->right, id,handle);
    }else{
        //Node exists...
    }
    return node;
}


// <-----BST Node deletion---->
BSTNode *minValueNode(BSTNode* node){
    while(node->left != NULL){
        node = node->left;
    }
    return node;
}

BSTNode* deleteBST(BSTNode* node, int id){
    if(node == NULL){
        return NULL;
    }

    if(id<node->id){
        node->left = deleteBST(node->left, id);
    }else if(id>node->id){
        node->right = deleteBST(node->right, id);
    }else{  
        //Node found


        //No childred
        if(node->left == NULL && node->right == NULL){
            free(node);
            return NULL;
        }

        //Only one children
        if(node->left == NULL){
            BSTNode *temp = node->right;
            free(node);
            return temp;
        }else if(node->right == NULL){
            BSTNode *temp = node->left;
            free(node);
            return temp;
        }

        
        //two children
        
        //find next successor
        BSTNode *temp = minValueNode(node->right);
        //replace with successor
        node->id = temp->id;
        node->handle = temp->handle;

        //delete the successor
        node->right = deleteBST(node->right, temp->id);

        return node;

    }
}

// <------------------------------------ Heap functions -------------------------------->
void swapHeapPosition(int i, int j){
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;

    //update QP
    QP[heap[i]] = i;
    QP[heap[j]] = j;
}

int higherPriority(int i, int j){
    int handle1 = heap[i];
    int handle2 = heap[j];
    return patients[handle1]->priority > patients[handle2]->priority;
}

void swim(int pos){
    while(pos>1 && higherPriority(pos, pos/2)){
        swapHeapPosition(pos, pos/2);
        pos = pos/2;
    }
}


void sink(int pos){
    while(2*pos <= heapSize){
        int child = 2*pos;

        if(child+1<= heapSize && higherPriority(child+1,child)){
            child = child +1;
        }

        if(higherPriority(pos, child)){
            break;
        }

        swapHeapPosition(pos,child);
        pos = child;
    }
}

int changePriority(int handle, int newPriority){
    if(handle < 0 || handle >= nextHandle || QP[handle] == -1){
        return -1;
    }

    int oldPriority = patients[handle]->priority;
    patients[handle]->priority = newPriority;

    int pos = QP[handle];

    if(newPriority > oldPriority){
        swim(pos);
    }else if( newPriority < oldPriority){
        sink(pos);
    }
    return 0;
}


// <------------------------------------ QP functions -------------------------------->

int getHandleByID(BSTNode *node, int id){
    if(node == NULL){
        return -1;
    }

    if(id == node->id){
        return node->handle;
    } else if(id < node->id){
        return getHandleByID(node->left, id);
    } else {
        return getHandleByID(node->right, id);
    }
}


// <------------------------------------ Patient functions -------------------------------->
int addPatient(int id, char *name, int priority ){
    if(nextHandle >= MAX_PATIENTS) {
        printf("Heap full!\n");
        return -1;
    }
    //creating new patient
    Patient *p = (Patient*) malloc(sizeof(Patient));  
    p->id = id;
    strcpy(p->name, name);
    p->priority = priority;  

    int handle = nextHandle++;
    patients[handle] = p;

    root = insertBST(root,id,handle);

    //Add to heap
    heap[++heapSize] = handle;

    //update QP
    QP[handle] = heapSize;

    swim(heapSize);
    
    return handle;
}

void freePatient(int handle){
    if(handle<0 || handle>=MAX_PATIENTS){
        return;
    }

    if(patients[handle] != NULL){
        free(patients[handle]);
        patients[handle] = NULL;
    }
}

Patient* nextPatient(){
    if(heapSize == 0){
        return NULL;
    }

    int handle = heap[1];
    Patient *p = patients[handle];


    //move last heap to first
    heap[1] = heap[heapSize];
    QP[heap[1]] = 1;
    heapSize--;

    // mark removed
    QP[handle] = -1;

    // fix heap
    sink(1);

    return p;
}

void removeByHandle(int handle){
    int pos = QP[handle];

    if(pos == -1){
        printf("Patient is not in heap");
        return;
    }

    swapHeapPosition(pos, heapSize);

    QP[handle] = -1;

    heapSize--;
    if(pos<=heapSize){
        swim(pos);
        sink(pos);
    }
    
    //Free BST node;
    int id = patients[handle]->id;
    root = deleteBST(root, id);
    
    //Free Patient Memory;
    freePatient(handle);

}

void removeById(int id){
    int handle = getHandleByID(root, id);
    if(handle == -1){
        printf("Invalid ID\n");
        return;
    }

    removeByHandle(handle);
    

}





int main(int argc, char* argv[]){
    init();
    int choice = 0;

    while (choice!=5)
    {

        printf("Welcome to hospital management System\n");
        printf("Enter number to continue..\n");
        printf("1. Add patient\n");
        printf("2. Change Priority\n");
        printf("3. Diplay next patient in line\n");
        printf("4. Remove patient\n");
        printf("5. Exit\n");
        printf(">>> ");
        scanf("%d", &choice);
    
        switch (choice)
        {
            case 1:{
                int id;
                char name[50];
                int priority;

                printf("Enter patient's name\n>>");
                scanf("%s", name);
                printf("Enter patient's id\n>>");
                scanf("%d", id);
                printf("Enter priority 1-10: 10 -> highest\n>>");
                scanf("%d", priority);

                int p1 = addPatient(id, name, priority);
                if(p1 == -1){
                    printf("Error. Maximum number of patients reached.\n");
                }else{
                    printf("Patient added succesfully.");
                }
                break;
            }
              
            case 2:{
                int id, priority;
                printf("Enter patient's id\n>>");
                scanf("%d", &id);
                printf("Enter priority 1-10: 10 -> highest\n>>");
                scanf("%d", &priority);

                int handle = getHandleByID(root, id);
                if(handle == -1){
                    printf("Invalid Id\n");
                    break;
                }
                int success = changePriority(handle, priority);
                if(success == -1){
                    printf("Invalid handle or patient not in heap!\n");
                }else{
                    printf("Priority updated.\n");
                }
                break;
            }

            case 3:{
                Patient *p = nextPatient();
                if(p == NULL){
                    printf("No patient found");
                    break;
                }

                printf("Next Patient id: %d\n", p->id);
                printf("Name: %s\n",p->name);

                int handle = getHandleByID(root, p->id);
                root = deleteBST(root, p->id);             
                freePatient(handle);
                break;
            }

            case 4:{

                int id;
                printf("Enter patient's id\n>>");
                scanf("%d", &id);
                removeById(id);
                break;
            }
            case 5:
                break;
            default:
                printf("Enter valid number (1-5)\n");
                break;
            }
    }

    return 0;
}