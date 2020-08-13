#include <stdio.h>
#define INT_MAX 2147483647

unsigned char PanelChoice, BatteryChoice, ControllerChoice, InverterChoice;

//Quantities of each equipment at the database below
unsigned char PanelQuant = 5, BatteryQuant=5, ControllerQuant=5,InverterQuant=5;
int Phouse = 915, Psurge = 980, Econsumption = 4880;
float Insol = 4.92; //(kWh/m2/day CRESESB 2016)
int Vsystem = 24;  //12V, 24V, 36V or 48V: DC Bus voltage definition
int autonomy = 48; //autonomy in hours
int SOClimit = 75;
int VAC = 127;
float LCC;

float PanelData[5][13] = {{1.94432, 0.1620, 72, 45, 0.00053, -0.0031, 9.18, 45.1, 315, 8.16, 36.6, 33.4, 268.40},
                          {1.94432, 0.1646, 72, 45, 0.00053, -0.0031, 9.26, 45.3, 320, 8.69, 36.8, 33.6, 190.00},
                          {1.94432, 0.1672, 72, 45, 0.00053, -0.0031, 9.34, 45.5, 325, 8.78, 37.0, 33.7, 216.67},
                          {1.94432, 0.1697, 72, 45, 0.00053, -0.0031, 9.45, 45.6, 330, 8.88, 37.2, 33.9, 170.30},
                          {0.99960, 0.1500, 36, 46, 0.00060, -0.0037, 8.61, 22.90, 150, 8.12, 18.50, 14.61, 108.50}};

float BatteryData[5][6] = {{0.85, 12, 80, 14.4, 13.8, 131.00},
                           {0.85, 12, 105, 14.4, 13.8, 150.00},
                           {0.85, 12, 150, 14.4, 13.8, 324.75},
                           {0.85, 12, 175, 14.4, 13.8, 299.75},
                           {0.85, 12, 220, 14.4, 13.2, 330.73}};

float ControllerData[5][6] = {{0.98, 35, 24, 13, 145, 294.95},
                              {0.98, 15, 24, 13, 75, 88.40},
                              {0.98, 50, 48, 13, 150, 347.82},
                              {0.98, 60, 48, 13, 150, 388.91},
                              {0.96, 60, 60, 13, 140, 1072.50}};

float InverterData[5][6] = {{0.93, 48, 110, 700, 1600, 400.00},
                            {0.93, 48, 110, 1200, 2400, 750.00},
                            {0.91, 24, 120, 280, 750, 149.75},
                            {0.91, 24, 120, 400, 1000, 187.25},
                            {0.90, 24, 125, 1800, 2900, 1669.75}};

int getLowestCost(int num_rows, int num_cols, float arr[num_rows][num_cols])
{
    return 461;
    // int totalCost = INT_MAX;

    // int cost_column = num_cols - 1;

    // for (int i = 0; i < num_rows; i++)
    // {
    //     int v = arr[i][cost_column];

    //     if (v < totalCost)
    //         totalCost = v;
    // }

    // if (totalCost == INT_MAX)
    //     return -1;
    // else
    //     return totalCost;
}

int getTotalCost()
{
    int cost_panel = getLowestCost(sizeof(PanelData) / sizeof(PanelData[0]), sizeof(PanelData[0]) / sizeof(PanelData[0][0]), PanelData);

    int cost_baterry = getLowestCost(sizeof(BatteryData) / sizeof(BatteryData[0]), sizeof(BatteryData[0]) / sizeof(BatteryData[0][0]), BatteryData);

    int cost_controller = getLowestCost(sizeof(ControllerData) / sizeof(ControllerData[0]), sizeof(ControllerData[0]) / sizeof(ControllerData[0][0]), ControllerData);

    int cost_inverter = getLowestCost(sizeof(InverterData) / sizeof(InverterData[0]), sizeof(InverterData[0]) / sizeof(InverterData[0][0]), InverterData);

    int cost_total = cost_panel + cost_baterry + cost_controller + cost_inverter;

    return cost_total;
}

int optimizeCost(int cost)
{
    int NTP, NPP, NPS, NBtotal, NBS, NBP, NPPmin, ICmin;
    int arrang, NPmin;
    float Ecorrected, Ep, NTPmin, NPSmin1, NPSmin2, Cbank, Iscamb, NBSmin, NBPmin, Fobj;
    float Pminpanels, ItotalPVpanels, VtotalPVpanels, Eb, DODdaycalc, IminDCbus, equipcost, DODmax;

	PanelChoice = nondet_uchar();
    __VERIFIER_assume(PanelChoice <= (PanelQuant-1));

	BatteryChoice = nondet_uchar();
    __VERIFIER_assume(BatteryChoice <= (BatteryQuant-1));

	ControllerChoice = nondet_uchar();
	__VERIFIER_assume(ControllerChoice <= (ControllerQuant-1));

	InverterChoice = nondet_uchar();
	__VERIFIER_assume(InverterChoice <= (InverterQuant-1));

	// information from the PV Panel
	float Ap = PanelData[PanelChoice][0];
	float np = PanelData[PanelChoice][1];
	int N = (int)PanelData[PanelChoice][2];    //N=number of series-connected cells
	int NOCT = (int)PanelData[PanelChoice][3]; //Nominal Operating Cell Temperature=45°C +-2 at G=800 W/m2, light spectrum AM 1.5G, windspeed=1m/s, air temp at 20°C
	float mii = PanelData[PanelChoice][4]; //short-circuit current temperature coefficient (A/K)
	float miv = PanelData[PanelChoice][5]; //open-circuit voltage temperature coefficient (V/K)
	float Iscref = PanelData[PanelChoice][6];
	float Vocref = PanelData[PanelChoice][7];
	float Pmref = PanelData[PanelChoice][8];
	float Imref = PanelData[PanelChoice][9];
	float Vmref = PanelData[PanelChoice][10];
	float VmpNOCT = PanelData[PanelChoice][11];
	float PanelCost = PanelData[PanelChoice][12];

	//battery information
	float nb = BatteryData [BatteryChoice][0];
	int Vbat = (int)BatteryData [BatteryChoice][1];
	int capacity = (int)BatteryData [BatteryChoice][2];
	float Vbulk = BatteryData [BatteryChoice][3]; //(14.40*NBS);
	float Vfloat = BatteryData [BatteryChoice][4]; //(13.20*NBS);
	float BatteryCost = BatteryData [BatteryChoice][5];

	// charge controller
	float nc = ControllerData[ControllerChoice][0];
	int IC = (int)ControllerData[ControllerChoice][1];
	int VC = (int)ControllerData[ControllerChoice][2];
	int Vmpptmin = (int)ControllerData[ControllerChoice][3];
	float VCmax = ControllerData[ControllerChoice][4];
	float ControllerCost = ControllerData[ControllerChoice][5];

	//inverter
	float ni = InverterData[InverterChoice][0];
	int VinDC = (int)InverterData[InverterChoice][1];
	int VoutAC = (int)InverterData[InverterChoice][2];
	int PACref = (int)InverterData[InverterChoice][3];
	int MAXACref = (int)InverterData[InverterChoice][4];
	float InverterCost = InverterData[InverterChoice][5];

	//Econsumption = energy consumed in one day from the house
	Ecorrected = Econsumption / (nb*nc*ni);

	Pminpanels = 1.25 * Ecorrected / Insol;
	NPmin = ((Pminpanels -1)/ Pmref)+1;
	NPP = 2;
	if ((NPmin % 2) == 0) NPS = NPmin/2; //even number
	else NPS = (NPmin + 1)/2; //odd number
	NTP = NPS * NPP;

    //checking voltage and current from the PV panel and the controller
    ItotalPVpanels = NPP * Imref;
    __VERIFIER_assume ( (IC >= ItotalPVpanels) );

    VtotalPVpanels = NPS * Vmref;
    __VERIFIER_assume ( (VCmax >= VtotalPVpanels) );

    DODmax = (100-SOClimit)*2;
    autonomy = 2; // (48/24)
    Eb = autonomy * Ecorrected*100/DODmax;

    DODdaycalc = Ecorrected * 100/Eb;

    //check DC bus current
    IminDCbus = Eb/(float)Vsystem;

    ///////arranjo baterias
    NBS = Vsystem/Vbat; //fixed value 
    NBP = ((IminDCbus -1)/ capacity)+1; //calculando e arredondando
    NBtotal = NBS * NBP;

    //controller vs inverter check
    __VERIFIER_assume ((VCmax* IC * nc) >= PACref);

	//inverter sizing and check
	__VERIFIER_assume ( ( VinDC >= Vsystem ) ); //if inverter supports 48V, then it supports 12 and 24 as well

	__VERIFIER_assume ( (VoutAC >= (VAC-VAC*15/100)) && (VoutAC <= (VAC+VAC*15/100)) ); 
	//Inverter output mus be +- 15% of the expected house's VAC

	__VERIFIER_assume ( (Phouse <= PACref) && (Psurge <= MAXACref) ); 
	//Power supported by the inverter must be greater than House's demand
	// and the Peak power from inverter must support the Peak from the house

	// Function objective: minimum acquisition cost
	Fobj= NTP*PanelCost + NBtotal*BatteryCost + ControllerCost + InverterCost;
	LCC = Fobj+Fobj*0.05+20*289.64; //cost = equipment + 5% of installation + 3*batrep + O&M cost [out: 3*(NBtotal*BatteryCost)+]
	//minimize cost of the solution, considering all the equipment that can be used and was declared at the code
	
    if (!(Fobj > (float)cost)) { __VERIFIER_error(); }

	return 0;
}

int main()
{
    // int total = getTotalCost();

    for (int i = 461; i < 461 * 5; i++)
    {
        optimizeCost(i);
    }    

    return 0;
}