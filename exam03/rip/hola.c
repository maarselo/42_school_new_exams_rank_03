#include <stdio.h>

int ft_strlen(char *str) {
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_check(char *str) {
    int i = 0;
    int open = 0;
    
    while(str[i]) {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')') {
            if (open == 0)
                return (1);
            open--;
        }
        i++;
    }
    if (open > 0)
        return (1);
    return (0);
}

void ft_rip(int open_needed, int close_needed, int start, int len, char *str) {
    
    // 🛑 Llegaste al final
    if (start == len) {
        if (open_needed == 0 && close_needed == 0 && !ft_check(str))
            puts(str);
        return;
    }
    
    // 🔀 OPCIÓN 1: ELIMINAR (si es necesario)
    if (open_needed > 0 && str[start] == '(') {
        str[start] = ' ';
        ft_rip(open_needed - 1, close_needed, start + 1, len, str);
        str[start] = '(';  // Vuelve al original
    }
    if (close_needed > 0 && str[start] == ')') {
        str[start] = ' ';
        ft_rip(open_needed, close_needed - 1, start + 1, len, str);
        str[start] = ')';  // Vuelve al original
    }
    
    // 🔀 OPCIÓN 2: MANTENER
    ft_rip(open_needed, close_needed, start + 1, len, str);
}

int main(int argc, char **argv) {
    if (argc != 2)
        return (0);
    
    int len = ft_strlen(argv[1]);
    
    // Si ya está balanceado, imprímelo y sal
    if (!ft_check(argv[1]))
        return (puts(argv[1]), 0);
    
    // 📊 Calcula cuántos sobran (CORRECTAMENTE)
    int i = 0;
    int open = 0;    // Cajas sin tapa
    int close = 0;   // Tapas sin caja
    
    while (argv[1][i]) {
        if (argv[1][i] == '(')
            open++;
        else if (argv[1][i] == ')') {
            if (open > 0)
                open--;      // Empareja
            else
                close++;     // Tapa sin caja
        }
        i++;
    }
    
    ft_rip(open, close, 0, len, argv[1]);
    
    return (0);
}
