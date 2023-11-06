#include "prioqueuechar.h"
#include <stdio.h>
#include <stdlib.h>

boolean IsEmpty_PQueue (PrioQueueChar Q) {
    return(Head_PQueue(Q) == Nil && Tail_PQueue(Q) == Nil); 
}

boolean IsFull_PQueue (PrioQueueChar Q) {
    return NBElmt_PQueue(Q) == MaxEl_PQueue(Q);
}

int NBElmt_PQueue (PrioQueueChar Q) {
    if (IsEmpty_PQueue(Q)) {
        return 0;
    }
    else {
        if (Tail_PQueue(Q) >= Head_PQueue(Q)) {
            return(Tail_PQueue(Q) - Head_PQueue(Q) + 1);
        }
        else {
            int temp = MaxEl_PQueue(Q) + Tail_PQueue(Q);
            return(temp - Head_PQueue(Q) + 1);
        }
    }
}

void MakeEmpty_PQueue (PrioQueueChar * Q, int Max) {
    (*Q).T = (infotype_PQueue *) malloc (Max * sizeof(infotype_PQueue));
	MaxEl_PQueue(*Q) = Max;
	Head_PQueue(*Q) = Nil;
	Tail_PQueue(*Q) = Nil;
}

void DeAlokasi_PQueue (PrioQueueChar * Q) {
    free((*Q).T);
	MaxEl_PQueue(*Q)=0;
}

void Enqueue_PQueue (PrioQueueChar * Q, infotype_PQueue X) {
    if(!IsEmpty_PQueue(*Q)) {
		Tail_PQueue(*Q) = (Tail_PQueue(*Q) + 1) % MaxEl_PQueue(*Q);
		InfoTail_PQueue(*Q) = X;
		int i = (Tail_PQueue(*Q));
		infotype_PQueue temp;

		while (i != Head_PQueue(*Q)) {
			int idxBefore = (i - 1 + MaxEl_PQueue(*Q)) % MaxEl_PQueue(*Q);
			if (Prio_PQueue(Elmt_PQueue(*Q,i)) > Prio_PQueue(Elmt_PQueue(*Q,idxBefore))){
				temp = Elmt_PQueue(*Q, i);
				Elmt_PQueue(*Q, i) = Elmt_PQueue(*Q, idxBefore);
				Elmt_PQueue(*Q, idxBefore) = temp;
			}
			i = idxBefore;
		}
	}
    else {
		Head_PQueue(*Q) =0;
		Tail_PQueue(*Q) = 0;
		InfoTail_PQueue(*Q) = X;
    }
}

void Dequeue_PQueue (PrioQueueChar * Q, infotype_PQueue * X) {
    *X = InfoHead_PQueue(*Q);
	if (NBElmt_PQueue(*Q)==1) {
        Head_PQueue(*Q) = Nil;
        Tail_PQueue(*Q) = Nil;
    } 
    else {
        if (Head_PQueue(*Q) == MaxEl_PQueue(*Q)-1) {
            Head_PQueue(*Q) = 1;
        } 
        else {
            Head_PQueue(*Q)++;
        }
    }
}

void PrintPrioQueueChar_PQueue (PrioQueueChar Q) {
    if (IsEmpty_PQueue(Q)) {
 		printf("#\n");
	} 
    else {
		int i,j;
		if (Tail_PQueue(Q) - Head_PQueue(Q) < 0) {
	            for (i = Head_PQueue(Q); i < MaxEl_PQueue(Q); i++) {
	                printf("%d %c\n", Prio_PQueue(Elmt_PQueue(Q,i)), Info_PQueue(Elmt_PQueue(Q,i)));
	            }
	            for (j = 0; j < Tail_PQueue(Q) + 1; j++) {
	                if (j != Tail_PQueue(Q)) {
	                    printf("%d %c\n", Prio_PQueue(Elmt_PQueue(Q,j)), Info_PQueue(Elmt_PQueue(Q,j)));
	                } else {
	                    printf("%d %c\n", Prio_PQueue(Elmt_PQueue(Q,j)), Info_PQueue(Elmt_PQueue(Q,j)));
	                }
	            }
	            printf("#\n");
        } 
        else {
            for (i = Head_PQueue(Q); i < Tail_PQueue(Q) + 1; i++) {
                if (i!=Tail_PQueue(Q)) {
                    printf("%d %c\n", Prio_PQueue(Elmt_PQueue(Q,i)), Info_PQueue(Elmt_PQueue(Q,i)));
                } 
                else {
                    printf("%d %c\n", Prio_PQueue(Elmt_PQueue(Q,i)), Info_PQueue(Elmt_PQueue(Q,i)));
                }
            }
            printf("#\n");
        }
    }
}