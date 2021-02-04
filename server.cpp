#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <string>
#include <pthread.h>

#define TRUE   1
#define FALSE  0
#define PORT 2000
#define MAX_CLIENTS 30

int cards[57][8] = {
    {1, 8, 15, 16, 17, 18, 19, 20},
    {1, 9, 21, 22, 23, 24, 25, 26},
    {1, 10, 27, 28, 29, 30, 31, 32},
    {1, 11, 33, 34, 35, 36, 37, 38},
    {1, 12, 39, 40, 41, 42, 43, 44},
    {1, 13, 45, 46, 47, 48, 49, 50},
    {1, 14, 51, 52, 53, 54, 55, 56},
    {2, 8, 26, 27, 36, 41, 46, 51},
    {2, 9, 15, 32, 37, 42, 47, 52},
    {2, 10, 16, 21, 38, 43, 48, 53},
    {2, 11, 17, 22, 28, 44, 49, 54},
    {2, 12, 18, 23, 29, 33, 50, 55},
    {2, 13, 19, 24, 30, 34, 39, 56},
    {2, 14, 20, 25, 31, 35, 40, 45},
    {3, 8, 23, 32, 34, 43, 45, 54},
    {3, 9, 18, 30, 38, 40, 49, 51},
    {3, 10, 15, 24, 35, 44, 46, 55},
    {3, 11, 19, 21, 31, 41, 50, 52},
    {3, 12, 16, 25, 28, 36, 47, 56},
    {3, 13, 20, 22, 27, 33, 42, 53},
    {3, 14, 17, 26, 29, 37, 39, 48},
    {4, 8, 22, 31, 38, 39, 47, 55},
    {4, 9, 19, 29, 36, 44, 45, 53},
    {4, 10, 17, 25, 34, 42, 50, 51},
    {4, 11, 15, 23, 27, 40, 48, 56},
    {4, 12, 20, 21, 30, 37, 46, 54},
    {4, 13, 18, 26, 28, 35, 43, 52},
    {4, 14, 16, 24, 32, 33, 41, 49},
    {5, 8, 25, 30, 33, 44, 48, 52},
    {5, 9, 16, 27, 35, 39, 50, 54},
    {5, 10, 18, 22, 37, 41, 45, 56},
    {5, 11, 20, 24, 29, 43, 47, 51},
    {5, 12, 15, 26, 31, 34, 49, 53},
    {5, 13, 17, 21, 32, 36, 40, 55},
    {5, 14, 19, 23, 28, 38, 42, 46},
    {6, 8, 24, 28, 37, 40, 50, 53},
    {6, 9, 17, 31, 33, 43, 46, 56},
    {6, 10, 20, 23, 36, 39, 49, 52},
    {6, 11, 16, 26, 30, 42, 45, 55},
    {6, 12, 19, 22, 32, 35, 48, 51},
    {6, 13, 15, 25, 29, 38, 41, 54},
    {6, 14, 18, 21, 27, 34, 44, 47},
    {7, 8, 21, 29, 35, 42, 49, 56},
    {7, 9, 20, 28, 34, 41, 48, 55},
    {7, 10, 19, 26, 33, 40, 47, 54},
    {7, 11, 18, 25, 32, 39, 46, 53},
    {7, 12, 17, 24, 27, 38, 45, 52},
    {7, 13, 16, 23, 31, 37, 44, 51},
    {7, 14, 15, 22, 30, 36, 43, 50},
    {1, 2, 3, 4, 5, 6, 7, 57},
    {20, 26, 32, 38, 44, 50, 56, 57},
    {8, 9, 10, 11, 12, 13, 14, 57},
    {18, 24, 31, 36, 42, 48, 54, 57},
    {15, 21, 28, 33, 39, 45, 51, 57},
    {17, 23, 30, 35, 41, 47, 53, 57},
    {16, 22, 29, 34, 40, 46, 52, 57},
    {19, 25, 27, 37, 43, 49, 55, 57}
};

struct Player {
   char  username[20];
   int   points;
   int   cardOnHand;
   int   socket;
} players[30];

struct Game {
    int numberOfPlayers;
    int timer;
    bool on;
    int cardOnBoard;
    int cardIterator;
    int stash[57];
} game;

void broadcast(char message[30]) {
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if ( players[i].socket != 0 ) {
            if ( (unsigned)send(players[i].socket, message, strlen(message), 0) != strlen(message) ) {
                perror("send");
            }
        }
    }
}

void sendCard(int i) {
    char countDownFinished[30] = "countDownFinished,1;";
    char b[10];
    sprintf(b, "%d", players[i].cardOnHand);
    strcat(countDownFinished, b);
    strcat(countDownFinished, ";");
    char c[10];
    sprintf(c, "%d", game.cardOnBoard);
    strcat(countDownFinished, c);

    printf("%s\n", countDownFinished);

    if( (unsigned)send(players[i].socket, countDownFinished, strlen(countDownFinished), 0) != strlen(countDownFinished) ) {
        perror("send");
    }
}

void countDownFinished() {
    if (game.numberOfPlayers < 2) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if ( players[i].socket != 0 ) {
                char countDownFinished[30] = "countDownFinished,0;0;0";
                if( (unsigned)send(players[i].socket, countDownFinished, strlen(countDownFinished), 0) != strlen(countDownFinished) ) {
                    perror("send");
                }
            }
        }
        return;
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if ( players[i].socket != 0 ) {
            sendCard(i);
        }
    }
    game.on = TRUE;
}

void playerCount(int numberOfPlayers) {
    char playerCount[300] = "playerCount,";
    char n[10];
    sprintf(n, "%d", numberOfPlayers);
    strcat(playerCount, n);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if ( players[i].socket != 0 ) {
            strcat(playerCount, ";");
            strcat(playerCount, players[i].username);
            strcat(playerCount, ";");
            char c[10];
            sprintf(c, "%d", players[i].points);
            strcat(playerCount, c);
        }
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if ( players[i].socket != 0 ) {
            if( (unsigned)send(players[i].socket, playerCount, strlen(playerCount), 0) != strlen(playerCount) ) {
                perror("send");
            }
        }
    }
}

void* timer(void *vargp) {
    while (1) {
        if (game.numberOfPlayers < 2 || game.on) {
            return NULL;
        }
        else if (game.timer == 0 && game.numberOfPlayers >= 2) {
        printf("%d\n", game.timer);
            countDownFinished();
            return NULL;
        }
        if (--game.timer < 0)
            break;
        char timer[30] = "countDown,";
        char iInStr[10];
        sprintf(iInStr, "%d", game.timer);
        strcat(timer, iInStr);
        broadcast(timer);
        sleep(1);
    };
    return NULL;
}

bool numInCard(int answer) {
    for (int i=0; i<8; i++) {
        if (cards[game.cardOnBoard][i] == answer) {
            return TRUE;
        }
    }
    return FALSE;
}

void check(int i, int max_clients, char *message) {
    if (!numInCard(cards[players[i].cardOnHand][atoi(message)])) {
        return;
    }
    players[i].points--;
    game.cardOnBoard = players[i].cardOnHand;
    players[i].cardOnHand = game.stash[game.cardIterator];
    game.cardIterator++;
    countDownFinished();
    sleep(1);
    if (players[i].points != 0) {
        playerCount(game.numberOfPlayers);
        return;
    }
    printf("%s has won\n", players[i].username);
    char finish[30] = "finish,1;0";
    if ( (unsigned)send( players[i].socket, finish, strlen(finish), 0) != strlen(finish) ) {
        perror("send");
    }
    for (int k = 0; k < max_clients; k++) {
        if ( players[k].socket != 0 && players[i].socket != players[k].socket ) {
            char finish[30] = "finish,0;";
            strcat(finish, players[i].username);
            if ( (unsigned)send( players[k].socket, finish, strlen(finish), 0) != strlen(finish) ) {
                perror("send");
            }
            printf("%s\n", finish);
        }
    }
    game.timer = 10;
    pthread_t tid;
    pthread_create(&tid, NULL, timer, (void *)&tid);
    printf("pthread_create\n");
}

void shuffle(int *array, size_t n) {    
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int usec = tv.tv_usec;
    srand48(usec);


    if (n > 1) {
        size_t i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48()*(i+1));
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int main(int argc , char *argv[])
{
    int opt = TRUE;
    int master_socket , addrlen , new_socket , max_clients = MAX_CLIENTS , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;
    game.on = FALSE;
    game.cardOnBoard = 0;
    game.cardIterator = 1;

    for (int i=0; i<57; i++) {
        game.stash[i] = i;
    }
    shuffle(game.stash, 57);

    char buffer[1025]; //data buffer of 1K

    //set of socket descriptors
    fd_set readfds;

    for (i = 0; i < max_clients; i++)
    {
        players[i].socket = 0;
    }

    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
          sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //bind the socket to localhost port 2000
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while(TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++)
        {
            //socket descriptor
            sd = players[i].socket;

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket, then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            valread = read( new_socket, buffer, 1024);
            if (valread <= 0) {
                printf("User tried to log in with empty username\n");
                continue;
            }
            char *ptr = strtok(buffer, ",");
            ptr = strtok(NULL, ",");
            char *username = ptr;
            if ( game.numberOfPlayers == 7 ) {
                printf("Too many users\n");
                char limit[30] = "limit,";
                if ( (unsigned)send(new_socket, limit, strlen(limit), 0) != strlen(limit) ) {
                    perror("send");
                }
                goto cnt;
            }
            for (i = 0; i < max_clients; i++) {
                if ( players[i].socket != 0 && strcmp(username, players[i].username ) == 0 ) {
                    printf("User tried to log in with duplicate username\n");
                    char duplicate[30] = "duplicate,";
                    if ( (unsigned)send(new_socket, duplicate, strlen(duplicate), 0) != strlen(duplicate) ) {
                        perror("send");
                    }
                    goto cnt;
                }
            }
            
            //TODO: sleeps situation (\0)
            
            char loginSuccess[30] = "loginSuccess";
            //send new connection greeting message
            if( (unsigned)send(new_socket, loginSuccess, strlen(loginSuccess), 0) != strlen(loginSuccess) )
            {
                perror("send");
            }
            
            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++)
            {
                //if position is empty
                if( players[i].socket == 0 )
                {
                    players[i].socket = new_socket;
                    strcpy(players[i].username, username);
                    players[i].cardOnHand = game.stash[game.cardIterator];
                    game.cardIterator++;
                    game.numberOfPlayers++;
                    if (game.on) {
                        int max=0;
                        for (int k = 0; k < max_clients; k++) {
                            if ( players[k].socket != 0 ) {
                                if (players[k].points > max) {
                                    max = players[k].points;
                                }
                            }
                        }
                        players[i].points = max;
                        sleep(1);
                        sendCard(i);
                    } else {
                        players[i].points = 7;
                    }
                    printf("Adding to list of sockets as %d,\n   username: %s\n   points: %d\n   cardOnHand: %d\n   clientNr: %d\n" , i, players[i].username, players[i].points, players[i].cardOnHand, game.numberOfPlayers);
                    sleep(1);
                    playerCount(game.numberOfPlayers);
                    sleep(1);
                    if (game.numberOfPlayers == 2) {
                        game.timer = 10;
                        game.on = FALSE;
                        pthread_t tid;
                        pthread_create(&tid, NULL, timer, (void *)&tid);
                    }
                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = players[i].socket;

            if (FD_ISSET( sd , &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valread = read( sd , buffer, 1024)) <= 0)
                {
                    //Somebody disconnected
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("%s disconnected\n", players[i].username);

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    players[i].socket = 0;
                    game.numberOfPlayers--;
                    if (game.numberOfPlayers == 1){
                        countDownFinished();
                    }
                    if (game.numberOfPlayers == 0) {
                        game.on = FALSE;
                    }
                    playerCount(game.numberOfPlayers);
                } else {
                    //set the string terminating NULL byte on the end of the data read
                    buffer[valread] = '\0';
                    char delim[] = ",";

                    char *ptr = strtok(buffer, delim);

                    // printf("type: %s\n", ptr);
                    char *type = ptr;
                    ptr = strtok(NULL, delim);
                    char *message = ptr;

                    if ( strcmp(type, "startGame") == 0 ) {
                        countDownFinished();
                    } else if ( strcmp(type, "answer") == 0 ) {
                        check(i, max_clients, message);
                    }
                }
            }
        }
        cnt:;
    }

    return 0;
}   