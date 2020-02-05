#include "Commande.h"

void Commande()
{
    printf("Les commandes possibles sont :\n-Tchat afin de communiquer avec votre compagnon.\n-Quitter pour fermer le jeu.\n-Indice pour afficher la liste de vos indices.\n-Inspecter puis le nom de l'objet que vous voulez inspecter.\n-Reponse suivi de votre reponse pour donner votre reponse a une enigme.\n-Code suivi du code secret si vous l'avez trouve.\n");
}


void Avertissement()
{
    printf("Commande non reconnue, vous pouvez taper : Commande pour avoir la liste des commandes.\n");
}

void Introduction()
{
    printf("Bienvenue a vous deux !\nPour sortir, vous allez devoir cooperer et resoudre des enigmes pour trouver le code a 4 caracteres, afin de vous aider, voici le seul indice dont vous disposez: \"RJBV\".\nBon courage !\n");
}

void Indice()
{
     printf("Le seul indice dont vous disposez est \"RJBV\".\n");
}

void nonReconnu()
{
    printf("Objet non reconnu.\n");
}

void Victoire()
{
    printf("Felicitations vous parvenez a entrer le bon code et vous entendez un cliquetis satisfaisant.\n");
    printf("Quand vous testez la porte, elle est ouverte, vous pouvez taper la commande sortir pour sortir.\n");
    printf("Pensez cependant a aider votre compagnon si ce n'est deja fait, il vous a aide aussi apres tout.\n");
}

void Fin()
{
    printf("Vous parvenez a sortir de cette etrange piece et retrouvez votre liberte !\nVous avez complete le jeu felicitations !\n");
}

void Ferme()
{
    printf("Vous essayez de sortir, cependant la porte est ferme, il vous faut entrer le code pour sortir.\n");
}

void CodeMauvais()
{
    printf("Malheureusement vous n'avez pas rentre le bon code a quatre chiffre, la porte ne s'ouvre pas.\n");
}
