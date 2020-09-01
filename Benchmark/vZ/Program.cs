using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using Microsoft.Z3;

namespace PVS
{
    class Program
    {
        //{area, efficiency, num cells, NOCT, mii, miv, Iscref, Vocref, Pmref, Imref, Vmref, VmpNOCT, cost}
        public static float[,] PanelData = {
            {1.94432f, 0.1620f, 72f, 45f, 0.00053f, -0.0031f, 9.18f, 45.1f, 315f, 8.16f, 36.6f, 33.4f, 268.40f},
            {1.94432f, 0.1646f, 72f, 45f, 0.00053f, -0.0031f, 9.26f, 45.3f, 320f, 8.69f, 36.8f, 33.6f, 190.00f},
            {1.94432f, 0.1672f, 72f, 45f, 0.00053f, -0.0031f, 9.34f, 45.5f, 325f, 8.78f, 37.0f, 33.7f, 216.67f},
            {1.94432f, 0.1697f, 72f, 45f, 0.00053f, -0.0031f, 9.45f, 45.6f, 330f, 8.88f, 37.2f, 33.9f, 170.30f},
            {0.99960f, 0.1500f, 36f, 46f, 0.00060f, -0.0037f, 8.61f, 22.90f, 150f, 8.12f, 18.50f, 14.61f, 108.50f}};

        //{efficiency, voltage, capacityC20, Vbulk, Vfloat, cost} 
        public static float[,] BatteryData = {
            {0.85f, 12f, 80f,  14.4f, 13.8f, 131.00f},
            {0.85f, 12f, 105f, 14.4f, 13.8f, 150.00f},
            {0.85f, 12f, 150f, 14.4f, 13.8f, 324.75f},
            {0.85f, 12f, 175f, 14.4f, 13.8f, 299.75f},
            {0.85f, 12f, 220f, 14.4f, 13.2f, 330.73f}};

        //{efficiency, nominal current, voltage  output, Vmpptmin=vbat+1, Vcmax, cost}
        public static float[,] ControllerData = {
            {0.98f, 35f, 24f, 13f, 145f, 294.95f},
            {0.98f, 15f, 24f, 13f,  75f, 88.40f},
            {0.98f, 50f, 48f, 13f, 150f, 347.82f},
            {0.98f, 60f, 48f, 13f, 150f, 388.91f},
            {0.96f, 60f, 60f, 13f, 140f, 1072.50f}};

        //efficiency, VinDC, VoutAC, PACref, MAXACref, cost
        public static float[,] InverterData = {
            {0.93f, 48f, 110f, 700f, 1600f, 400.00f},
            {0.93f, 48f, 110f, 1200f, 2400f, 750.00f},
            {0.91f, 24f, 120f, 280f, 750f, 149.75f},
            {0.91f, 24f, 120f, 400f, 1000f, 187.25f},
            {0.90f, 24f, 125f, 1800f, 2900f, 1669.75f}};

        //data from the house
        static int Phouse = 263, Psurge = 732, Econsumption = 2500;
        static float Insol = 3.80f; //(kWh/m2/day CRESESB 2016)
        static int SOClimit = 75;
        static int autonomy = 48; //autonomy in hours
        static int Vsystem = 24;
        static int VAC = 127;
        static int Vbat = 12;
        static void Main(string[] args)
        {
            Microsoft.Z3.Global.ToggleWarningMessages(true);
            Log.Open("test.log");

            using (Context ctx = new Context())
            {
                int min = 2000;
                int max = 3000;

                for (int i = min; i < max; i++)
                    if (Faux(i, ctx))
                        break;

                ctx.Dispose();
            }

            Console.ReadLine();
        }

        private static bool Faux(int cost, Context ctx)
        {
            Console.WriteLine("");

            var opt = ctx.MkOptimize();

            var pccv = ctx.MkIntConst("panelChoice");
            var panelCostHigh = ctx.MkLt(pccv, ctx.MkInt(GetArraySize(PanelData)));
            var panelLow = ctx.MkGe(ctx.MkIntConst("panelChoice"), ctx.MkInt(0));
            opt.Add(panelCostHigh); opt.Add(panelLow);
            opt.MkMaximize(pccv);

            var bttCostHigh = ctx.MkLt(ctx.MkIntConst("batteryChoice"), ctx.MkInt(GetArraySize(BatteryData)));
            var bttLow = ctx.MkGe(ctx.MkIntConst("batteryChoice"), ctx.MkInt(0));
            opt.Add(bttCostHigh); opt.Add(bttLow);

            var cttCostHigh = ctx.MkLt(ctx.MkIntConst("controllerChoice"), ctx.MkInt(GetArraySize(ControllerData)));
            var cttLow = ctx.MkGe(ctx.MkIntConst("controllerChoice"), ctx.MkInt(0));
            opt.Add(cttCostHigh); opt.Add(cttLow);

            var invCostHigh = ctx.MkLt(ctx.MkIntConst("inverterChoice"), ctx.MkInt(GetArraySize(InverterData)));
            var invLow = ctx.MkGe(ctx.MkIntConst("inverterChoice"), ctx.MkInt(0));
            opt.Add(invCostHigh); opt.Add(invLow);

            opt.Add(ctx.MkGe(ctx.MkIntConst("cost"), ctx.MkInt(cost)));

            var firstVerification = opt.Check();

            if (firstVerification == Status.SATISFIABLE)
            {
                var s32b = ctx.MkFPSort32();

                int NTP, NPP, NPS, NBtotal, NBS, NBP, NPmin;
                float Ecorrected, Fobj, Pminpanels, ItotalPVpanels, VtotalPVpanels, Eb, DODdaycalc, IminDCbus, DODmax;

                var btt = ((IntNum)opt.Model.ConstInterp(opt.Model.ConstDecls
                          .FirstOrDefault(x => x.Name.ToString() == "batteryChoice"))).Int;

                var pcc = ((IntNum)opt.Model.ConstInterp(opt.Model.ConstDecls
                            .FirstOrDefault(x => x.Name.ToString() == "panelChoice"))).Int;

                var ctt = ((IntNum)opt.Model.ConstInterp(opt.Model.ConstDecls
                            .FirstOrDefault(x => x.Name.ToString() == "controllerChoice"))).Int;

                var invc = ((IntNum)opt.Model.ConstInterp(opt.Model.ConstDecls
                           .FirstOrDefault(x => x.Name.ToString() == "inverterChoice"))).Int;

                opt.Check();
                Console.WriteLine(opt.Model);

                #region Values
                float nb = BatteryData[btt, 0];
                int capacity = (int)BatteryData[btt, 2];
                float BatteryCost = BatteryData[btt, 5];

                float ControllerCost = ControllerData[ctt, 5];
                float VCmax = ControllerData[ctt, 4];
                int IC = (int)ControllerData[ctt, 1];
                float nc = ControllerData[ctt, 0];

                float InverterCost = InverterData[invc, 5];
                int PACref = (int)InverterData[invc, 3];
                int VinDC = (int)InverterData[invc, 1];
                int VoutAC = (int)InverterData[invc, 2];
                int MAXACref = (int)InverterData[invc, 4];
                float ni = InverterData[invc, 0];

                float Pmref = PanelData[pcc, 8];
                float Imref = PanelData[pcc, 9];
                float Vmref = PanelData[pcc, 10];
                float PanelCost = PanelData[pcc, 12];
                #endregion

                Ecorrected = Econsumption / (nb * nc * ni);
                Pminpanels = (float)(1.25 * Ecorrected / Insol);
                NPmin = (int)((Pminpanels - 1) / Pmref) + 1;

                NPP = 2;
                if ((NPmin % 2) == 0)
                    NPS = NPmin / 2; //even number
                else
                    NPS = (NPmin + 1) / 2; //odd number

                NTP = NPS * NPP;
                ItotalPVpanels = NPP * Imref;

                //IC >= ItotalPVpanels
                opt.Assert(ctx.MkFPGEq(ctx.MkFP(IC, s32b), ctx.MkFP(ItotalPVpanels, s32b)));
                if (!ValidateStep(opt)) return false;

                VtotalPVpanels = NPS * Vmref;

                //VCmax >= VtotalPVpanels
                var vcmax = ctx.MkFP(VCmax, ctx.MkFPSort32());
                var vtotalPV = ctx.MkFP(VtotalPVpanels, ctx.MkFPSort32());
                opt.Assert(ctx.MkFPGEq(vcmax, vtotalPV));
                if (!ValidateStep(opt)) return false;

                DODmax = (100 - SOClimit) * 2;
                autonomy = 2;
                Eb = autonomy * Ecorrected * 2;
                DODdaycalc = Ecorrected * 100 / Eb;
                IminDCbus = Eb / (float)Vsystem;
                NBS = Vsystem / Vbat; //fixed value 
                NBP = (int)(((IminDCbus - 1) / capacity) + 1); //calculando e arredondando
                NBtotal = NBS * NBP;

                //controller vs inverter check
                var cic = VCmax * IC * nc;
                opt.Assert(ctx.MkFPGEq(ctx.MkFP(cic, s32b), ctx.MkFP(PACref, s32b)));
                if (!ValidateStep(opt)) return false;

                opt.Assert(ctx.MkFPGEq(ctx.MkFP(VinDC, s32b), ctx.MkFP(Vsystem, s32b)));
                if (!ValidateStep(opt)) return false;

                var minus = (VAC - VAC * 15 / 100);
                var plus = (VAC + VAC * 15 / 100);

                //(VoutAC >= (VAC - VAC * 15 / 100))
                opt.Assert(ctx.MkFPGEq(ctx.MkFP(VoutAC, s32b), ctx.MkFP(minus, s32b)));
                if (!ValidateStep(opt)) return false;

                //(VoutAC <= (VAC + VAC * 15 / 100))
                opt.Assert(ctx.MkFPLEq(ctx.MkFP(VoutAC, s32b), ctx.MkFP(plus, s32b)));
                if (!ValidateStep(opt)) return false;

                //(Phouse <= PACref)
                var _phouse = ctx.MkInt(Phouse);
                var _pacref = ctx.MkInt(PACref);
                var _psurge = ctx.MkInt(Psurge);
                var _maxacref = ctx.MkInt(MAXACref);

                var lefteq = (ctx.MkLe(_phouse, _pacref));
                var righteq = (ctx.MkLe(_psurge, _maxacref));

                opt.Assert(ctx.MkEq(lefteq, ctx.MkTrue()));
                opt.Assert(ctx.MkEq(righteq, ctx.MkTrue()));
                opt.Assert(ctx.MkAnd(lefteq, righteq));
                if (!ValidateStep(opt)) return false;

                Fobj = NTP * PanelCost + NBtotal * BatteryCost + ControllerCost + InverterCost;

                opt.Assert(ctx.MkFPLEq(ctx.MkFP(Fobj, s32b), ctx.MkFP(cost, s32b)));
                var rrrr = opt.Check();
                if (!ValidateStep(opt))
                {
                    Console.WriteLine($"Custo: {cost} -- Fobj: {Fobj} -- Result: {rrrr}");
                    return false;
                }

                opt.MkMinimize(ctx.MkInt((int)Fobj));
                opt.Check();
                if (rrrr == Status.SATISFIABLE)
                {
                    Console.WriteLine(opt.Model);
                    return true;
                }
            }

            return false;
        }

        private static bool ValidateStep(Optimize opt)
        {
            if (opt.Check() == Status.SATISFIABLE)
            {
                Console.Write("OK ");
                return true;
            }
            else
            {
                Console.Write("F ");
                return false;
            }
        }

        private static int GetArraySize(float[,] panelData)
        {
            if (panelData.Length > 0)
                return panelData.GetLength(0);
            else
                return -1;
        }
    }
}