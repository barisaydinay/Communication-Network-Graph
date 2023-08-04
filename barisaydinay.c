// BARIS AYDINAY 2452977 //

//JUST TO CLARIFY: I named the Sender's as graphHead, and the Receivers are my graphVertex nodes.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct myData
{
    int mailID;
    char sender[50];
    char receipt[50];
    int day;
    char content[200];
    int noOfWords;
};

struct graphHead
{
    int noSent;
    int noReceived;
    int checked;
    char sender[50];
    int nowordsReceived;
    struct graphVertex *firstVertex;
    struct graphHead *nextHead;

};

struct graphVertex
{
    char receipt[50];
    int noWords;
    struct graphVertex *nextVertex;
    struct graphHead *destination;

};


void menu();
struct graphHead* readMail(char *,int,struct graphHead*);
struct graphHead* createEdge(struct graphHead*,char *, int);
struct graphVertex* createVertex(char *,int);
void printGraph(struct graphHead*);
struct graphHead* populateWordsReceived(struct graphHead*);
int isExist(struct graphHead*,char *);
int checkPath(struct graphHead*,char *);
struct graphHead* connectPath(struct graphHead*);


int main()
{
    int number=0,option=-1;
    char filePath[50];
    printf("Enter data path: ");
    scanf("%s",filePath);
    fflush(stdin);
    printf("How many files: ");
    scanf("%d",&number);
    strcat(filePath,"/");


    struct graphHead  *head =  ( struct graphHead  *) malloc(sizeof (struct graphHead));
    strcpy(head->sender,"Initial");
    head->noReceived = 0;
    head->noSent = 0;
    head->checked = 0;
    head->nowordsReceived = 0;
    head->firstVertex = NULL;
    head->nextHead = NULL;


    head = readMail(filePath,number,head); // Reads mails, then creates the related graph.
    head = populateWordsReceived(head); // populated.
    head = connectPath(head); // This function simply connects the path between nodes.



    while(option!=3) {

        menu();
        printf("\n");
        printf("Enter option: ");
        scanf("%d",&option);
        printf("\n");

        if(option == 1)
        {
            printGraph(head);
        }

        else if(option == 2)
        {
            printGraph(head);
            char sender[50];
            char receiver[50];
            printf("\nEnter First Name:\n");
            scanf("%s",sender);
            printf("\nEnter Second Name:\n");
            scanf("%s",receiver);




            struct graphHead *checkReset = head->nextHead;

            while(checkReset != NULL)
            {

                checkReset->checked = 0;
                checkReset = checkReset->nextHead;

            }

             struct graphHead *temp = head->nextHead;


            while(temp != NULL)
            {

                if(strcmp(temp->sender,sender) == 0) {break;}


                temp = temp->nextHead;
            }




            if(checkPath(temp,receiver)) printf("\nThere is a path between two people!\n");
            else printf("\nThere is NOT a path between two people!\n");


        }

        else printf("\n** GoodBye! **");

    }



}




struct graphHead* connectPath(struct graphHead *head) {

    struct graphHead* temp = head->nextHead;


    while(temp != NULL)
        {
            struct graphVertex* tempVertex = temp->firstVertex;

            while(tempVertex != NULL)
            {

                struct graphHead* temp2 = head->nextHead;

                    while(temp2 != NULL)
                    {

                        if(strcmp(temp2->sender,tempVertex->receipt) == 0) tempVertex->destination = temp2;
                        temp2 = temp2->nextHead;
                    }
                    tempVertex = tempVertex->nextVertex;

            }


        temp= temp->nextHead;



        }

    return head;


};





void menu()
{

    printf("\nPlease choose one of the following options:\n");
    printf("(1) Print Graph\n");
    printf("(2) Check Path\n");
    printf("(3) Exit\n");

}



struct graphHead* readMail(char filePath[50],int number,struct graphHead *head)
{

    FILE *inFile1;
    char fileName[50]="";
    char fileNumber[3] = "";
    int i;
    int validity=0;


    int j=1;
    int count=0;


    for(i=0; i < number; i++)
    {
        struct myData dummy;



        char str[200] = "";
        strcpy(fileName,filePath);

        itoa(i+1, fileNumber, 10);


        strcat(fileName,fileNumber);
        strcat(fileName,".txt");
        inFile1 = fopen(fileName,"r");

        if(inFile1 != NULL)
        {
            validity = 1;
        }

        if(inFile1 == NULL)
        {
            if(validity == 1)
            {
                printf("\n*** You have entered excess number of files, so entire folder have been read ! ***\n");
                i = number-1;
                continue;
            }
            else
            {
                printf("Directory that contains the mails can not be found !");
                exit(0);
            }
        }


        fseek(inFile1, 0, SEEK_SET);

        while(fgets(str,200,inFile1))
        {


            if(j==1)
            {
                int id = atoi(str);
                dummy.mailID = id;
            }

            else if(j==2)
            {
                if(str[0] == ' ') {
                    int subsize = strlen(str) -1;
                    char sub[subsize];
                    strncpy(sub,&str[1],subsize-1);
                    sub[subsize-1] = '\0';
                    strcpy(dummy.sender,sub);
                }
                else {
                        int subsize = strlen(str);
                        char sub[subsize];
                        strncpy(sub,&str[0],subsize-1);
                        sub[subsize-1] = '\0';
                        strcpy(dummy.sender,sub);
                }



            }
            else if(j==3)
            {

                if(str[0] == ' ') {
                    int subsize = strlen(str) -1;
                    char sub[subsize];
                    strncpy(sub,&str[1],subsize-1);
                    sub[subsize-1] = '\0';
                    strcpy(dummy.receipt,sub);
                }
                else {
                        int subsize = strlen(str);
                        char sub[subsize];
                        strncpy(sub,&str[0],subsize-1);
                        sub[subsize-1] = '\0';
                        strcpy(dummy.receipt,sub);
                }

            }

            else if(j==4)
            {
                int dayNo = atoi(str);
                dummy.day = dayNo;
            }
            else if(j==5)
            {
                strcpy(dummy.content,str);
                int k,words=0;

                for(k=0; k<strlen(str); k++)
                {
                    if(str[k] == ' ') words++;
                }
                dummy.noOfWords = words+1;

            }


            j++;
            if(j==4) fseek(inFile1, 6, SEEK_CUR);
            if(j==2) fseek(inFile1, 6,SEEK_CUR);
            if(j==3) fseek(inFile1,4,SEEK_CUR);
            count++;

        }




        int nullflag = 1;
        struct graphHead *dummyHead = head->nextHead;

        if(dummyHead == NULL) {
            struct graphHead  *myHeads =  ( struct graphHead  *) malloc(sizeof (struct graphHead));
            strcpy(myHeads->sender,dummy.sender);
            myHeads->noSent = 0;
            myHeads->noReceived = 0;
            myHeads->nowordsReceived = 0;
            myHeads->nextHead = NULL;
            myHeads->firstVertex = createVertex(dummy.receipt,dummy.noOfWords);
            myHeads->noSent++;
            head->nextHead = myHeads;


            struct graphHead  *myHeads2 =  ( struct graphHead  *) malloc(sizeof (struct graphHead));
            strcpy(myHeads2->sender,dummy.receipt);
            myHeads2->noSent = 0;
            myHeads2->noReceived = 0;
            myHeads2->nowordsReceived = 0;
            myHeads2->nextHead = NULL;
            myHeads2->firstVertex = NULL;
            myHeads->nextHead = myHeads2;

        }

        else {

                if(isExist(head,dummy.receipt) == 0) {
                        struct graphHead *h = head->nextHead;
                        while(h->nextHead != NULL) h = h->nextHead;
                        struct graphHead  *myHeads3 =  ( struct graphHead  *) malloc(sizeof (struct graphHead));
                        strcpy(myHeads3->sender,dummy.receipt);
                        myHeads3->noSent = 0;
                        myHeads3->noReceived = 0;
                        myHeads3->nowordsReceived = 0;
                        myHeads3->nextHead = NULL;
                        myHeads3->firstVertex = NULL;
                        h->nextHead = myHeads3;
                }

        while(dummyHead != NULL) {

            if(strcmp(dummyHead->sender,dummy.sender) == 0)
            {
                dummyHead = createEdge(dummyHead,dummy.receipt,dummy.noOfWords);
                dummyHead->noSent++;
                nullflag = 0;

            }

            if(dummyHead->nextHead == NULL) break;
            else dummyHead = dummyHead->nextHead;

        }

        if(nullflag == 1)
        {
            struct graphHead  *myHeads =  ( struct graphHead  *) malloc(sizeof (struct graphHead));
            strcpy(myHeads->sender,dummy.sender);
            //myHeads->checked = 0;
            myHeads->noSent = 0;
            myHeads->noReceived = 0;
            myHeads->nowordsReceived = 0;
            myHeads->nextHead = NULL;
            myHeads->firstVertex = createVertex(dummy.receipt,dummy.noOfWords);
            myHeads->noSent++;
            dummyHead->nextHead = myHeads;
        }



        }


        j=1;
        strcpy(fileName,"");
        fclose(inFile1);
    }


    return head;


}



int checkPath(struct graphHead *head,char B[50]) {


   struct graphVertex *tempVertex = head->firstVertex;
    head->checked = 1;

   while(tempVertex != NULL) {

    if(strcmp(tempVertex->receipt,B) == 0) {return 1;}

    if(tempVertex->destination->checked == 0) {if(checkPath(tempVertex->destination,B) == 1) return 1; else checkPath(tempVertex->destination,B);}

    tempVertex = tempVertex->nextVertex;

   }

   return 0;


}






int isExist(struct graphHead* head,char name[50]) {

    struct graphHead *temp = head->nextHead;

    while(temp != NULL) {
    if(strcmp(temp->sender,name) == 0) return 1;
    temp = temp->nextHead;
    }

    return 0;

}



struct graphHead* populateWordsReceived(struct graphHead* head) {

    struct graphHead *temp = head->nextHead;
    struct graphHead *temp2 = head->nextHead;

    while(temp != NULL) {

        while(temp2 != NULL) {

            struct graphVertex *v = temp2->firstVertex;
            while(v != NULL) {
                if(strcmp(v->receipt,temp->sender) == 0) temp->nowordsReceived = temp->nowordsReceived + v->noWords;
                v = v->nextVertex;
            }
            temp2 = temp2 ->nextHead;


        }
        temp2 = head->nextHead;
        temp = temp->nextHead;

    }


    return head;
};





struct graphVertex* createVertex(char receipt[50],int noOfWords) {

    struct graphVertex *vertex = (struct graphVertex *)malloc(sizeof(struct graphVertex));
    vertex->nextVertex = NULL;
    vertex->destination = NULL;
    vertex->noWords = noOfWords;
    strcpy(vertex->receipt,receipt);

    return vertex;

};


struct graphHead* createEdge(struct graphHead* head,char receipt[50], int noOfWords) {

    int flag = 0;

    struct graphVertex *dummyVertex = head->firstVertex;
    while(dummyVertex != NULL) {
        if(strcmp(dummyVertex->receipt,receipt) == 0) {
            dummyVertex->noWords = dummyVertex->noWords + noOfWords;
            flag = 1;
        }
        dummyVertex = dummyVertex->nextVertex;
    }



    if(flag==0)
    {
    struct graphVertex *vertex = (struct graphVertex *)malloc(sizeof(struct graphVertex));
    strcpy(vertex->receipt,receipt);
    vertex->noWords = noOfWords;
    vertex->nextVertex = NULL;
    vertex->nextVertex = head->firstVertex;
    head->firstVertex = vertex;
    }

    return head;

};





void printGraph(struct graphHead* head) {

    printf("\nThe resulting graph adjacency list:\n");
    struct graphHead *temp = head->nextHead;
    struct graphVertex *tempVertex = temp->firstVertex;

    while(temp != NULL) {
            printf("\n%s -> ",temp->sender);

            while(tempVertex != NULL) {

                if(tempVertex->nextVertex != NULL) {
               printf("%s | %d -> ",tempVertex->receipt,tempVertex->noWords);
               tempVertex = tempVertex->nextVertex;
                }
                else {
                printf("%s | %d ",tempVertex->receipt,tempVertex->noWords);
                tempVertex = tempVertex->nextVertex;
                }

            }
    temp = temp->nextHead;
    if(temp!=NULL) tempVertex = temp->firstVertex;
    printf("\n");
    }



    struct graphHead *temp2 = head->nextHead;

    int max=0;
    int maxWords = 0;
    char name[50];
    char maxWordsName[50];
    while(temp2 != NULL) {
        if(temp2->noSent > max) {
            max = temp2->noSent;
            strcpy(name,temp2->sender);
        }
        if(temp2->nowordsReceived > maxWords) {
            maxWords = temp2->nowordsReceived;
            strcpy(maxWordsName,temp2->sender);
        }
        temp2 = temp2->nextHead;


    }

    printf("\nPeople with the maximum number of emails sent: \n%s sent %d emails\n\n",name,max);
    printf("\nPeople with the maximum number of words received: \n%s received %d words\n\n",maxWordsName,maxWords);


}

