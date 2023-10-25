#include<stdio.h>
#include<stdlib.h>
typedef struct process *nextp;
struct process{
	int pnum;
	int priority;
	int burst;
	nextp next;
};
int num=0;

void rr(nextp rrf, nextp rrl, nextp sjfl){
	nextp curr, tail, temp;
	curr=rrf->next;
	tail=rrf;
	while(curr){
		temp=curr;
		tail->next=curr->next;
		curr=curr->next;
		if(temp->burst<=10){
			printf("%d complete\n",temp->pnum);
			free(temp);
		}
		else{
			sjfl->next=temp;
			temp->burst-=10;
			temp->next=NULL;
			sjfl=sjfl->next;
		}
	}
}

void sjf(nextp sjff, nextp sjfl){
	int pn;
	int pr; 
	int bt;
	nextp curr, tail,temp;
	curr=sjff->next;
	while(curr){
		tail=curr->next;
		while(tail){
			if(tail->burst<curr->burst){
				pn=curr->pnum;
				pr=curr->priority;
				bt=curr->burst;
				curr->pnum=tail->pnum;
				curr->priority=tail->priority;
				curr->burst=tail->burst;
				tail->pnum=pn;
				tail->priority=pr;
				tail->burst=bt;
			}
			tail=tail->next;
		}
		curr=curr->next;
	}
	curr=sjff->next;
	while(curr){
		curr=curr->next;
	}
	printf("\n\n");
	curr=sjff->next;
	tail=sjff;
	while(curr){
		temp=curr;
		printf("%d is complete\n",curr->pnum);
		tail->next=curr->next;
		curr=curr->next;
		free(temp);
	}
}

void fcfs(nextp fcfsf, nextp fcfsl){
	nextp curr, tail, temp;
	curr=fcfsf->next;
	tail=fcfsf;
	while(curr){
		temp=curr;
		printf("%d is complete\n",curr->pnum);
		tail->next=curr->next;
		curr=curr->next;
		free(temp);
	}
}

int main(){
	nextp rrf=(nextp)malloc(sizeof(struct process));
	nextp rrl=rrf;
	rrl->next=NULL;
	nextp sjff=(nextp)malloc(sizeof(struct process));
	nextp sjfl=sjff;
	sjfl->next=NULL;
	nextp fcfsf=(nextp)malloc(sizeof(struct process));
	nextp fcfsl=fcfsf;
	fcfsl->next=NULL;
	int x=1;
	int pr, bt;
	printf("Enter 1 to create a new process or 0 to exit: \n");
	scanf("%d",&x);
	while(x){
		printf("Enter priority and burst time: ");
		scanf("%d %d", &pr, &bt);
		if(pr==1){
			rrl->next=(nextp)malloc(sizeof(struct process));
			rrl->next->pnum=num;
			num++;
			rrl->next->priority=pr;
			rrl->next->burst=bt;
			rrl->next->next=NULL;
			rrl=rrl->next;
		}
		else if(pr==2){
			sjfl->next=(nextp)malloc(sizeof(struct process));
			sjfl->next->pnum=num;
			num++;
			sjfl->next->priority=pr;
			sjfl->next->burst=bt;
			sjfl->next->next=NULL;
			sjfl=sjfl->next;
		}
		else if(pr==3){
			fcfsl->next=(nextp)malloc(sizeof(struct process));
			fcfsl->next->pnum=num;
			num++;
			fcfsl->next->priority=pr;
			fcfsl->next->burst=bt;
			fcfsl->next->next=NULL;
			fcfsl=fcfsl->next;
		}
		printf("Enter 1 to create a new process or 0 to exit: \n");
		scanf("%d",&x);
	}
	rr(rrf,rrl,sjfl);
	sjf(sjff, sjfl);
	fcfs(fcfsf,fcfsl);
}