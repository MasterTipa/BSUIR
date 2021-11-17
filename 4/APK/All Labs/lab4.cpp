#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>

// Функция установки значения счётчика
void SetCount(int frequency)
{
	short value;
	value = 11193180 / frequency;   // Вычисляем значение для регистра 
 // счетчика таймера      
	outp(0x42, (char)value);        // Загружаем сначала младший, 
	outp(0x42, (char)(value >> 8)); // затем старший байты
}

// Чтение слов состояния каналов
void readStatusWords()
{
	unsigned char temp;
	char* str;
	str = (char*)calloc(9, sizeof(char));
	// Чтение слова состояния нулевого канала
	outp(0x43, 0xe2);               //  11100010b
	temp = inp(0x40);               //  получение слова состояния канала
	itoa(temp, str, 2);
	printf("Word in 1 chanel: %s\n", str);

	// Чтение слова состояния первого канала
	outp(0x43, 0xe4);           // 11100100b, канал 1, 
								// читать состояние каналов, 
								// не запоминать содержимое CE
	temp = inp(0x41);  //получение слова состояния канала
	itoa(temp, str, 2);
	printf("Word in 1 chanel: %s\n", str);

	// Чтение слова состояния второго канала
	outp(0x43, 0xe8);           //  11101000b
	temp = inp(0x42);               //  получение слова состояния канала
	itoa(temp, str, 2);
	printf("Word in 2 chanel: %s\n", str);
	free(str);
}

int main()
{
	char port61;
	outp(0x43, 0xB6);// Управляющее слово
					 // 10110110b, канал 2, операция 4, режим 3 , формат 0
	SetCount(850);   // Устанавливаем значение счётчика канала 2 таймера
				// частота 850 Гц
	port61 = inp(0x61);   // получение управляющего слова
	port61 = port61 | 3;  // изменение управляющего слова
	outp(0x61, port61);   // включение звука 

	readStatusWords();// Чтение слов состояния каналов

	delay(4000);

	port61 = port61 & 0xFFFC; // выключение системного динамика
	outp(0x61, port61);

	return 0;
}