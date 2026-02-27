#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

int main(int argc, char* argcv[]) {
    unsigned char message[MAX_INFO];
    paquet_t pData, pAck;
    int fin = 0;
    int i = 0;

    init_reseau(RECEPTION);

    printf("Initialisation reseau: OK.\n");
    printf("Debut execution protocole transport.\n");

    while (!fin)
    {
        de_reseau(&pData); /* reception de données depuis la couche reseau */

        /* verifier la somme control pour generer le type du paquet d'acuittement */
        if (verifier_controle(pData))
        {
            for (int i = 0; i < pData.lg_info; i++)
            {
                message[i] = pData.info[i];
            }
            pAck.type = ACK;
            fin = vers_application(message, pData.lg_info); 
        }
        else
        {
            pAck.type = NACK;
        }
        vers_reseau(&pAck);
    }
    
    printf("[TRP] Fin execution protocole transport.\n");

    return 0;
}