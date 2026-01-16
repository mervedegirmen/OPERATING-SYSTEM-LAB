# tr: Derleyici ve bayraklar (-g debug sembolleri, -Wall tüm uyarılar)
# en: Compiler and flags (-g debug symbols, -Wall all warnings)
CC      = gcc
CFLAGS  = -g -Wall

# tr: Hedef ikili dosya adı
# en: Target binary name
TARGET  = prog6_run

# tr: Kaynak ve header dosyaları
# en: Sources and headers
SRCS    = prog6.c calculator.c
HDRS    = calculator.h

# tr: SRCS'den .o listesi türet (prog6.o calculator.o)
# en: Derive .o list from SRCS (prog6.o calculator.o)
OBJS    = $(SRCS:.c=.o)

# tr: Varsayılan hedef
# en: Default target
all: $(TARGET)

# tr: Link aşaması: .o dosyalarından ikiliyi üret
# en: Link stage: produce binary from .o files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# tr: Her .c için genel kural: ilgili .o'yu üret
# en: Generic rule for each .c: build corresponding .o
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# tr: Temizlik
# en: Clean artifacts
clean:
	rm -f $(TARGET) $(OBJS)