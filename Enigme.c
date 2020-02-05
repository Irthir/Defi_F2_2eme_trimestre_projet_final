#include "Enigme.h"

#define TAILLECARREMAGIQUE 7

void CarreMagique()
{
	color(14,0);

	int tabCarreMagique[TAILLECARREMAGIQUE][TAILLECARREMAGIQUE]={0};

	div_t divresult=div(TAILLECARREMAGIQUE,2);

	int nI,nJ;

    nI=divresult.quot-1;
    nJ=divresult.quot;

	tabCarreMagique[nI][nJ]=1;

	for (int nX=2; nX<=TAILLECARREMAGIQUE*TAILLECARREMAGIQUE;nX++)
    {
        nI--;
        nJ++;
        if (nJ>=TAILLECARREMAGIQUE)
            nJ=0;
        if (nI<0)
            nI=TAILLECARREMAGIQUE-1;
        while (tabCarreMagique[nI][nJ]!=0)
        {
            nI--;
            nJ--;
            if (nJ<0)
                nJ=TAILLECARREMAGIQUE-1;
            if (nI<0)
                nI=TAILLECARREMAGIQUE-1;
        }
        tabCarreMagique[nI][nJ]=nX;
    }



	for (int nI = 0; nI < TAILLECARREMAGIQUE; nI++)
	{
		for (int nX = 0; nX < TAILLECARREMAGIQUE; nX++)
		{
			printf("____");
		}
		printf("\n|");
		for (int nJ = 0; nJ < TAILLECARREMAGIQUE; nJ++)
		{
		    if (tabCarreMagique[nI][nJ]==36)
		    {
                printf(" ? ");
		    }
            else
                printf("%3d",(int)tabCarreMagique[nI][nJ]);
			printf("|");
		}
		printf("\n");
	}

	color(7,0);
}