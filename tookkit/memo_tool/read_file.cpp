
const size_t MAX_LEN = 128;

typedef struct {
    char db_path[MAX_LEN];
} Data;

void readfile(Data *d) {
    const char *FileName = "/Users/zy.yuan/Develop/github.com/Flyingon/code_tpl_cpp/tookkit/memo_tool/config.ini";
    char LineBuf[MAX_LEN] = {0};
    FILE *configFile = fopen(FileName, "r");
    memset(d, 0, sizeof(Data));
    while (NULL != fgets(LineBuf, sizeof(LineBuf), configFile)) {
        size_t bufLen = strlen(LineBuf);
        if ('\r' == LineBuf[bufLen - 1] || '\n' == LineBuf[bufLen - 1]) {
            LineBuf[bufLen - 1] = '\0';
        }
        char *pos = strchr(LineBuf, ':');
        if (NULL != pos) {
            *pos = '\0';
            pos++;
            if (0 == strcmp(LineBuf, "db_path")) {
                for (; *pos == ' '; pos++) {}

                strcpy(d->db_path, pos);
            } else {
                printf("Failed to read config from the file.");
                break;
            }
        }
    }
    fclose(configFile);
    configFile = NULL;
    return;
}
