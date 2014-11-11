/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    MRnppStokesFoam

Description
    Solver for steady state NPP-Stokes equations in multi-region

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "regionProperties.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    
    regionProperties rp(runTime);

    #include "createFluidMeshes.H"
    #include "createSolidMeshes.H"

    #include "readConstants.H"
    #include "createFluidFields.H"
    #include "createSolidFields.H"

    #include "initContinuityErrs.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    #include "initialize.H"
    #include "mrNPPStokesSteadyControl.H"

    Info<< "\nStarting iteration loop\n" << endl;
    
    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

	forAll(solidRegions,i)
	{
	    #include "setSolidRegions.H"
	    if(!fixNPP)
	    {
	        Info<< "\nSolving for phiV in solid region "
	            << solidRegions[i].name() << endl;
	        #include "solidLaplaceEqn.H"
    	    }
	}
            
	forAll(fluidRegions, i)
	{
	    #include "setFluidRegions.H"
	    if(!fixNPP)
	    {
	        Info<< "\nSolving for phiV in fluid region "
	            << fluidRegions[i].name() << endl;
	        #include "nppEqns.H"
    	    }
	    if(!fixU)
	    { 
		#include "flowEqns.H"
	    }
	}

        #include "checkSteadyState.H"

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;

    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
