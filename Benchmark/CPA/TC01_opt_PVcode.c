/*
 ============================================================================
 Name        : opt_PVcode_rev0925_CASEx
 Author      : Alessandro Trindade
 Version     : rev0923 - Sep 2020: 70 equipment, lowerbound defined by SW, better HintCost
 Description : stand-alone PV sizing optimization (Universal: CBMC, ESBMC, UAutomizer and CPChecker)
 //assume (exp);  MUST BE REPLACE BY:   if (!expr) { __VERIFIER_error(); }
 ============================================================================*/

//case studies
//case1       
int Phouse = 342, Psurge = 342, Econsumption = 3900, VAC = 127;
//case2       int Phouse = 814, Psurge = 980, Econsumption = 4800, VAC = 127;
//case3       int Phouse = 815, Psurge = 980, Econsumption = 4880, VAC = 127;
//case4       int Phouse = 253, Psurge = 722, Econsumption = 3600, VAC = 127;
//case5       int Phouse = 263, Psurge = 732, Econsumption = 2500, VAC = 127;
//case6       int Phouse = 322, Psurge = 896, Econsumption = 4300, VAC = 127;
//case7       int Phouse = 1586, Psurge = 2900, Econsumption = 14400, VAC = 220;

//data from Manaus
int minSolarIrrad [24] = {0,0,0,0,0,0,25,135,274,422,509,537,503,505,430,281,80,10,0,0,0,0,0,0};
int maxSolarIrrad [24] = {0,0,0,0,0,4,87,295,487,648,751,852,817,742,610,418,128,51,0,0,0,0,0,0};
int minTemp [12] = {23,23,23,23,23,23,23,23,23,24,24,23};
int maxTemp [12] = {30,30,30,30,30,30,30,31,32,32,31,30};
float Insol = 3.89; //(kWh/m2/day CRESESB corrigido)
int Gref = 1000; //reference irradiance is 1000 W/mB2
int G = 800;
float Tref = 298.15; //reference temperature is 25oC or 298.15K

//must define
int MaxCost=10000; //10 million maximum cost just to control the loop of main function
int Vsystem = 24;  //12V, 24V, 36V or 48V: DC Bus voltage definition
int autonomy = 48; //autonomy in hours
int SOClimit = 75, SOCabsorption = 95, SOCfull = 100, Vbat = 12;

//Quantities of each equipment at the database below
unsigned char PanelQuant = 17, BatteryQuant=17, ControllerQuant=19,InverterQuant=17;

// panel data        {area, efficiency, num cells, NOCT, mii, miv, Iscref, Vocref, Pmref, Imref, Vmref, VmpNOCT, cost} 
// Canadian (CS6U-315, 320, 325, 330P), Kyocera (KU340-8BCA, KC200GT), Sinosola (SA275-60P, SA360-72M), Risen (RSM36-6-150P), Yingli (YL150P-17b), Yingli (YL330P-35B), OSDA (ODA330-36-P), OSDA (ODA380-36-M), Ulica UL-395M-144, Canadian CS3U-355P
// 425W Canadian HiKu, LONGI 144 CELLS 435W HALF
float PanelData[17][13] = {{1.94432, 0.1620, 72, 45, 0.00053, -0.0031, 9.18, 45.1, 315, 8.16, 36.6, 33.4, 268.40},
                          {1.94432, 0.1646, 72, 45, 0.00053, -0.0031, 9.26, 45.3, 320, 8.69, 36.8, 33.6, 190.00},
                          {1.94432, 0.1672, 72, 45, 0.00053, -0.0031, 9.34, 45.5, 325, 8.78, 37.0, 33.7, 216.67},
			  {1.94432, 0.1697, 72, 45, 0.00053, -0.0031, 9.45, 45.6, 330, 8.88, 37.2, 33.9, 170.30},
			  {2.19384, 0.1515, 80, 47, 0.00020, -0.0048, 8.86, 50.8, 340, 8.26, 41.2, 37.0, 214.20},
			  {1.41075, 0.1600, 54, 47, 0.0000318, -0.00123, 8.21, 32.9, 200, 7.61, 32.9, 23.2, 300.00},
			  {1.62688, 0.1690, 60, 47, 0.00039, -0.00307, 9.44, 38.84, 275, 8.81, 31.22, 26.72, 150.00},
			  {1.94035, 0.1855, 72, 45, 0.00039, -0.00307, 9.73, 47.60, 360, 9.33, 38.59, 34.96, 237.24},
			  {1.00640, 0.1515, 36, 45, 0.00033, -0.0039, 8.81, 22.30, 150, 8.20, 18.30, 14.40, 94.75},
			  {0.99960, 0.1500, 36, 46, 0.00060, -0.0037, 8.61, 22.90, 150, 8.12, 18.50, 14.61, 108.50},
		          {1.97904, 0.1700, 72, 45, 0.0005, -0.003, 9.33, 45.6, 330, 8.85, 37.3, 34.4, 118},
		          {1.94432, 0.1697, 72, 45, 0.0006, -0.003, 9.57, 44.72, 330, 8.86, 37.26, 34.28, 131.25},
			  {1.94432, 0.1926, 72, 45, 0.00048, -0.004, 10.67, 47.80, 380, 9.74, 39.02, 36.48, 155.52},
			  {1.984, 0.1991, 144, 45, 0.00049, -0.0029, 10.31, 49.10, 395, 9.83, 40.2, 37.5, 178.03},
		          {1.984, 0.1789, 144, 45, 0.0005, -0.0029, 9.59, 46.8, 355, 9.02, 39.4, 36.60, 144.26},
			  {2.20918, 0.1924, 144, 42, 0.0005, -0.0029, 11.29, 48.00, 425, 10.71, 39.70, 36.00, 187.41},
			  {2.17357, 0.1960, 144, 45, 0.00048, -0.0027, 11.39, 48.7, 435, 10.64, 40.9, 36.4, 225.11}};

// battery data  	{efficiency, voltage, capacityC20, Vbulk, Vfloat, cost} 
// moura (12MF80, 12MF105, 12MF150, 12MF175, 12MF220) , heliar (DF1000, DF1500, DF2500, DF3000, DF4001)
// Heliar DF4100, Fulguris FGCL220, Moura 12MS234, Fulguris OPzS 250Ah-5.000 ciclos, Fulguris OPzS 300Ah-5.000 ciclos
// Freedom Df500, Freedom Df700
float BatteryData [17][6] = {{0.85, 12, 80, 14.4, 13.8, 131.00},
			    {0.85, 12, 105, 14.4, 13.8, 150.00},
			    {0.85, 12, 150, 14.4, 13.8, 324.75},
			    {0.85, 12, 175, 14.4, 13.8, 299.75},
                            {0.85, 12, 220, 14.4, 13.8, 374.75},
			    {0.85, 12, 60, 14.4, 13.8, 114.75},
			    {0.85, 12, 80, 14.4, 13.2, 138.00},
			    {0.85, 12, 150, 14.4, 13.2, 275.00},
			    {0.85, 12, 170, 14.4, 13.2, 299.01},
			    {0.85, 12, 220, 14.4, 13.2, 330.73},
			    {0.85, 12, 220, 14.4, 13.2, 279.33},
			    {0.85, 12, 220, 14.14, 13.2, 243.69},
			    {0.85, 12, 220, 14.4, 13.2, 290.59},
			    {0.85, 12, 250, 14.4, 13.2, 1836.55},
			    {0.85, 12, 300, 14.4, 13.2, 1930.34},
			    {0.85, 12, 36, 14.4, 13.2, 77.00},
			    {0.85, 12, 45, 14.4, 13.2, 85.00}};

// controller data  	{efficiency, nominal current, voltage  output, Vmpptmin=vbat+1, Vcmax, cost}
// victron MPPT (35-145, 15-75, 15-100, 50-100), Epever (TRIRON 2210N 20A 12/24V, TRIRON 3210N 30A 12/24V, TRIRON 4210N 40A 12/24V), Epsolar (Tracer-2210RN 20A 12/24V, New Tracer-3215BN 30A 12/24V), Schneider Electric (XW-MPPT 60/150)
// Epever Tracer 10415AN, Epever Tracer 4215BN, Epever Tracer 54150AN, Epever Tracer6415AN, Bluesolar MPPT 150V 45A MC4
// Sandi Electric SDC400V-100A, SDC384V-250A
float ControllerData [19][6] = {{0.98, 35, 24, 13, 145, 294.95},
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
			       {0.96, 60, 60, 13, 140, 1072.50},
			       {0.98, 100, 24, 14, 150, 750.18},
			       {0.98, 40, 24, 13, 150, 281.39},
			       {0.98, 50, 24, 13, 150, 356.43},
			       {0.98, 60, 24, 13, 150, 530.70},
			       {0.98, 45, 24, 13, 150, 506.50},
			       {0.95, 100, 48, 13, 400, 1800},
			       {0.95, 250, 48, 13, 384, 2300}};

// inverter data  	{efficiency, VinDC, VoutAC, PACref, MAXACref, cost}
// victron (Phoenix 24-800,Phoenix 48-1200), Epever (IP1500-11,  IP350-11, IP500-11), Epsolar (SHI600-12, STI1000-24-120), Xantrex (SW 1000, HFS 1055 1000W, HFS 1800W)
// Epever SHI3000-22-3000W, Epever IPower IP1500-12, Epever SHI2000-22 - 2000W, Epever IPower IP2000-22, Epever IPower IP1500-11
// Growatt Spf10kthvm, Growatt hibrido 3kW
float InverterData [17][6] =   {{0.93, 48, 110, 700, 1600, 400.00},
			       {0.93, 48, 110, 1200, 2400, 750.00},
			       {0.93, 24, 120, 1200, 2400, 450.00},
			       {0.91, 24, 120, 280, 750, 149.75},
			       {0.91, 24, 120, 400, 1000, 187.25},
			       {0.93, 12, 220, 600, 1350, 342.25},
			       {0.93, 24, 120, 800, 1200, 500.00},
			       {0.90, 12, 120, 900, 2000, 649.75},
			       {0.82, 12, 120, 1000, 2000, 1122.25},
			       {0.90, 24, 125, 1800, 2900, 1669.75},
			       {0.93, 24, 110, 3000, 6900, 1144.14},
			       {0.93, 24, 220, 1200, 2400, 212.00},
			       {0.95, 24, 220, 2000, 4600, 775.00},
				{0.95, 24, 220, 1600, 3200, 544.03},
				{0.93, 24, 110, 1200, 2400, 506.50},
				{0.88, 48, 220, 10000, 30000, 2270.64},
				{0.93, 48, 220, 3000, 6000, 1125.59}};

//global variables
float SOC = 100; //battery is charged when starts the verification

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume(int expression);
unsigned int nondet_uint();
unsigned char nondet_uchar();


int FHintCost(void){
	int lowervalue, cost=0, cont;
	lowervalue=(int)PanelData[0][12];
	for (cont=1; cont <= 16; cont++) {
		if ((int)PanelData[cont][12] < lowervalue) lowervalue=(int)PanelData[cont][12];
	}
	cost = 2*lowervalue;
	lowervalue=(int)BatteryData[0][5];
	for (cont=1; cont <= 16; cont++) {
		if ((int)BatteryData[cont][5] < lowervalue) lowervalue=(int)BatteryData[cont][5];
	}
	cost = cost+2*lowervalue;
	lowervalue=(int)ControllerData[0][5];
	for (cont=1; cont <= 18; cont++) {
		if ((int)ControllerData[cont][5] < lowervalue) lowervalue=(int)ControllerData[cont][5];
	}
	cost = cost+lowervalue;
	lowervalue=(int)InverterData[0][5];
	for (cont=1; cont <= 16; cont++) {
		if ((int)InverterData[cont][5] < lowervalue) lowervalue=(int)InverterData[cont][5];
	}
	cost = cost+lowervalue;
	cost = cost + cost*0.05 + 20*289.64;
	return(cost);  
}

/*--------------------------------
            Auxiliary function
----------------------------------*/
int Faux (int cost){
	int NTP, NPP, NPS, NBtotal, NBS, NBP, NPPmin, ICmin;
	int arrang, NPmin;
	float Ecorrected, Ep, NTPmin, NPSmin1, NPSmin2, Cbank, Iscamb, NBSmin, NBPmin, Fobj;
float Pminpanels, ItotalPVpanels, VtotalPVpanels, Eb, DODdaycalc, IminDCbus, equipcost, DODmax;
	unsigned char PanelChoice, BatteryChoice, ControllerChoice, InverterChoice;

	PanelChoice = nondet_uchar();
        __VERIFIER_assume(PanelChoice <= (PanelQuant-1));
//	__VERIFIER_assume((PanelChoice >= 0) && (PanelChoice <= PanelQuant));

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
	int NOCT = (int)PanelData[PanelChoice][3]; //Nominal Operating Cell Temperature=45B0C +-2 at G=800 W/m2, light spectrum AM 1.5G, windspeed=1m/s, air temp at 20B0C
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

////definir arranjos de painC)is solares para tentativa de projeto C3timo NPS, NPP

//arrang = nondet_uint();

//	NPP = 1; //arrangement for series connection
//	NPS = ((Pminpanels-1) / Pmref)+1;  //arrangement for series connection
NPmin = ((Pminpanels -1)/ Pmref)+1;
//begin panel arrangement definition
//if (NPmin >= 3) {
//	arrang = nondet_uint();
//	__VERIFIER_assume( (arrang >= 1) && (arrang <= 2) );
//	if (arrang == 1) { //series arrangement of PV array
//		NPP = 1;
//		NPS = NPmin;
//	}
//	if (arrang == 2) { //parallel arrangement of PV array
		NPP = 2;
		if ((NPmin % 2) == 0) NPS = NPmin/2; //even number
		else NPS = (NPmin + 1)/2; //odd number
//	}	
//} 
//else { //1 or two panels in series
//NPP = 1;
//NPS = NPmin;
//}

NTP = NPS * NPP;

//checking power from PV panels
/////////////////////////////////////__VERIFIER_assume  (Pminpanels <= (NPS*NPP*Pmref));

//checking voltage and current from the PV panel and the controller
ItotalPVpanels = NPP * Imref;
VtotalPVpanels = NPS * Vmref;
__VERIFIER_assume ( (IC >= ItotalPVpanels) && (VCmax >= VtotalPVpanels) );

DODmax = (100-SOClimit)*2;
autonomy = 2; // (48/24)
//checking batteries
//Eb = (autonomy/24) * Ecorrected/((float)(DODmax/100));
Eb = autonomy * Ecorrected*2;
//Eb = autonomy * Ecorrected*100/(24*(float)((100-SOClimit)*2));

DODdaycalc = Ecorrected * 100/Eb;

//check DC bus current
IminDCbus = Eb/(float)Vsystem;

///////arranjo baterias
NBS = Vsystem/Vbat; //fixed value 
NBP = ((IminDCbus -1)/ capacity)+1; //calculando e arredondando
NBtotal = NBS * NBP;

//////////////////////////////////////__VERIFIER_assume (IminDCbus <= (NBP * capacity));

//controller vs inverter check
__VERIFIER_assume ((VCmax* IC * nc) >= PACref);

	
//ok daqui pra baixo
	//controller sizing and check, considering just one controller
//__VERIFIER_assume( (VC == Vsystem) );
//Iscamb = G*Iscref*(1+mii*(NOCT-25))/Gref; //from each PV panel
//ICmin = ((Iscamb - 1) * NPP)+1;
//	__VERIFIER_assume( (IC >= ICmin) );

	//inverter sizing and check
//	__VERIFIER_assume ( ( VinDC >= Vsystem ) ); //if inverter supports 48V, then it supports 12 and 24 as well

	__VERIFIER_assume ( ( VinDC >= Vsystem ) && (VoutAC >= (VAC-VAC*15/100)) && (VoutAC <= (VAC+VAC*15/100)) ); 
	//Inverter output mus be +- 15% of the expected house's VAC

	__VERIFIER_assume ( (Phouse <= PACref) && (Psurge <= MAXACref) ); 
	//Power supported by the inverter must be greater than House's demand
	// and the Peak power from inverter must support the Peak from the house

	// Function objective: minimum acquisition cost
	equipcost = NTP*PanelCost + NBtotal*BatteryCost + ControllerCost + InverterCost;
	Fobj= equipcost + equipcost*0.05 + 20*289.64; //cost = equipment + 5% of installation + 3*batrep + O&M cost 

	//minimize cost of the solution, considering all the equipment that can be used and was declared at the code
	if (!(Fobj > (float)cost)) { __VERIFIER_error(); }
	return 0;
}

/* ----------- MAIN FUNCTION --------- */
int main() {
	int HintCost, step=1;
	HintCost = FHintCost();

	for (; HintCost <= MaxCost; HintCost=HintCost+step){
		Faux(HintCost);
	}
	return 0;
}
