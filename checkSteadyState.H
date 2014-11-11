// compare solution with the previous iteration to determine steady state

scalar delta_c1f = 0.0;
scalar delta_c2f = 0.0;
scalar delta_phiVf = 0.0;
scalar delta_phiVs = 0.0;
scalar delta_Uf = 0.0;
scalar delta_pf = 0.0;

forAll(fluidRegions, i)
{
    if(!fixNPP)
    {
        if(max(mag(c1f[i]-c1f[i].prevIter())).value() > delta_c1f)
	    delta_c1f = max(mag(c1f[i]-c1f[i].prevIter())).value();
        if(max(mag(c2f[i]-c2f[i].prevIter())).value() > delta_c2f)
	    delta_c2f = max(mag(c2f[i]-c2f[i].prevIter())).value();
        if(max(mag(phiVf[i]-phiVf[i].prevIter())).value() > delta_phiVf)
	    delta_phiVf = max(mag(phiVf[i]-phiVf[i].prevIter())).value();
    }
    if(!fixU)
    {
	if(max(mag(Uf[i]-Uf[i].prevIter())).value() > delta_Uf)
            delta_Uf = max(mag(Uf[i]-Uf[i].prevIter())).value();
        if(max(mag(pf[i]-pf[i].prevIter())).value() > delta_pf)
	    delta_pf = max(mag(pf[i]-pf[i].prevIter())).value();
    }
}

forAll(solidRegions, i)
{
    if(!fixNPP)
    {
        if(max(mag(phiVs[i]-phiVs[i].prevIter())).value() > delta_phiVs)
	    delta_phiVs = max(mag(phiVs[i]-phiVs[i].prevIter())).value();
    }
}

Info<< ">> delta_c1 = " << delta_c1f << nl
    << ">> delta_c2 = " << delta_c2f << nl
    << ">> delta_phiVf = " << delta_phiVf << nl 
    << ">> delta_U = " << delta_Uf << nl 
    << ">> delta_p = " << delta_pf << nl
    << ">> delta_phiVs = " << delta_phiVs << nl << endl;

nppSteadyState = (delta_c1f < delta_c1_max) 
	   && (delta_c2f < delta_c2_max)
 	   && (delta_phiVf < delta_phiV_max)
	   && (delta_phiVs < delta_phiV_max);


nppStokesSteadyState = nppSteadyState	   
		    && (delta_Uf < delta_U_max)
	   	    && (delta_pf < delta_p_max);

if(!fixNPP)
{
    if(nppSteadyState)
    {
	Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
	    << nl << "The NPP system reached steady state or has converged to the residual specified."
            << nl << endl;

        runTime.writeNow();
	break;
    }
}

if(!fixU)
{
    if(nppStokesSteadyState)
    {
	Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
	    << nl << "The NPP-Stokes system reached steady state or has converged to the residual specified."
            << nl << endl;

        runTime.writeNow();
	break;
    }
}


