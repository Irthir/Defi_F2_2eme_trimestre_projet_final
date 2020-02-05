#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#pragma once

#include <windows.h>
#include <unistd.h>
#include <winsock2.h>
#include <pthread.h>
#include <ctype.h>
typedef int socklen_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORT 23

#include "Commande.h"
#include "Affichage.h"
#include "Enigme.h"

void client();
void* ReceptionClient(void* data);
void EnvoieClient(char *cBuffer, SOCKET cSock);

#endif
