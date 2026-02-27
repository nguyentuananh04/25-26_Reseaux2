#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

int main(int argc, char* argv[])
{
    unsigned char message[MAX_INFO];
    int taille_msg;
    paquet_t pData, pAck; /*pData: pacquet de données à transert
                            pAck: pacquet d'acquittement*/

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau: OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    de_application(message, &taille_msg);

    while(taille_msg != 0) {
        for (int i = 0; i < taille_msg; i++)
        {
            pData.info[i] = message[i];
        }
        pData.lg_info = taille_msg;
        pData.somme_ctrl = generer_control(pData);
        pData.type = DATA;

        while (pAck.type != ACK)
        {
            vers_reseau(&pData);
            de_reseau(&pAck);
        }
        
        de_application(message, &taille_msg);
    }
}