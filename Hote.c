#include "Hote.h"

int nFonctionnementHote=1;

void hote(void)
{
    pthread_t threadRecept;

    WSADATA WSAData;
    int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);

    SOCKET sock;
    SOCKADDR_IN sin;
    SOCKET csock;
    SOCKADDR_IN csin;
    socklen_t recsize = sizeof(csin);
    int sock_err;


    /* Si les sockets Windows fonctionnent */
    if(!erreur)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        /* Si la socket est valide */
        if(sock != INVALID_SOCKET)
        {
            printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

            /* Configuration */
            sin.sin_addr.s_addr     = htonl(INADDR_ANY);   /* Adresse IP automatique */
            sin.sin_family          = AF_INET;             /* Protocole familial (IP) */
            sin.sin_port            = htons(PORT);         /* Listage du port */
            //sin.sin_addr.s_addr = inet_addr("127.0.0.1");
            sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));


            /* Si la socket fonctionne */
            if(sock_err != SOCKET_ERROR)
            {
                //Tentative d'affichage de l'IP.
                showHost();

                /* Démarrage du listage (mode server) */
                sock_err = listen(sock, 5);
                printf("Listage du port %d...\n", PORT);

                /* Si la socket fonctionne */
                if(sock_err != SOCKET_ERROR)
                {
                    /* Attente pendant laquelle le client se connecte */
                    printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);

                    csock = accept(sock, (SOCKADDR*)&csin, &recsize);
                    printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

                    pthread_create(&threadRecept,NULL,ReceptionHote,(void*)csock);

                    system("cls");
                    printf("Le tchat est lance.\nLe jeu est lance.\n");

                    char cBuffer[100];
                    int nEnigme1=0;
                    int nEnigme2=0;
                    int nFin=0;

                    Introduction();
                    AfficheSalleJ1();

                    while(nFonctionnementHote>0)
                    {
                        fgets(cBuffer,sizeof(cBuffer),stdin);

                        char *cInput=cBuffer;
                        char *cVerb=strtok(cInput," \n");
                        if (cVerb!=NULL)
                        {
                            if (strcmp(strupr(cVerb),"TCHAT")==0)
                            {
                                char *cNoun=strtok(NULL,"");
                                EnvoieHote(cNoun,csock);
                            }
                            else if(strcmp(strupr(cVerb),"COMMANDE")==0)
                                Commande();
                            else if(strcmp(strupr(cVerb),"QUITTER")==0)
                            {
                                nFonctionnementHote=0;
                                char *cNoun="Sulta";
                                //Ca veut dire "Fin" en draconique de D&D pour éviter qu'un joueur rentre ça sans faire exprès.
                                EnvoieHote(cNoun,csock);
                            }
                            else if(strcmp(strupr(cVerb),"INDICE")==0)
                                Indice();
                            else if(strcmp(strupr(cVerb),"INSPECTER")==0)
                            {
                                char *cNoun=strtok(NULL," \n");
                                if (strcmp(strupr(cNoun),"TABLEAU")==0)
                                    descTableau();
                                else if (strcmp(strupr(cNoun),"CAGE")==0)
                                    descCage();
                                else if (strcmp(strupr(cNoun),"PILE DE CUBES")==0 || strcmp(strupr(cNoun),"PILE")==0)
                                {
                                    affPile();

                                    if (nEnigme1==1)
                                        Code1();
                                }
                                else
                                    nonReconnu();
                            }
                            else if(strcmp(strupr(cVerb),"REPONSE")==0)
                            {
                                char *cNoun=strtok(NULL," \n");
                                if (strcmp(strupr(cNoun),"10")==0)
                                {
                                    printf("C'est une bonne reponse !\n");
                                    Code1();
                                    printf("Un bouton etrange apparait, essayez la commande Bouton.\n");
                                    nEnigme1=1;
                                }
                                else if (strcmp(strupr(cNoun),"2")==0)
                                {
                                    printf("C'est une bonne reponse !\n");
                                    Code3();
                                    nEnigme2=1;
                                }
                            }
                            else if(strcmp(strupr(cVerb),"BOUTON")==0)
                            {
                                enigmeJ1();
                                if (nEnigme2==1)
                                    Code3();
                            }
                            else if(strcmp(strupr(cVerb),"CODE")==0)
                            {
                                char *cNoun=strtok(NULL," \n");
                                if (strcmp(strupr(cNoun),"CHAT")==0)
                                {
                                    Victoire();
                                    nFin=1;
                                }
                                else
                                    CodeMauvais();
                            }
                            else if(strcmp(strupr(cVerb),"SORTIR")==0)
                            {
                                if (nFin==1)
                                {
                                    Fin();
                                    nFonctionnementHote=0;
                                }
                                else
                                    Ferme();
                            }
                            else
                                Avertissement();
                        }
                    }


                    pthread_exit(threadRecept);
                    //pthread_join(threadRecept,NULL);

                    /* Il ne faut pas oublier de fermer la connexion (fermée dans les deux sens) */
                    shutdown(csock, 2);
                }
            }
            /* Fermeture de la socket */
            closesocket(sock);
            printf("Fermeture de la connexion.\n");
        }
    }
    WSACleanup();
    printf("Fermeture du jeu.\n");
    return EXIT_SUCCESS;
}

void showHost()
{
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    //printf("Hostname: %s\n", hostname);
    struct hostent* remoteHost;
    remoteHost = gethostbyname(hostname);
    char* ip;
    ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
    printf("Votre adresse IP est : %s.\n", ip);
}

void* ReceptionHote(void* data)
{
    char cBufferReception[100];
    while (nFonctionnementHote>0)
    {
        /* Si l'on reçoit des informations : on les affiche à l'écran */
        if (nFonctionnementHote>0 && recv((int)data, cBufferReception, 100, 0) != SOCKET_ERROR)
        {
            if (strcmp(cBufferReception,"Sulta")==0)
            {
                nFonctionnementHote=0;
            }
            else
            {
                printf("[Client]: %s\n", cBufferReception);
            }
        }
    }
    return 0;
}

void EnvoieHote(char *cBuffer, SOCKET cSock)
{
    int sock_err;

    sock_err = send(cSock, cBuffer, 100, 0);

    if(sock_err != SOCKET_ERROR)
    {
        if (strcmp(cBuffer,"Sulta")!=0)
            printf("[Serveur]: %s\n", cBuffer);
    }
    else
        printf("Erreur de transmission\n");

    fflush(stdin);
}
