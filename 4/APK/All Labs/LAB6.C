#include <dos.h>
#include <conio.h>
#include <stdio.h>

void interrupt newInt9(void);     // �㭪�� ��ࠡ�⪨ ���뢠���
void interrupt (*oldInt9)(void);  // �����⥫� �� ���뢠���

void indicator(unsigned char mask); // �㭪�� �ࠢ����� �������ࠬ�
void blinking (void);    // �㭪�� ������� �������ࠬ�

int isResend = 1;  // ���� �訡�� / ����室����� ����୮� ��।�� ������
int quitFlag = 0;
int blinkingON = 0;

void main()
{
	oldInt9 = getvect(9);	// ���࠭塞 ��஥ ���뢠���
	setvect(9, newInt9);	// ���塞 ��� �� �����	
	while(!quitFlag)	 // ���� �� ��⠭����� 䫠� ��室�
	{
		if (blinkingON) 		// �᫨ ��⠭����� 䫠� ������� �������஢ 
			blinking(); // ������ �������ࠬ�
	}		
	setvect(9, oldInt9);    // ����⠭�������� ��஥ ���뢠���
	return;
}

// �㭪�� ��ࠡ�⪨ ���뢠���
void interrupt newInt9()
{
	unsigned char value = 0;
	oldInt9();
	value = inp(0x60);    // ����砥� ���祭�� �� ���� 60h
	if(value == 0x01) quitFlag = 1; // ��⠭�������� 䫠� ��室�, �᫨ ����� Esc	
	
	if (value == 0x26 && blinkingON == 0) blinkingON = 1;  // ���⠢��� ��� ���� 䫠� �������
	else if (value == 0x26 && blinkingON == 1) blinkingON = 0;
	
	if (value != 0xFA && blinkingON == 1)    // �᫨ ��� ���⢥ত���� �ᯥ譮�� �믮������ �������
		isResend = 1; 	// ��⠭�������� 䫠� ����୮� ��।�� ����
	else isResend = 0;
	
	
		if (blinkingON) 		// �᫨ ��⠭����� 䫠� ������� �������஢ 
			blinking(); // ������ �������ࠬ�
	

	printf("\t%x", value);
	outp(0x20, 0x20);       // ���� ����஫��� ���뢠���
}

// �㭪�� �ࠢ����� �������ࠬ�
void indicator(unsigned char mask)
{
	isResend = 1;
	while (isResend)     // ���� ��� ���⢥ত���� �ᯥ譮�� �믮������ �������
	{
		while((inp(0x64) & 0x02) != 0x00); // ������� �᢮�������� �室���� ���� ����������
		outp(0x60, 0xED);	// �����뢠�� � ���� ������� �ࠢ����� �������ࠬ�
		delay(50);
	}
	
	isResend = 1;
	while (isResend)    // ���� ��� ���⢥ত���� �ᯥ譮�� �믮������ �������
	{
		while((inp(0x64) & 0x02) != 0x00);  // ������� �᢮�������� �室���� ���� ����������
		outp(0x60, mask);     // �����뢠�� � ���� ��⮢�� ���� ��� ����ன�� �������஢
		delay(50);
	}
}

// �㭪�� ������� �������ࠬ�
void blinking ()
{
	indicator(0x02); // ���. �������� Num Lock
	delay(150);
	indicator(0x04); // ���. �������� Caps Lock
	delay(150);
	indicator(0x6); // ���. Num Lock � Caps Lock
	delay(200);
	indicator(0x00); // �몫. �� ���������
    delay(50);
	indicator(0x06); // ���. Num Lock � Caps Lock
    delay(100);
    indicator(0x00); // �몫. �� ���������
}
