#include <stdio.h>

extern void http_client_1(void);

typedef struct project_t
{
    const char *name;
    void (*app_callback)(void);
} project_t;

static project_t project_table[] =
{
    {"http_client_1", http_client_1},
};

int main(int argc, char **argv)
{
    if (argc != 2)
        return 0;

    printf("start test: \r\n");
    for (int i = 1; i < argv[1] - '0'; i++)
    {
        printf("%s: \r\n", project_table[i].name);
        project_table[i].app_callback();
    }
    printf("end test.\r\n");

    return 0;
}