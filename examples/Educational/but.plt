[Transient Analysis]
{
   Npanes: 1
   {
      traces: 1 {268959747,0,"V(out)"}
      X: (' ',0,0,1,10)
      Y[0]: ('µ',0,-0.0003,5e-005,0.0002)
      Y[1]: ('µ',0,1e+308,0.0001,-1e+308)
      Volts: ('µ',0,0,0,-0.0003,5e-005,0.0002)
      Log: 0 0 0
      GridStyle: 1
      PltMag: 1
      PltPhi: 1 0
   }
}
[AC Analysis]
{
   Npanes: 1
   {
      traces: 1 {34603010,0,"I(L2)"}
      X: (' ',0,0.01,0,10)
      Y[0]: (' ',0,1e-015,30,1000)
      Y[1]: (' ',0,-240,40,240)
      Log: 1 2 0
      GridStyle: 1
      PltMag: 1
      PltPhi: 1 0
   }
}
