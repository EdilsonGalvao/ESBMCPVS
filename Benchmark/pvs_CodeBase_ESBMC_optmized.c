#include <assert.h>
#include <stdio.h>

unsigned int nondet_uint();

#define MAX_INTEGER 2147483647;
#define GET_MATRIX_SIZE(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))

int LOWEST = MAX_INTEGER;

float _inverterSet [10][6] =   {{0.93, 48, 110, 700, 1600, 400.00},
                   {0.93, 48, 110, 1200, 2400, 750.00},
                   {0.93, 24, 120, 1200, 2400, 450.00},
                   {0.91, 24, 120, 280, 750, 149.75},
                   {0.91, 24, 120, 400, 1000, 187.25},
                   {0.93, 12, 220, 600, 1350, 342.25},
                   {0.93, 24, 120, 800, 1200, 500.00},
                   {0.90, 12, 120, 900, 2000, 649.75},
                   {0.82, 12, 120, 1000, 2000, 1122.25},
                   {0.90, 24, 125, 1800, 2900, 1669.75}};

float _controllerSet [12][6] = {{0.98, 35, 24, 13, 145, 294.95},
                   {0.98, 15, 24, 13, 75, 88.40},
                   {0.98, 15, 24, 13, 100, 137.70},
                   {0.98, 50, 24, 13, 100, 294.95},
                   {0.98, 20, 24, 13, 100, 132.25},
                   {0.98, 30, 24, 13, 100, 161.00},
                   {0.98, 40, 24, 13, 100, 184.75},
                   {0.97, 20, 24, 13, 100, 217.25},
                   {0.97, 30, 24, 13, 100, 297.25},
                   {0.98, 50, 48, 13, 150, 347.82},
                   {0.98, 60, 48, 13, 150, 388.91},
                   {0.96, 60, 60, 13, 140, 1072.50}};

float _batterySet [10][6] = {{0.85, 12, 80, 14.4, 13.8, 131.00},
                {0.85, 12, 105, 14.4, 13.8, 150.00},
                {0.85, 12, 150, 14.4, 13.8, 324.75},
                {0.85, 12, 175, 14.4, 13.8, 299.75},
                {0.85, 12, 220, 14.4, 13.8, 374.75},
                {0.85, 12, 60, 14.4, 13.8, 114.75},
                {0.85, 12, 80, 14.4, 13.2, 138.00},
                {0.85, 12, 150, 14.4, 13.2, 275.00},
                {0.85, 12, 170, 14.4, 13.2, 299.01},
                {0.85, 12, 220, 14.4, 13.2, 330.73}};

float _panelSet[10][13] = {{1.94432, 0.1620, 72, 45, 0.00053, -0.0031, 9.18, 45.1, 315, 8.16, 36.6, 33.4, 268.40},
                          {1.94432, 0.1646, 72, 45, 0.00053, -0.0031, 9.26, 45.3, 320, 8.69, 36.8, 33.6, 190.00},
                          {1.94432, 0.1672, 72, 45, 0.00053, -0.0031, 9.34, 45.5, 325, 8.78, 37.0, 33.7, 216.67},
                          {1.94432, 0.1697, 72, 45, 0.00053, -0.0031, 9.45, 45.6, 330, 8.88, 37.2, 33.9, 170.30},
                          {2.19384, 0.1515, 80, 47, 0.00020, -0.0048, 8.86, 50.8, 340, 8.26, 41.2, 37.0, 214.20},
                          {1.41075, 0.1600, 54, 47, 0.0000318, -0.00123, 8.21, 32.9, 200, 7.61, 32.9, 23.2, 300.00},
                          {1.62688, 0.1690, 60, 47, 0.00039, -0.00307, 9.44, 38.84, 275, 8.81, 31.22, 26.72, 150.00},
                          {1.94035, 0.1855, 72, 45, 0.00039, -0.00307, 9.73, 47.60, 360, 9.33, 38.59, 34.96, 237.24},
                          {1.00640, 0.1515, 36, 45, 0.00033, -0.0039, 8.81, 22.30, 150, 8.20, 18.30, 14.40, 94.75},
                          {0.99960, 0.1500, 36, 46, 0.00060, -0.0037, 8.61, 22.90, 150, 8.12, 18.50, 14.61, 108.50}};

int Vsystem = 24;  //12V, 24V, 36V or 48V: DC Bus voltage definition
int autonomy = 48; //autonomy in hours
int SOClimit = 75, SOCabsorption = 95, SOCfull = 100, Vbat = 12, VAC = 127;
int Phouse = 263, Psurge = 732, Econsumption = 2500;
float Insol = 3.80; 
float LCC;


int getLowestCost(int panel, int battery, int controller, int inverter)
{
    int NTP, NPP, NPS, NBtotal, NBS, NBP, NPPmin, ICmin;
    int arrang, NPmin;
    float Ecorrected, Ep, NTPmin, NPSmin1, NPSmin2, Cbank, Iscamb, NBSmin, NBPmin, Fobj;
    float Pminpanels, ItotalPVpanels, VtotalPVpanels, Eb, DODdaycalc, IminDCbus, equipcost, DODmax;

    unsigned char PanelChoice, BatteryChoice, ControllerChoice, InverterChoice; 
   
    // information from the PV Panel
    float Ap = _panelSet[panel][0];
    float np = _panelSet[panel][1];
    int N = (int)_panelSet[panel][2];    
    int NOCT = (int)_panelSet[panel][3]; 
    float mii = _panelSet[panel][4]; 
    float miv = _panelSet[panel][5]; 
    float Iscref = _panelSet[panel][6];
    float Vocref = _panelSet[panel][7];
    float Pmref = _panelSet[panel][8];
    float Imref = _panelSet[panel][9];
    float Vmref = _panelSet[panel][10];
    float VmpNOCT = _panelSet[panel][11];
    float PanelCost = _panelSet[panel][12];

    //battery information
    float nb = _batterySet[battery][0];
    int Vbat = (int)_batterySet[battery][1];
    int capacity = (int)_batterySet[battery][2];
    float Vbulk = _batterySet[battery][3]; //(14.40*NBS);
    float Vfloat = _batterySet[battery][4]; //(13.20*NBS);
    float BatteryCost = _batterySet[battery][5];

    // charge controller
    float nc = _controllerSet[controller][0];
    int IC = (int)_controllerSet[controller][1];
    int VC = (int)_controllerSet[controller][2];
    int Vmpptmin = (int)_controllerSet[controller][3];
    float VCmax = _controllerSet[controller][4];
    float ControllerCost = _controllerSet[controller][5];

    //inverter
    float ni = _inverterSet[inverter][0];
    int VinDC = (int)_inverterSet[inverter][1];
    int VoutAC = (int)_inverterSet[inverter][2];
    int PACref = (int)_inverterSet[inverter][3];
    int MAXACref = (int)_inverterSet[inverter][4];
    float InverterCost = _inverterSet[inverter][5];

    Ecorrected = Econsumption / (nb*nc*ni);

    Pminpanels = 1.25 * Ecorrected / Insol;

    NPmin = ((Pminpanels -1)/ Pmref)+1;

    NPP = 2;
    if ((NPmin % 2) == 0) NPS = NPmin/2; //even number
    else NPS = (NPmin + 1)/2; //odd number

    NTP = NPS * NPP;

    ItotalPVpanels = NPP * Imref;
    VtotalPVpanels = NPS * Vmref;

    if(!(IC >= ItotalPVpanels && VCmax >= VtotalPVpanels))
        return MAX_INTEGER;
    // __VERIFIER_assume((IC >= ItotalPVpanels));   
    // __VERIFIER_assume((VCmax >= VtotalPVpanels));

    DODmax = (100-SOClimit)*2;
    autonomy = 2; // (48/24)
    Eb = autonomy * Ecorrected*2;
    DODdaycalc = Ecorrected * 100/Eb;
    IminDCbus = Eb/(float)Vsystem;

    NBS = Vsystem/Vbat; //fixed value 
    NBP = ((IminDCbus -1)/ capacity)+1; //calculando e arredondando
    NBtotal = NBS * NBP;

    if(!((VCmax* IC * nc) >= PACref))
        return MAX_INTEGER;

    if(!(VinDC >= Vsystem ))
        return MAX_INTEGER;
        
    if(!(VoutAC >= (VAC-VAC*15/100)))
        return MAX_INTEGER;
    
    if(!((Phouse <= PACref) && (Psurge <= MAXACref)))
        return MAX_INTEGER;
    
    Fobj= NTP*PanelCost + NBtotal*BatteryCost + ControllerCost + InverterCost;
    
    LCC = Fobj + (Fobj*0.05 + 20*289.64);

    return Fobj;
}

int main() 
{ 
  unsigned int Apos = 0;
  unsigned int Bpos = 0;
  unsigned int Cpos = 0;
  unsigned int Dpos = 0;

  int Alim = GET_MATRIX_SIZE(_panelSet);
  int Blim = GET_MATRIX_SIZE(_batterySet);
  int Clim = GET_MATRIX_SIZE(_controllerSet);
  int Dlim = GET_MATRIX_SIZE(_inverterSet);

  int sequence = Alim * Blim * Clim * Dlim;

  int crA = Alim;
  int crB = Blim;
  int crC = Clim;
  int crD = Dlim;

  for (int i = 0; i < sequence; i++)
  {
    Apos = nondet_uint();
    __VERIFIER_assume(Apos >= 0 && Apos != (int)crA && Apos < Alim);

    if(Apos + 1 == Alim)
    {
      Bpos = nondet_uint();
      __VERIFIER_assume(Bpos >= 0 && Bpos != (int)crB && Bpos < Blim);

        if(Bpos + 1 == Blim)
        {
          Cpos = nondet_uint();
          __VERIFIER_assume(Cpos >= 0 && Cpos != (int)crC && Cpos < Clim);

            if(Cpos + 1 == Clim)
            {
              Dpos = nondet_uint();
              __VERIFIER_assume(Dpos >= 0 && Dpos != (int)crD && Dpos < Dlim);
            }
        }
    }

    crA = Apos; crB = Bpos; crC = Cpos; crD = Dpos;

    int cost = getLowestCost(crA, crB, crC, crD);

    if(cost < LOWEST)
    {
        LOWEST = cost;
        int result = nondet_uint();
        __VERIFIER_assume(result == LOWEST);
    }
  }
  
  __VERIFIER_error();

   return 0;
 }

