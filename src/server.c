/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:20:11 by grohr             #+#    #+#             */
/*   Updated: 2025/02/19 18:21:10 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Fonction de gestion des signaux
void    ft_handler(int signal)
{
    static int	bit;    // Compteur de bits reçus (persistant entre les appels)
    static int	c_created;      // Caractère en cours de construction (persistant entre les appels)

    if (signal == SIGUSR1)
        c_created |= (0x01 << bit);    // Si SIGUSR1 est reçu, on met le bit correspondant à 1
    bit++;    // On passe au bit suivant
    if (bit == 8)    // Si on a reçu 8 bits (un caractère complet)
    {
        ft_printf("%c", c_created);    // On affiche le caractère
        bit = 0;    // On réinitialise le compteur de bits
        c_created = 0;      // On réinitialise le caractère en construction
    }
}

int main(int argc, char **argv)
{
    int pid;

    (void)argv;    // Pour éviter un warning de variable non utilisée
    if (argc != 1)    // Le serveur ne doit pas avoir d'arguments
    {
        ft_printf("\033[91mError: wrong format.\033[0m\n");
        ft_printf("\033[33mTry: ./server\033[0m\n");
        return (0);
    }
    pid = getpid();    // On récupère le PID du processus serveur
    ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
    ft_printf("\033[90mWaiting for a message...\033[0m\n");
    while (argc == 1)    // Boucle infinie tant que le programme n'est pas interrompu
    {
        signal(SIGUSR1, ft_handler);    // On associe SIGUSR1 à ft_handler
        signal(SIGUSR2, ft_handler);    // On associe SIGUSR2 à ft_handler
        pause();    // On met le processus en pause jusqu'à réception d'un signal
    }
    return (0);
}
