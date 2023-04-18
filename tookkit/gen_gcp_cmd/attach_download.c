
#include <stdio.h>

const char* cmd_attach_tpl = "kubectl exec -it %s -- /bin/bash";
const char* cmd_download_tpl = "kubectl cp %s:/deploy/%s ~/Job/temp/%s";

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("args is not enough, please use as: gen_tcpdump_cmd {pod} {file}\n");
        return -1;
    }
    printf(cmd_attach_tpl, argv[1]);
    printf("\n");
    printf("cd /deploy");
    printf("\n");
    printf("tcpdump -XX -vvv -nn -i any -w %s", argv[2]);
    printf("\n");
    printf(cmd_download_tpl, argv[1], argv[2], argv[2]);
    printf("\n");
}
