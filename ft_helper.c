#include "main.h"

int length(char *str)
{
        int i = 0;
        while (str[i])
                i++;
        return i;
}

int str_cmp(char *s1, char *s2)
{
        int i = 0;                                                                       while (s1[i] && s2[i])
        {
                if (s1[i] != s2[i])
                        return (s1[i] - s2[i]);
                i++;
        }
        return 0;
}

void ft_strcat(char *dest, char *str)
{
        int i = 0;
        int len = length(dest);
        while (str[i])                                                                   {
                dest[len] = str[i];                                                              len++;
                i++;                                                                     }
        dest[len] = '\0';
}

void ft_free(char *str)
{
        int i = 0;
        while (str[i])
        {
                str[i] = '\0';
                i++;
        }
}

int execut(char *cmd)
{
        int state;
        int i;
        char **args;
        char *str;

        str = strtok(cmd, " ");
        args = malloc(length(cmd) + 1);
        i = 0;
        while (str != NULL && i < length(cmd))
        {
                args[i] = str;
                str = strtok(NULL, " ");
                i++;
        }
        args[i] = NULL;
        state = execvp(args[0], args);
        free(args);
        return state;
}
