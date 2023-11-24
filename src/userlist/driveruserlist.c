#include "userlist.h"
#include <stdio.h>

    Friendship FShip;
    UserList UList;
    User ActiveUser;

    
int peekData(){
    int x;
    printf("\n SELECT DATA: \n");
    printf("1. Active friendship matrix\n");
    printf("2. User List\n");
    printf("3. Cancel\n");
    scanf("%d",&x);
    switch(x){
        case(1):{
            printf("Matrix:\n");
            displayMatrix(FShip.friends);
            printf("\n");
            break;
        }
        case(2):{
            printf("\n Active user list:\n");
            printListUser(UList);
            break;
        }
        default:{

        }
    }
    printf("\n");
}

int main(){
    int x;
   
    CreateUserList(&UList);
    boolean loggedIn = false;


    createEmptyFriendship(&FShip);
    
    User dummy1;
    User dummy2;

    Word tempWord;
    tempWord.Length = 0;
    dummy1.username = insertStrToWord(tempWord,"dummy1",6,0);
    dummy1.password = insertStrToWord(tempWord,"dummy1",6,0);
    dummy1.privacy = false;
    dummy2.username = insertStrToWord(tempWord,"dummy2",6,0);
    dummy2.password = insertStrToWord(tempWord,"dummy2",6,0);
    dummy2.privacy = false;

    createMatrix(10, 10, &FShip.friends);
    FriendshipStatus(FShip, 0, 1) = 0;
    FriendshipStatus(FShip, 1, 0) = 0;
    FriendshipStatus(FShip, 1, 1) = 1;
    FriendshipStatus(FShip, 0, 0) = 1;

    MakeEmptyPrioQueue(&dummy1.friendRequest,10);
    MakeEmptyPrioQueue(&dummy2.friendRequest,10);


    

    insertLastUser(&UList,dummy1);
    insertLastUser(&UList,dummy2);
    do{
        if(loggedIn){
            printf("Logged in as : %s\n",wordToStr(ActiveUser.username));
        }
        else{
            printf("Not logged in...\n");
        }
        printf("\n");
        printf("Silahkan pilih fungsi yang ingin di tes:\n");
        printf("1. DAFTAR\n");
        printf("2. MASUK\n");
        printf("3. TAMBAH TEMAN\n");
        printf("4. SETUJUI PERMINTAAN PERTEMANAN\n");
        printf("5. LOG OUT\n");
        printf("6. quick switch user (to dummy1)\n");
        printf("7. quick switch user (to dummy2)\n");
        printf("8. Peek data\n");
        printf("9. QUIT\n");
        scanf("%d",&x);
        switch (x){
            case(1):{
                DAFTAR(&UList,&FShip);
                //TEMPORARY PRIOQUEUE FIX
                MakeEmptyPrioQueue(&UList.TabUser[UList.Neff-1].friendRequest,10);
                break;
            }
            case(2):{
                MASUK(UList, &ActiveUser, &loggedIn);
                break;
            }
            case(3):{
                tambahteman(ActiveUser, &UList, FShip);
                break;
            }
            case(4):{
                setujuipermintaanteman(&ActiveUser, &UList, &FShip);
                break;
            }
            case(5):{
                KELUAR(&loggedIn);
                printf("\n");
                break;
            }
            case(6):{
                ActiveUser = Pengguna(UList, 0);
                loggedIn = true;
                break;
            }
            case(7):{
                ActiveUser = Pengguna(UList, 1);
                loggedIn = true;
                break;
            }
            case(8):{
                peekData();
            }
            default:{

            }
        }
    } while (x != 9);
    return 0;
}
