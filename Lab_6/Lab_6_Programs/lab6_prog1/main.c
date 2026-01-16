#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before exec - This will be printed\n");
    // Exec öncesi - Bu yazdırılacak
    
    printf("Executing 'ls -l' command...\n");
    // 'ls -l' komutu çalıştırılıyor...
    
    // execl(path, arg0, arg1, ..., NULL)
    execl("/bin/ls", "ls", "-l", NULL);
    
	printf("After exec - will this be printed?\n");
    // This line will NOT be executed if exec succeeds
    // Exec başarılı olursa bu satır ÇALIŞTIRILMAYACAK
    perror("execl failed");
    return 1;
}