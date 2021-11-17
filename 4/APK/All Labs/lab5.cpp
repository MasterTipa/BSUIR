#include <dos.h>
#include <ctype.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>


int msCounter = 0;

void interrupt (*oldHandler)(...);
void interrupt newHandler(...){
    msCounter++;
	outp(0x70,0x0C); //код для прерывания
	inp(0x71); //инициализация прерывания для контроллера
	outp(0x20, 0x20);
	outp(0xA0, 0x20);
}

void WaitForMSCounter(unsigned long delayPeriod){
	msCounter = 0;
	while(msCounter != delayPeriod);
}

int BCDToInteger (int bcd){
	return bcd % 16 + bcd / 16 * 10;
}

unsigned char IntToBCD (int value){
	return (unsigned char)((value/10)<<4)|(value%10);
}

void WaitClockIsFree(){
	do{
		outp(0x70, 0x0A);
	} while( inp(0x71) & 0x80 ); // ожидание единицы в бите номер 7
}

void LockClockUpdate(){ //запретить обновление часов
	unsigned char value;
	WaitClockIsFree(); //вызвать функцию ожидания
	outp(0x70,0x0B); //записать в порт 70h значение 11 (регистр состояния 0Bh)
	value = inp(0x71); //считать при помощи порта 71h состояние регистра 0Bh
	value|=0x80; //изменить 7й бит на 1
	outp(0x70, 0x0B); //записать в порт 70h значение 11 (регистр состояния 0Bh)
	outp(0x71, value); //вывести в регистр 0Bh полученное значение
}

void UnlockClockUpdate(){
	unsigned char value;
	WaitClockIsFree(); //вызвать функцию ожидания 
	outp(0x70,0x0B); //записать в порт 70h значение 11 (регистр состояния 0Bh)
	value = inp(0x71); //считать при помощи порта 71h состояние регистра 0Bh
	value-=0x80; //изменить 7й бит на 0
	outp(0x70, 0x0B); //записать в порт 70h значение 11 (регистр состояния 0Bh)
	outp(0x71, value); //вывести в регистр 0Bh полученное значение
}


void GetTime(){
	unsigned char value;
	WaitClockIsFree();
	outp(0x70, 0x04); // получить часы
	value = inp(0x71); 
	printf("%d:",BCDToInteger(value)); 
	WaitClockIsFree();
	outp(0x70, 0x02); // получить минуты
	value = inp(0x71); 
	printf("%d:",BCDToInteger(value)); 
	WaitClockIsFree();
	outp(0x70, 0x00); // получить секунды
	value = inp(0x71); 
	printf("%d   ",BCDToInteger(value)); 
	WaitClockIsFree();
	outp(0x70, 0x07); // получить день месяца
	value = inp(0x71); 
	printf("%d.",BCDToInteger(value)); 
	WaitClockIsFree();
	outp(0x70, 0x08); // получить номер месяца
	value = inp(0x71); 
	printf("%d.",BCDToInteger(value)); 
	WaitClockIsFree();
	outp(0x70, 0x09); // получить год
	value = inp(0x71); 
	printf("%d   ",BCDToInteger(value)); 
	WaitClockIsFree();
	outp(0x70, 0x06); // получить день недели
	value = inp(0x71);
	switch(BCDToInteger(value)) //вывод полученного дня недели
	{
		case 1: printf("Sunday\n"); break;
		case 2: printf("Monday\n"); break;
		case 3: printf("Tuesday\n"); break;
		case 4: printf("Wednesday\n"); break;
		case 5: printf("Thursday\n"); break;
		case 6: printf("Friday\n"); break;
		case 7: printf("Saturday\n"); break;		
		default: printf("Undefined day of week\n"); break;
	}
}

void SetTime(){
	int hours, minutes, seconds, weekDay, monthDay, month, year;	
	printf("Enter hours: "); 
	scanf("%d", &hours); //считать часы
	printf("Enter minutes: "); 
	scanf("%d", &minutes); //считать минуты
	printf("Enter seconds: "); 
	scanf("%d", &seconds); //считать секунды
	printf("Enter week day number: "); 
	scanf("%d", &weekDay); //считать номер дня недели
	printf("Enter day of month: "); 
	scanf("%d", &monthDay); //считать номер дня месяца 
	printf("Enter mounth: "); 
	scanf("%d", &month); //считать месяц 
	printf("Enter year: "); 
	scanf("%d", &year); //считать гооооод
	LockClockUpdate(); //вызываем функцию блокировки часов
	outp(0x70, 0x04); //запись в порт 70h (порт только для записи и выбора регистра CMOS памяти) значения 04h (выбор 4го регистра CMOS памяти для ввода часов)
	outp(0x71, IntToBCD(hours)); //запись в порт 71 (порт для записи и чтения данных из указанного в 70h регистра CMOS) значения часа в BCD	
	outp(0x70, 0x02); //запись в порт 70h значения 02h
	outp(0x71, IntToBCD(minutes)); //запись в порт 71 значения минут в BCD		
	outp(0x70, 0x00); //запись в порт 70h значения 00h
	outp(0x71, IntToBCD(seconds)); //запись в порт 71 значения секунд в BCD		
	outp(0x70, 0x06); //запись в порт 70h значения 06h
	outp(0x71, IntToBCD(weekDay)); //запись в порт 71 значения номера дня недели в BCD		
	outp(0x70, 0x07); //запись в порт 70h значения 07h
	outp(0x71, IntToBCD(monthDay)); //запись в порт 71 значения номера дня мецяца в BCD		
	outp(0x70, 0x08); //запись в порт 70h значения 08h
	outp(0x71, IntToBCD(month)); //запись в порт 71 значения месяца в BCD		
	outp(0x70, 0x09); //запись в порт 70h значения 09h
	outp(0x71, IntToBCD(year)); //запись в порт 71 значения года в BCD	
	UnlockClockUpdate(); //вызываем функцию разрешения обновления часов 
}

void CustomDelay()
{
	unsigned long ms;
	printf("Delay in ms: ");
	scanf("%ld", &ms);

	disable();
	oldHandler = getvect(0x70);
	setvect(0x70, newHandler);
	enable();

	outp(0xA1, inp(0xA1) & 0xFE); // разрешить прерывания часов

	outp(0x70, 0xB);
	outp(0x71, inp(0x71) | 0x40); //разрешить переодические прерывания

	msCounter = 0;
	while (msCounter <= ms);
	printf("Its work!");
	disable();
	setvect(0x70, oldHandler);
	enable();

}

void main(){
	char c, value;
	clrscr();
	printf("Press:\n'1' - Show time\n'2' - Set time\n'3' - Delay time\n'Esc' - quit\n\n");
	while(c != 27){
		c = getch(); //ожидавем ввода с клавиатуры
		switch(c){
			case '1': GetTime();break; //если введено 1
			case '2': SetTime();break; //если введено 2
			case '3': CustomDelay();break; //если введено 3
			case 27: break; //если введено ESC
		}
	}
}
