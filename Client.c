#include "Client.h"

int nFonctionnementClient=1;

void client(void)
{
    pthread_t threadRecept;

    WSADATA WSAData;
    int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);

    SOCKET sock;
    SOCKADDR_IN sin;

    if(!erreur)
    {
        /* Création de la socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);

        char cIP[15]={'\0'};
        printf("Veuillez rentrer l'adresse IP de l'hote.\n");
        fflush(stdin);
        fgets(cIP,sizeof(cIP),stdin);
        fflush(stdin);

        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr(cIP);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);

        /* Si l'on a réussi à se connecter */
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        {
            printf("Connection a %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

            pthread_create(&threadRecept,NULL,ReceptionClient,(void*)sock);

            system("cls");
            printf("Le tchat est lance.\nLe jeu est lance.\n");

            char cBuffer[100];
            int nEnigme1=0;
            int nEnigme2=0;
            int nFin=0;

            Introduction();
            AfficheSalleJ2();
            while(nFonctionnementClient>0)
            {
                fgets(cBuffer,sizeof(cBuffer),stdin);
                char *cInput=cBuffer;
                char *cVerb=strtok(cInput," \n");
                if (cVerb!=NULL)
                {
                    if (strcmp(strupr(cVerb),"TCHAT")==0)
                    {
                        char *cNoun=strtok(NULL,"");
                        EnvoieClient(cNoun,sock);
                    }
                    else if(strcmp(strupr(cVerb),"COMMANDE")==0)
                        Commande();
                    else if(strcmp(strupr(cVerb),"QUITTER")==0)
                    {
                        nFonctionnementClient=0;
                        char *cNoun="Sulta";
                        //Ca veut dire "Fin" en draconique de D&D pour éviter qu'un joueur rentre ça sans faire exprès.
                        EnvoieClient(cNoun,sock);
                    }
                    else if(strcmp(strupr(cVerb),"INDICE")==0)
                        Indice();
                    else if(strcmp(strupr(cVerb),"INSPECTER")==0)
                    {
                        char *cNoun=strtok(NULL," \n");
                        if (strcmp(strupr(cNoun),"TELEVISION")==0)
                            descTelevision();
                        else if (strcmp(strupr(cNoun),"GRAVURE")==0)
                        {
                            CarreMagique();
                            descGravure();
                            if (nEnigme1==1)
                                Code2();
                        }
                        else if (strcmp(strupr(cNoun),"BOUGIE")==0)
                            descBougie();
                        else
                            nonReconnu();
                    }
                    else if(strcmp(strupr(cVerb),"REPONSE")==0)
                    {
                        char *cNoun=strtok(NULL," \n");
                        if (strcmp(strupr(cNoun),"36")==0)
                        {
                            printf("C'est une bonne reponse !\n");
                            Code2();
                            printf("Un bouton etrange apparait, essayez la commande Bouton.\n");
                            nEnigme1=1;
                        }
                        else if (strcmp(strupr(cNoun),"1")==0)
                        {
                            printf("C'est une bonne reponse !\n");
                            Code4();
                            nEnigme2=1;
                        }
                    }
                    else if(strcmp(strupr(cVerb),"BOUTON")==0)
                    {
                        enigmeJ2();
                        if (nEnigme2==1)
                            Code4();
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
                            nFonctionnementClient=0;
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
        }
        /* sinon, on affiche "Impossible de se connecter" */
        else
        {
            printf("Impossible de se connecter\n");
        }

        /* On ferme la socket */
        closesocket(sock);
        printf("Fermeture de la connexion.\n");
    }
    WSACleanup();
    printf("Fermeture du jeu.\n");
    return EXIT_SUCCESS;
}


void* ReceptionClient(void* data)
{
    char cBufferReception[100];
    while (nFonctionnementClient>0)
    {
        /* Si l'on reçoit des informations : on les affiche à l'écran */
        if (nFonctionnementClient>0 && recv((int)data, cBufferReception, 100, 0) != SOCKET_ERROR)
        {
            if (strcmp(cBufferReception,"Sulta")==0)
            {
                nFonctionnementClient=0;
            }
            else
            {
                printf("[Serveur]: %s\n", cBufferReception);
            }
        }
    }
    return 0;
}

void EnvoieClient(char *cBuffer, SOCKET cSock)
{
    int sock_err;

    sock_err = send(cSock, cBuffer, 100, 0);

    if(sock_err != SOCKET_ERROR)
    {
        if (strcmp(cBuffer,"Sulta")!=0)
            printf("[Client]: %s\n", cBuffer);
    }
    else
        printf("Erreur de transmission\n");

    fflush(stdin);
}
