#ifndef HOTE_H_INCLUDED
#define HOTE_H_INCLUDED
#pragma once

#include <windows.h>
#include <unistd.h>
#include <winsock2.h>
#include <pthread.h>
#include <ctype.h>
typedef int socklen_t;

#include "Commande.h"
#include "Affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORT 23

void showHost();
void hote();
void EnvoieHote(char *cBuffer, SOCKET cSock);
void* ReceptionHote(void* data);

#endif
