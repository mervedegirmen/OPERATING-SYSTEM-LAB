# tr: Derleyici ve bayraklar
# en: Compiler and flags
CC = gcc
CFLAGS = -g -Wall

# tr: Varsayılan hedef: prog5_run ikilisini oluşturur.
# en: Default target: builds the prog5_run binary.
all: prog5_run

# tr: prog5_run hedefinin nasıl üretileceği (tek kaynak dosya).
# en: How to build prog5_run (single source file).
prog5_run: prog5.c
	$(CC) $(CFLAGS) -o prog5_run prog5.c

# tr: Temizlik hedefi: çıktı ve geçici dosyaları siler.
# en: Clean target: remove build artifacts.
clean:
	rm -f prog5_run
