/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:11:14 by grohr             #+#    #+#             */
/*   Updated: 2025/02/19 17:58:02 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Fonction pour envoyer un caractère bit par bit
//
// if ((c & (0x01 << bit)) != 0) :
//
// "&" compare bit par bit "c" et 0x01 << bit en binaire cad 00000001 decalé de <bit> crans vers la gauche
// ex :
// Si bit = 3 et c = 'a' (01110011) en binaire.
// On compare 01110'0'11 avec 00000'1'00
// On voit bien que 1 est diff de 0 donc (i & (0x01 << bit)) est égal à 0.
// On renvoie SIGUSR1
void    ft_send_bits(int pid, char i)
{
    int bit;

    bit = 0;
    while (bit < 8)    // Pour chaque bit du caractère
    {
        if ((i & (0x01 << bit)) != 0)    // Si le bit est 1
            kill(pid, SIGUSR1);    // On envoie SIGUSR1
        else    // Si le bit est 0
            kill(pid, SIGUSR2);    // On envoie SIGUSR2
        usleep(100);    // On attend un peu pour éviter de surcharger le serveur
        bit++;
    }
}

int main(int argc, char **argv)
{
    int pid;
    int i;

    i = 0;
    if (argc == 3)    // Le client doit avoir 2 arguments : PID et message
    {
        pid = ft_atoi(argv[1]);    // On convertit le PID en entier
        while (argv[2][i] != '\0')    // Pour chaque caractère du message
        {
            ft_send_bits(pid, argv[2][i]);    // On envoie le caractère
            i++;
        }
        ft_send_bits(pid, '\n');    // On envoie un retour à la ligne à la fin
    }
    else
    {
        ft_printf("\033[91mError: wrong format.\033[0m\n");
        ft_printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
        return (1);
    }
    return (0);
}
