#include <dos.h>



struct BitMask
{
    unsigned bit7: 1;
    unsigned bit6: 1;
    unsigned bit5: 1;
    unsigned bit4: 1;
    unsigned bit3: 1;
    unsigned bit2: 1;
    unsigned bit1: 1;
    unsigned bit0: 1;
};

struct VIDEO
{
	unsigned char symbol;
	unsigned char attribute;
};

int attribute = 0x03;

struct BitMask* mask;

//struct VIDEO far* out_reg(struct VIDEO far* screen, char reg);
void _print_(int offset, int reg);
void get_reg();

void interrupt(*_int8M_) (...); // pointer to previous interrupt function
void interrupt(*_int9M_) (...);
void interrupt(*_intAM_) (...);
void interrupt(*_intBM_) (...);
void interrupt(*_intCM_) (...);
void interrupt(*_intDM_) (...);
void interrupt(*_intEM_) (...);
void interrupt(*_intFM_) (...);
void interrupt(*_intC8M_) (...);

void interrupt(*_int70S_) (...);
void interrupt(*_int71S_) (...);
void interrupt(*_int72S_) (...);
void interrupt(*_int73S_) (...);
void interrupt(*_int74S_) (...);
void interrupt(*_int75S_) (...);
void interrupt(*_int76S_) (...);
void interrupt(*_int77S_) (...);

void interrupt _newint8M_(...) { get_reg(); _int8M_(); }// new interrupt function
void interrupt _newint9M_(...) {
    if(attribute > 0x05)
        attribute = 0x02;
    ++attribute; 
    get_reg(); 
    _int9M_(); 
}
void interrupt _newintAM_(...) { get_reg(); _intAM_(); }
void interrupt _newintBM_(...) { get_reg(); _intBM_(); }
void interrupt _newintCM_(...) { get_reg(); _intCM_(); }
void interrupt _newintDM_(...) { get_reg(); _intDM_(); }
void interrupt _newintEM_(...) { get_reg(); _intEM_(); }
void interrupt _newintFM_(...) { get_reg(); _intFM_(); }
void interrupt _newintC8M_(...) { get_reg(); _intC8M_(); }

void interrupt _newint70S_(...) { get_reg(); _int70S_(); }
void interrupt _newint71S_(...) { get_reg(); _int71S_(); }
void interrupt _newint72S_(...) { get_reg(); _int72S_(); }
void interrupt _newint73S_(...) { get_reg(); _int73S_(); }
void interrupt _newint74S_(...) { get_reg(); _int74S_(); }
void interrupt _newint75S_(...) { get_reg(); _int75S_(); }
void interrupt _newint76S_(...) { get_reg(); _int76S_(); }
void interrupt _newint77S_(...) { get_reg(); _int77S_(); }



void get_reg(){
    int MQR = 0;
    int MSR = 0;
    int MMR = 0;
    int SRQ = 0;
    int SSR = 0;
    int SMR = 0;
    
    MMR = inp(0x21);// get Master Mask Register
    _print_(0, MMR);
    outp(0x20, 0x0B);//
    MSR = inp(0x20); // get Master Service Register
    _print_(80, MSR);
    outp(0x20, 0x0A);//
    MQR = inp(0x20);// get Master Query Register
    _print_(80*2, MQR);

    SMR = inp(0xA1);// get Slave Mask Register
    _print_(80*3, SMR);
    outp(0xA0, 0x0B);//
    SSR = inp(0xA0);// get Slave Service Register
    _print_(80*4, SSR);
    outp(0xA0, 0x0A);//
    SRQ = inp(0xA0);// get Slave Query Register
    _print_(80*5, SRQ);
}


//struct VIDEO far* screen;
void _print_(int offset, int reg){
    VIDEO far* screen = (VIDEO far*)MK_FP(0xB800, 0); // get pointer to videobuff
    char temp = 0;
    screen+=offset;
    for (int i = 7; i >= 0; --i){
      temp = reg % 2;
      reg /= 2;
      screen->symbol = temp + '0';
      screen->attribute = attribute;
      ++screen;
    }
}


void init(void){
    _int8M_ = getvect(0x08); // get IRQ0
    _int9M_ = getvect(0x09); // get IRQ1
    _intAM_ = getvect(0x0A); // get IRQ2
    _intBM_ = getvect(0x0B); // get IRQ3
    _intCM_ = getvect(0x0C); // get IRQ4
    _intDM_ = getvect(0x0D); // get IRQ5
    _intEM_ = getvect(0x0E); // get IRQ6
    _intFM_ = getvect(0x0F); // get IRQ7
    _intC8M_ = getvect(0x78);

    _int70S_ = getvect(0x70); // get IRQ8
    _int71S_ = getvect(0x71); // get IRQ9
    _int72S_ = getvect(0x72); // get IRQ10
    _int73S_ = getvect(0x73); // get IRQ11
    _int74S_ = getvect(0x74); // get IRQ12
    _int75S_ = getvect(0x75); // get IRQ13
    _int76S_ = getvect(0x76); // get IRQ14
    _int77S_ = getvect(0x77); // get IRQ15

    setvect(0xC8, _newint8M_); // set new interrupt function to IRQ0
    setvect(0xC9, _newint9M_); // set new interrupt function to IRQ1
    setvect(0xCA, _newintAM_); // set new interrupt function to IRQ2
    setvect(0xCB, _newintBM_); // set new interrupt function to IRQ3
    setvect(0xCC, _newintCM_); // set new interrupt function to IRQ4
    setvect(0xCD, _newintDM_); // set new interrupt function to IRQ5
    setvect(0xCE, _newintEM_); // set new interrupt function to IRQ6
    setvect(0xCF, _newintFM_); // set new interrupt function to IRQ7


    setvect(0x08, _newint70S_); // set new interrupt function to IRQ8
    setvect(0x09, _newint71S_); // set new interrupt function to IRQ9
    setvect(0x0A, _newint72S_); // set new interrupt function to IRQ10
    setvect(0x0B, _newint73S_); // set new interrupt function to IRQ11
    setvect(0x0C, _newint74S_); // set new interrupt function to IRQ12
    setvect(0x0D, _newint75S_); // set new interrupt function to IRQ13
    setvect(0x0E, _newint76S_); // set new interrupt function to IRQ14
    setvect(0x0F, _newint77S_); // set new interrupt function to IRQ15

    _disable(); // disable all interruptions
    outp(0x20, 0x11); //master ICW1
    outp(0x21, 0xC8); //master ICW2
    outp(0x21, 0x04); //master ICW3
    outp(0x21, 0x01); //master ICW4

    outp(0xA0, 0x11); //slave ICW1
    outp(0xA1, 0x08); //slave ICW2
    outp(0xA1, 0x02); //slave ICW3
    outp(0xA1, 0x01); //slave ICW4
    _enable(); // enable all interruption

}

int main(){
    unsigned far *fp;
    init();

    FP_SEG (fp) = _psp; 
    FP_OFF (fp) = 0x2c; 
    _dos_freemem(*fp);
    _dos_keep(0, (_DS -_CS)+(_SP/16)+1);

    return 0;
}